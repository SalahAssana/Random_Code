% Interactive Graph Visualization using Dijkstra's Algorithm

% Import necessary libraries
import graph.*;
import java.util.*;

% Define a struct to hold graph properties
struct GraphProps
    numNodes = 0;
    numEdges = 0;
end;

% Define a struct to hold node properties
struct NodeProps
    id = -1;
    neighbors = {};
end;

% Define a function to create an adjacency list representation of the graph
function adjacencyList = createAdjacencyList(numNodes, numEdges)
    % Initialize the adjacency list with empty lists for each node
    adjacencyList = cell(1, numNodes);
    for i = 1:numNodes
        adjacencyList{i} = {};
    end;
    
    % Populate the adjacency list with edges
    for i = 1:numEdges
        [node1, node2] = input('Enter nodes for edge ', 's');
        adjacencyList{str2num(node1)}{end+1} = str2num(node2);
        adjacencyList{str2num(node2)}{end+1} = str2num(node1);  % Undirected graph
    end;
    
    % Create a struct to hold the graph properties
    graphProps = GraphProps();
    graphProps.numNodes = numNodes;
    graphProps.numEdges = numEdges;
    
    % Return the adjacency list and graph properties
    [adjacencyList, graphProps]
end;

% Define a function to run Dijkstra's algorithm on the graph
function shortestPaths = dijkstra(adjacencyList, startNode)
    % Initialize the distance array with infinity for all nodes except the start node
    distances = inf(1, size(adjacencyList, 2));
    distances(startNode) = 0;
    
    % Initialize the previous node array with NaN for all nodes except the start node
    previousNodes = nan(size(adjacencyList, 2), 1);
    previousNodes(startNode) = startNode;
    
    % Create a priority queue to hold nodes to be processed
    queue = PriorityQueue();
    queue.enqueue([startNode, 0]);
    
    % Process nodes in the priority queue
    while ~queue.isEmpty()
        [node, dist] = queue.dequeue();
        
        % Update distances and previous nodes for neighbors of the current node
        for neighbor = adjacencyList{node}
            oldDist = distances(neighbor);
            newDist = dist + 1;
            
            if newDist < oldDist
                distances(neighbor) = newDist;
                previousNodes(neighbor) = node;
                queue.enqueue([neighbor, newDist]);
            end;
        end;
    end;
    
    % Return the shortest paths from the start node to all other nodes
    shortestPaths = distances;
end;

% Define a function to visualize the graph and shortest paths
function visualize(adjacencyList, shortestPaths)
    % Create a figure for visualization
    fig = figure();
    ax = axes();
    
    % Plot the adjacency list as a graph
    for node = 1:size(adjacencyList, 2)
        if ~isempty(adjacencyList{node})
            for neighbor = adjacencyList{node}
                plot([node, neighbor], 'b', 'LineWidth', 2);
            end;
        end;
    end;
    
    % Plot the shortest paths as red lines
    for node = 1:size(shortestPaths, 2)
        if shortestPaths(node) ~= inf
            path = [startNode];
            while path(end) ~= node
                path = [path, previousNodes(path(end))];
            end;
            
            plot(path, 'r', 'LineWidth', 2);
        end;
    end;
    
    % Set the title and axis labels
    title('Interactive Graph Visualization using Dijkstra''s Algorithm');
    xlabel('Node ID');
    ylabel('Shortest Paths');
end;

% Main function to interactively explore graph properties
function main()
    % Create an adjacency list representation of the graph
    [adjacencyList, graphProps] = createAdjacencyList(10, 15);
    
    % Run Dijkstra's algorithm on the graph
    shortestPaths = dijkstra(adjacencyList, 1);  % Start at node 1
    
    % Visualize the graph and shortest paths
    visualize(adjacencyList, shortestPaths);
    
    % Wait for user input to continue exploring graph properties
    while true
        pause(0.1);
    end;
end;

% Run the main function when the script is executed
main();