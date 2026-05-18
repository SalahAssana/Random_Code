% Graph Traversal Algorithm
% Author: [Your Name]

% Define the graph as an adjacency matrix
graph = [
    0 1 0 0;
    1 0 1 1;
    0 1 0 1;
    0 1 1 0
];

% Function to perform DFS traversal
function dfs_traversal(graph, start_node)
    visited = zeros(size(graph));
    stack = [start_node];
    
    while ~isempty(stack)
        current_node = stack(end);
        if visited(current_node) == 0
            visited(current_node) = 1;
            disp([num2str(current_node), ' is being visited.']);
            
            % Get the neighbors of the current node
            neighbors = find(graph(:,current_node));
            for i = 1:length(neighbors)
                neighbor = neighbors(i);
                if visited(neighbor) == 0
                    stack(end + 1) = neighbor;
                end
            end
        else
            disp([num2str(current_node), ' has already been visited.']);
            stack(end) = [];
        end
    end
end

% Function to perform BFS traversal
function bfs_traversal(graph, start_node)
    visited = zeros(size(graph));
    queue = [start_node];
    
    while ~isempty(queue)
        current_node = queue(1);
        queue(1) = [];
        
        if visited(current_node) == 0
            visited(current_node) = 1;
            disp([num2str(current_node), ' is being visited.']);
            
            % Get the neighbors of the current node
            neighbors = find(graph(:,current_node));
            for i = 1:length(neighbors)
                neighbor = neighbors(i);
                if visited(neighbor) == 0
                    queue(end + 1) = neighbor;
                end
            end
        else
            disp([num2str(current_node), ' has already been visited.']);
        end
    end
end

% Main function to test the graph traversal algorithms
function main()
    start_node = 1; % Start node for both DFS and BFS
    
    % Perform DFS traversal
    disp('DFS Traversal:');
    dfs_traversal(graph, start_node);
    
    % Perform BFS traversal
    disp('BFS Traversal:');
    bfs_traversal(graph, start_node);
end

% Run the main function if this script is being run directly (not imported)
if nargin == 0 || isempty(varargin)
    main();
end