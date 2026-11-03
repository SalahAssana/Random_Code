% Nearest Neighbor Searcher
%
% Author: <Your Name>
%
% Date: <Date>

function nearest_neighbor_search = nearestNeighborSearch(data, query)
    % Check if input data is empty
    if isempty(data)
        error('Input data cannot be empty');
    end
    
    % Check if input query is empty
    if isempty(query)
        error('Input query cannot be empty');
    end
    
    % Initialize k-d tree with the given data
    kdtree = kdtreeInit(data);
    
    % Find the nearest neighbor for each query point using the k-d tree
    nearest_neighbors = [];
    for i = 1:size(query, 1)
        [dist, idx] = kdtreeQuery(kdtree, query(i, :));
        nearest_neighbor = data(idx, :);
        nearest_neighbors = [nearest_neighbors; nearest_neighbor];
    end
    
    % Return the found nearest neighbors
    nearest_neighbor_search = nearest_neighbors;
end

% Initialize k-d tree with the given data
function kdtree = kdtreeInit(data)
    % Determine the dimensionality of the input data
    num_dimensions = size(data, 2);
    
    % Initialize the root node of the k-d tree
    kdtree.root = kdtreeNodeInit(data, 1, num_dimensions);
end

% Initialize a new k-d tree node
function node = kdtreeNodeInit(data, level, max_level)
    % Calculate the median values for each dimension
    medians = zeros(1, size(data, 2));
    for i = 1:size(data, 2)
        medians(i) = median(data(:, i));
    end
    
    % Determine the split axis and value based on the median values
    [split_axis, split_value] = kdtreeNodeGetSplit(medians);
    
    % Split the data into left and right child nodes
    left_data = [];
    right_data = [];
    for i = 1:size(data, 1)
        if data(i, split_axis) <= split_value
            left_data = [left_data; data(i, :)];
        else
            right_data = [right_data; data(i, :)];
        end
    end
    
    % Recursively create child nodes for the left and right subtrees
    node.left = kdtreeNodeInit(left_data, level + 1, max_level);
    node.right = kdtreeNodeInit(right_data, level + 1, max_level);
    
    % Store the split axis and value in the current node
    node.axis = split_axis;
    node.value = split_value;
end

% Calculate the split axis and value based on the median values
function [axis, value] = kdtreeNodeGetSplit(medians)
    % Determine the dimension with the minimum variance
    min_variance_dimension = find(min(var(medians)) == var(medians));
    
    % Use the median of the chosen dimension as the split value
    axis = min_variance_dimension;
    value = medians(axis);
end

% Query the k-d tree for the nearest neighbor to a given query point
function [dist, idx] = kdtreeQuery(kdtree, query)
    % Start at the root node of the k-d tree
    [dist, idx] = kdtreeNodeQuery(kdtree.root, query);
end

% Query a single k-d tree node for the nearest neighbor to a given query point
function [dist, idx] = kdtreeNodeQuery(node, query)
    % Check if the node is a leaf node (i.e., it contains only data points)
    if isempty(node.left) && isempty(node.right)
        % Find the distance and index of the nearest data point in the leaf node
        min_dist = inf;
        idx = 0;
        for i = 1:size(node.data, 1)
            dist = sum((query - node.data(i, :)).^2);
            if dist < min_dist
                min_dist = dist;
                idx = i;
            end
        end
    else
        % Determine the axis and value of the current node
        axis = node.axis;
        value = node.value;
        
        % Split the query point into left and right child nodes based on the split value
        if query(axis) <= value
            [dist, idx] = kdtreeNodeQuery(node.left, query);
        else
            [dist, idx] = kdtreeNodeQuery(node.right, query);
        end
    end
    
    % Return the found distance and index
    nearest_neighbor_search = [nearest_neighbors; nearest_neighbor];
end

% Synthetic data generation
data = rand(1000, 2); % Generate synthetic data points

query = rand(5, 2); % Generate synthetic query points

% Perform nearest neighbor search using the k-d tree
nearest_neighbors = nearestNeighborSearch(data, query);

% Print the found nearest neighbors
fprintf('Found Nearest Neighbors:\n');
for i = 1:size(nearest_neighbors, 1)
    fprintf('Query Point %d: ', i);
    for j = 1:size(nearest_neighbors(i, :), 2)
        fprintf('%f ', nearest_neighbors(i, j));
    end
    fprintf('\n');
end

% End of script