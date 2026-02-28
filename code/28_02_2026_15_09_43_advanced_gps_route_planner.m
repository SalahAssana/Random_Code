% GPS Route Planner in MATLAB
%
% This program uses graph theory and optimization techniques to plan the most efficient GPS route between multiple locations.

classdef GPSRoutePlanner < handle
    methods (Access = public)
        function obj = GPSRoutePlanner(locations, edges)
            % Constructor for GPSRoutePlanner object.
            % @param locations - cell array of location names
            % @param edges - sparse matrix where edge(i,j) is the distance between locations i and j
            obj.locations = locations;
            obj.edges = edges;
        end
        
        function route = find_route(obj, start_location, end_location)
            % Find the shortest path from start_location to end_location using Dijkstra's algorithm.
            % @param start_location - name of starting location
            % @param end_location - name of ending location
            % @return route - vector of location names representing the shortest path
            
            num_locations = size(obj.edges, 1);
            distance = inf(num_locations, 1); 
            previous = zeros(num_locations, 1);
            
            distance(1) = 0;  % Distance to start_location is 0
            priority_queue = [start_location];
            while ~isempty(priority_queue)
                current_location = priority_queue(1);
                priority_queue(1) = [];
                
                for i = 2:num_locations
                    if obj.edges(current_location, i) > 0 && distance(i) == inf
                        distance(i) = distance(current_location) + obj.edges(current_location, i);
                        previous(i) = current_location;
                        priority_queue = [priority_queue; i];
                    end
                end
                
                if current_location == end_location
                    break;
                end
            end
            
            route = [];
            while current_location ~= start_location
                route = [current_location route];
                current_location = previous(current_location);
            end
            route = [start_location route];
            
            % Reverse the route because it was constructed in reverse order.
            route = fliplr(route);
        end
        
    end
    
end

% Synthetic data for testing
locations = {'A', 'B', 'C', 'D', 'E'};
edges = sparse([1 2 2 3 0; 2 1 3 4 0; 2 3 0 5 0; 3 4 0 6 0; 0 0 0 0 0], [1 2 3 4 5], [10 20 30 40 50]);
start_location = 'A';
end_location = 'E';

% Create and use a GPSRoutePlanner object
planner = GPSRoutePlanner(locations, edges);
route = planner.find_route(start_location, end_location);

% Print the route
fprintf('The shortest path from %s to %s is:\n', start_location, end_location);
for i = 1:length(route) - 1
    fprintf('%s -> ', route{i});
end
fprintf('%s\n', route{end});