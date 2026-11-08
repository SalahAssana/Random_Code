% Pathfinding Algorithm Generator
% 
% Description: A MATLAB script that allows users to generate different pathfinding algorithms (e.g., Dijkstra's, A*, Floyd-Warshall) for solving graph problems.

% Define a struct to hold graph information
struct Graph;
Graph.numNodes = 0;
Graph.adjMatrix = [];

% Define a function to add nodes to the graph
function addNode(graph, nodeID)
    if graph.numNodes == 0 || nodeID > graph.numNodes + 1
        error('Invalid node ID');
    end
    graph.numNodes = nodeID;
    if ~exist('graph.adjMatrix', 'var') || size(graph.adjMatrix, 1) < nodeID
        graph.adjMatrix = zeros(nodeID);
    end
end

% Define a function to add edges to the graph
function addEdge(graph, startNode, endNode, weight)
    if startNode > graph.numNodes || endNode > graph.numNodes
        error('Invalid node ID');
    end
    graph.adjMatrix(startNode, endNode) = weight;
    graph.adjMatrix(endNode, startNode) = weight;  % Assuming undirected graph
end

% Define a function to run Dijkstra's algorithm
function dijkstra(graph, startNode)
    distance = Inf * ones(1, graph.numNodes);
    distance(startNode) = 0;
    parent = -1 * ones(1, graph.numNodes);
    
    for i = 2:graph.numNodes
        minDistNode = find(distance == min(distance));
        node = minDistNode(1);
        distance(node) = Inf;
        
        for neighbor = 1:graph.numNodes
            if graph.adjMatrix(node, neighbor) ~= 0 && distance(neighbor) > distance(node) + graph.adjMatrix(node, neighbor)
                distance(neighbor) = distance(node) + graph.adjMatrix(node, neighbor);
                parent(neighbor) = node;
            end
        end
    end
    
    for i = 1:graph.numNodes
        fprintf('Node %d: Distance = %.2f, Parent Node = %d\n', i, distance(i), parent(i));
    end
end

% Define a function to run A* algorithm
function aStar(graph, startNode, endNode)
    priorityQueue = [];
    cameFrom = zeros(1, graph.numNodes);
    costSoFar = Inf * ones(1, graph.numNodes);
    
    costSoFar(startNode) = 0;
    
    while true
        % Get the node with the lowest cost-so-far value
        [minCost, minIndex] = min(costSoFar);
        node = minIndex;
        
        if node == endNode
            break;
        end
        
        % Remove the node from the priority queue and update its cameFrom information
        temp = priorityQueue(1);
        priorityQueue(1) = [];
        for i = 2:size(priorityQueue, 2)
            if i < size(priorityQueue, 2)
                priorityQueue(i - 1) = priorityQueue(i);
            end
        end
        cameFrom(node) = temp;
        
        % Update the cost-so-far values of the node's neighbors
        for neighbor = 1:graph.numNodes
            if graph.adjMatrix(node, neighbor) ~= 0 && costSoFar(neighbor) > costSoFar(node) + graph.adjMatrix(node, neighbor)
                costToNeighbor = costSoFar(node) + graph.adjMatrix(node, neighbor);
                if costToNeighbor < costSoFar(neighbor)
                    costSoFar(neighbor) = costToNeighbor;
                end
            end
        end
        
        % Add the node to the priority queue with its cost-so-far value as its priority
        for i = 1:graph.numNodes
            if graph.adjMatrix(node, i) ~= 0 && costSoFar(i) > costSoFar(node) + graph.adjMatrix(node, i)
                push(priorityQueue, [i, costSoFar(i)]);
            end
        end
    end
    
    path = [];
    node = endNode;
    
    while node ~= startNode
        path([1:length(path) + 1]) = node;
        node = cameFrom(node);
    end
    path([1:length(path)]) = startNode;
    
    fprintf('Path: ');
    for i = length(path):-1:1
        fprintf('%d ', path(i));
    end
    fprintf('\n');
end

% Define a function to run Floyd-Warshall algorithm
function floydWarshall(graph)
    distanceMatrix = zeros(graph.numNodes, graph.numNodes);
    
    % Initialize the distance matrix with infinite values
    for i = 1:graph.numNodes
        for j = 1:graph.numNodes
            if i == j
                distanceMatrix(i, j) = 0;
            elseif graph.adjMatrix(i, j) ~= 0
                distanceMatrix(i, j) = graph.adjMatrix(i, j);
            else
                distanceMatrix(i, j) = Inf;
            end
        end
    end
    
    % Find the shortest path between all pairs of nodes
    for k = 1:graph.numNodes
        for i = 1:graph.numNodes
            for j = 1:graph.numNodes
                if distanceMatrix(i, k) + distanceMatrix(k, j) < distanceMatrix(i, j)
                    distanceMatrix(i, j) = distanceMatrix(i, k) + distanceMatrix(k, j);
                end
            end
        end
    end
    
    % Print the shortest path between all pairs of nodes
    for i = 1:graph.numNodes
        for j = 1:graph.numNodes
            if distanceMatrix(i, j) == Inf
                fprintf('%.2f ', 'N/A');
            else
                fprintf('%.2f ', distanceMatrix(i, j));
            end
        end
        fprintf('\n');
    end
end

% Main function to run the program
function main()
    % Add nodes to the graph
    addNode(Graph, 5);
    
    % Add edges to the graph
    addEdge(Graph, 1, 2, 4);
    addEdge(Graph, 1, 3, 2);
    addEdge(Graph, 2, 3, 9);
    addEdge(Graph, 2, 4, 14);
    addEdge(Graph, 3, 4, 10);
    
    % Run Dijkstra's algorithm
    dijkstra(Graph, 1);
    
    % Run A* algorithm
    aStar(Graph, 1, 4);
    
    % Run Floyd-Warshall algorithm
    floydWarshall(Graph);
end

% Start the program
main();