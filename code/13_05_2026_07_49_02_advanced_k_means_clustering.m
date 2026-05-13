% K-Means Clustering Algorithm in MATLAB

classdef KMeans < handle
    methods
        function obj = KMeans(k, max_iter)
            % Constructor for K-Means clustering algorithm
            this.k = k;
            this.max_iter = max_iter;
            this.centroids = zeros(k, 2);
            this.cluster_assignments = zeros(1, size(obj.data, 1));
        end
        
        function obj = fit(obj, data)
            % Fit the K-Means clustering algorithm to the given data
            this.data = data;
            
            for i = 1:this.max_iter
                % Assign each data point to its closest centroid
                this.cluster_assignments = zeros(1, size(data, 1));
                for j = 1:size(data, 1)
                    distances = sqrt(sum((data(j,:) - this.centroids).^2));
                    [min_dist, min_idx] = min(distances);
                    this.cluster_assignments(j) = min_idx;
                end
                
                % Update the centroids
                for c = 1:this.k
                    indices = find(this.cluster_assignments == c);
                    if ~isempty(indices)
                        this.centroids(c,:) = mean(data(indices,:),1);
                    end
                end
            end
        end
        
        function results = predict(obj, data)
            % Predict the cluster assignments for given data
            distances = sqrt(sum((data - repmat(this.centroids', size(data, 1), 1)).^2));
            [min_dist, min_idx] = min(distances);
            results = min_idx';
        end
    end
end

% Synthetic Data Generation
n_points_per_cluster = 100;
n_clusters = 3;
data = zeros(n_points_per_cluster * n_clusters, 2);

for i = 1:n_clusters
    cluster_mean_x = rand(1);
    cluster_mean_y = rand(1);
    for j = 1:n_points_per_cluster
        data((i-1)*n_points_per_cluster + j,:) = [rand(1), rand(1) + cluster_mean_y];
    end
end

% K-Means Clustering Algorithm Execution
k = n_clusters;
max_iter = 10;

kmeans_obj = KMeans(k, max_iter);
data_clustered = kmeans_obj.fit(data);

% Display the clustered data
figure();
scatter(data(:,1), data(:,2));
hold on;
for i = 1:k
    indices = find(kmeans_obj.cluster_assignments == i);
    scatter(data(indices,1), data(indices,2), 'r');
end
hold off;

% Predict the cluster assignments for new data
new_data = [0.5, 0.7; 0.3, 0.8; 0.9, 0.4];
cluster_assignments_new = kmeans_obj.predict(new_data);

figure();
scatter(data(:,1), data(:,2));
hold on;
for i = 1:k
    indices = find(kmeans_obj.cluster_assignments == i);
    scatter(data(indices,1), data(indices,2), 'r');
end
scatter(new_data(:,1), new_data(:,2), 'go');
text(0.5, 0.7, num2str(cluster_assignments_new(1)));
text(0.3, 0.8, num2str(cluster_assignments_new(2)));
text(0.9, 0.4, num2str(cluster_assignments_new(3)));
hold off;