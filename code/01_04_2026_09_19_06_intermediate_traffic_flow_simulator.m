% Traffic Flow Simulator
% 
% Simulate the flow of traffic at an intersection using agent-based modeling
% and queueing theory concepts.

function traffic_flow_simulator

    % Define simulation parameters
    num_lanes = 3;  % Number of lanes at the intersection
    num_cars_per_lane = 10;  % Initial number of cars per lane
    max_speed = 25;  % Maximum speed in km/h
    time_step = 1;  % Time step in seconds

    % Initialize traffic variables
    traffic_vars = struct();
    traffic_vars.lanes = cell(num_lanes, 1);
    for i = 1:num_lanes
        traffic_vars.lanes{i} = struct('cars', num_cars_per_lane, 'speed', zeros(1, num_cars_per_lane), 'queue_len', 0);
    end

    % Define transition rules
    function transition(lane)
        % Update car speeds based on queue length and speed limits
        for i = 1:lane.cars
            if lane.queue_len > 2
                lane.speed(i) = min(max_speed, lane.speed(i) - 5);
            else
                lane.speed(i) = min(max_speed, lane.speed(i) + 5);
            end
        end

        % Update queue length based on car arrival and departure rates
        lane.queue_len = mod(lane.queue_len + (rand() < 0.2), 3);  % Arrivals at 20% rate
        for i = 1:lane.cars
            if rand() < lane.speed(i) / max_speed  % Departures based on speed
                lane.cars = lane.cars - 1;
                break;
            end
        end
    end

    % Run simulation loop
    for t = 1:100  % Simulate for 100 time steps
        for i = 1:num_lanes
            transition(traffic_vars.lanes{i});
        end

        % Print current traffic state
        fprintf('Time Step %d:\n', t);
        for i = 1:num_lanes
            fprintf('Lane %d: %d cars, speed range [%d, %d], queue length %d\n', i, traffic_vars.lanes{i}.cars, min(traffic_vars.lanes{i}.speed), max(traffic_vars.lanes{i}.speed), traffic_vars.lanes{i}.queue_len);
        end
        fprintf('\n');
    end

end
```
