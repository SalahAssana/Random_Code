#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define constants for packet sizes and rates
#define PACKET_SIZE 1024
#define PACKETS_PER_SECOND 1000

// Define structures for packets and network interfaces
typedef struct {
    int id;
    char data[PACKET_SIZE];
} Packet;

typedef struct {
    char name[20];
    int bandwidth;
    double latency;
    int packet_loss;
    Packet* packets;
    int packet_count;
} NetworkInterface;

// Function to simulate network traffic
void generate_traffic(NetworkInterface* interface, int duration) {
    // Initialize random seed for simulation randomness
    srand(time(NULL));

    // Simulate traffic generation
    for (int i = 0; i < duration; i++) {
        Packet packet;
        packet.id = rand() % 10000;
        memcpy(packet.data, "Hello", strlen("Hello"));
        interface->packets[interface->packet_count++] = packet;

        // Simulate latency and packet loss
        if (rand() % 100 > interface->latency) {
            // Packet lost due to network congestion
            printf("Packet loss: %d\n", interface->packet_loss++);
        } else {
            // Calculate transmission time based on bandwidth and packet size
            int transmission_time = (int)ceil((double)PACKET_SIZE / (interface->bandwidth * 8));
            printf("Transmission time: %d\n", transmission_time);
        }
    }
}

// Function to analyze network traffic
void analyze_traffic(NetworkInterface* interface, int duration) {
    // Calculate total packets transmitted and received
    int total_packets = interface->packet_count;
    int received_packets = total_packets - interface->packet_loss;

    // Calculate packet loss rate
    double packet_loss_rate = (double)interface->packet_loss / total_packets * 100;
    printf("Packet loss rate: %.2f%%\n", packet_loss_rate);

    // Calculate average latency
    double total_latency = 0;
    for (int i = 0; i < received_packets; i++) {
        int transmission_time = (int)ceil((double)PACKET_SIZE / (interface->bandwidth * 8));
        total_latency += transmission_time;
    }
    double average_latency = total_latency / received_packets;
    printf("Average latency: %.2f\n", average_latency);
}

// Main function
int main() {
    // Initialize network interface structure
    NetworkInterface interface;
    strcpy(interface.name, "Ethernet");
    interface.bandwidth = 1000; // Mbps
    interface.latency = 0.5; // percentage
    interface.packet_loss = 0;
    interface.packets = (Packet*)malloc(PACKETS_PER_SECOND * sizeof(Packet));
    interface.packet_count = 0;

    // Simulate traffic generation for 10 seconds
    generate_traffic(&interface, PACKETS_PER_SECOND);

    // Analyze network traffic
    analyze_traffic(&interface, PACKETS_PER_SECOND);

    return 0;
}