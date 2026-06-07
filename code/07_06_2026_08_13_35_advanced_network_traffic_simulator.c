#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define structure for packet
typedef struct {
    int src_id;
    int dst_id;
    int seq_num;
    int size;
} Packet;

// Define structure for network node
typedef struct {
    int id;
    int packets_sent;
    int packets_received;
    struct {
        Packet *packets;
        int len;
    } queue;
} Node;

// Function to generate random packet sequence numbers
int gen_seq_num() {
    return rand() % 1000;
}

// Function to simulate network traffic
void sim_traffic(Node nodes[], int num_nodes, int duration) {
    // Initialize time
    clock_t start = clock(), end;
    double cpu_time_used;

    // Simulate traffic for the given duration
    for (int i = 0; i < duration; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (rand() % 2) {
                // Node sends a packet
                Packet *packet = malloc(sizeof(Packet));
                packet->src_id = nodes[j].id;
                packet->dst_id = (nodes[j].id + 1) % num_nodes;
                packet->seq_num = gen_seq_num();
                packet->size = rand() % 1000;
                nodes[packet->dst_id].queue.packets[nodes[packet->dst_id].queue.len++] = *packet;
            } else {
                // Node receives a packet
                if (nodes[j].queue.len > 0) {
                    Packet *packet = &nodes[j].queue.packets[0];
                    nodes[j].packets_received++;
                    free(packet);
                    for (int k = 0; k < nodes[j].queue.len - 1; k++) {
                        nodes[j].queue.packets[k] = nodes[j].queue.packets[k + 1];
                    }
                    nodes[j].queue.len--;
                }
            }
        }
    }

    // Calculate CPU time used
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Simulation complete. Time taken: %f seconds.\n", cpu_time_used);
}

int main() {
    srand(time(NULL));

    Node nodes[5];
    for (int i = 0; i < 5; i++) {
        nodes[i].id = i;
        nodes[i].packets_sent = 0;
        nodes[i].packets_received = 0;
        nodes[i].queue.len = 0;
    }

    sim_traffic(nodes, 5, 10);

    return 0;
}