% Traffic Light Simulation
% Author: [Your Name]

% Define the traffic light states (red, yellow, green)
enum TrafficLightState { RED, YELLOW, GREEN };

% Define the simulation time in seconds
simulationTime = 60;

% Define the duration of each state in seconds
stateDurations = [10, 2, 15];

% Define the priority rules for the traffic lights
priorityRules = {'highway', 'local', 'pedestrian'};

% Function to simulate a single traffic light
function simulateTrafficLight(tlState)
    % Update the current state based on the priority rule and duration
    switch tlState
        case RED
            if rand < 0.5
                tlState = YELLOW;
            end
        case YELLOW
            if rand < 0.8
                tlState = GREEN;
            else
                tlState = RED;
            end
        case GREEN
            if rand < 0.3
                tlState = RED;
            end
    end
    
    % Print the current state and time
    fprintf(['Traffic Light State: ', enum2str(tlState), ', Time: %.2f seconds\n'], simulationTime);
end

% Main script to run the traffic light simulation
function main()
    % Initialize the traffic light state as RED
    tlState = RED;
    
    % Run the simulation for the specified time
    for t = 1:simulationTime
        simulateTrafficLight(tlState);
        
        % Update the current time
        t;
        
        % Wait for a short period to simulate the state change
        pause(0.1);
    end
end

% Call the main function
main();