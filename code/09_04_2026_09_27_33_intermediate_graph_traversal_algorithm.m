% Graph Traversal Algorithm
%
% Author: <Your Name>
%
% Description: This script implements DFS (Depth-First Search) and BFS (Breadth-First Search) graph traversal algorithms.

% Import necessary packages
importgraphplotting = @import(graphplot);
importdatastructures = @import(datastructures);

% Define a struct to represent a node in the graph
struct Node
    id;
    neighbors;
end

% Function to perform DFS on the graph
function dfs(node, visited)
    % Mark the current node as visited
    visited{node.id} = true;

    % Print the node ID
    fprintf('Visiting node %d\n', node.id);

    % Recursively visit all unvisited neighbors of the node
    for i = 1:length(node.neighbors)
        neighbor = node.neighbors{i};
        if ~any(visited, 'equal', {neighbor.id})
            dfs(Node({neighbor}), visited);
        end
    end
end

% Function to perform BFS on the graph
function bfs(node, queue, visited)
    % Dequeue a node from the queue and mark it as visited
    dequeuedNode = queue(1);
    queue(1) = [];
    visited{dequeuedNode.id} = true;

    % Print the node ID
    fprintf('Visiting node %d\n', dequeuedNode.id);

    % Enqueue all unvisited neighbors of the dequeued node
    for i = 1:length(dequeuedNode.neighbors)
        neighbor = dequeuedNode.neighbors{i};
        if ~any(visited, 'equal', {neighbor.id})
            queue = [queue; neighbor];
        end
    end
end

% Main function to perform graph traversal and visualization
function main()
    % Create a sample graph with 5 nodes and edges
    node1 = Node({1}, [2; 3]);
    node2 = Node({2}, [4]);
    node3 = Node({3}, []);
    node4 = Node({4}, [1; 2]);
    node5 = Node({5}, []);

    graph = {node1, node2, node3, node4, node5};

    % Initialize visited nodes
    visited = cell(5, 1);
    for i = 1:5
        visited{i} = false;
    end

    % Perform DFS on the graph
    dfs(graph{1}, visited);

    % Clear the visited array for BFS
    visited = cell(5, 1);
    for i = 1:5
        visited{i} = false;
    end

    % Initialize a queue for BFS
    queue = [graph{1}.id];

    % Perform BFS on the graph
    while ~isempty(queue)
        bfs(graph{find([graph.id] == queue(1))}, queue, visited);
        queue = queue(2:end);
    end

    % Visualize the graph using GraphPlotting package
    gplot = graphplotting.graphplot(graph);
    figure;
    plot(gplot);
end

% Guard for MATLAB script execution
if ~exist('matlabpool', 'file')
    main();
end