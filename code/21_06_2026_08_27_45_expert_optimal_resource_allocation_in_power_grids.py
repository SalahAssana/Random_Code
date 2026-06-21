# Import necessary libraries
import pandas as pd
from pulp import LpMaximize, LpProblem, lpSum, LpVariable
import numpy as np

# Define constants
N = 10  # number of nodes in the power grid
M = 5   # number of available resources (transmission lines)
R = 2   # number of resource types (e.g., high-voltage and low-voltage transmission)

# Create a sample dataset for demonstration purposes
data = {
    'node': np.arange(N),
    'demand_high_voltage': np.random.randint(10, 100, N),
    'demand_low_voltage': np.random.randint(5, 50, N)
}

df = pd.DataFrame(data)

# Define the optimization problem using PuLP
prob = LpProblem("PowerGridOptimization", LpMaximize)

# Create variables for each node's resource allocation
high_voltage_allocation = LpVariable.dicts("HighVoltage", df['node'], 0, None, cat='Integer')
low_voltage_allocation = LpVariable.dicts("LowVoltage", df['node'], 0, None, cat='Integer')

# Define the objective function (maximize total resource utilization)
prob += lpSum([(high_voltage_allocation[i] * df.loc[i, 'demand_high_voltage']) + 
               (low_voltage_allocation[i] * df.loc[i, 'demand_low_voltage']) for i in range(N)])

# Add constraints: each node's demand must be met
for i in range(N):
    prob += high_voltage_allocation[i] + low_voltage_allocation[i] >= df.loc[i, 'demand_high_voltage'] / 2

# Add constraints: total resource utilization per transmission line (resource type) cannot exceed capacity
high_voltage_capacity = np.random.randint(1000, 5000, M)
low_voltage_capacity = np.random.randint(500, 2000, M)

for j in range(M):
    prob += lpSum([high_voltage_allocation[i] if df.loc[i, 'node'] == j else 0 for i in range(N)]) <= high_voltage_capacity[j]
    prob += lpSum([low_voltage_allocation[i] if df.loc[i, 'node'] == j else 0 for i in range(N)]) <= low_voltage_capacity[j]

# Solve the optimization problem
prob.solve()

# Print the optimized resource allocation for each node
for i in range(N):
    print(f"Node {i}: High-Voltage = {high_voltage_allocation[i].value()}, Low-Voltage = {low_voltage_allocation[i].value()}")

if __name__ == '__main__':