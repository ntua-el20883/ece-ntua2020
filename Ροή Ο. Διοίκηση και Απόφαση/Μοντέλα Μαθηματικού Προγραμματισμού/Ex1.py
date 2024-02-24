from pulp import *  # Import the PuLP library, which is used for linear programming problems.
from tabulate import tabulate  # Import the tabulate library for nicely formatted table outputs.

# Define the problem
prob = LpProblem("Maximize_Value", LpMaximize)  # Create a linear programming problem with the goal of maximizing an objective (in this case, the "value").

# Parameters
quantities = ['q1', 'q2', 'q3', 'q4', 'q5']  # Define the names of the variables representing the quantities of packets.
weights = [5, 8, 3, 2, 7]  # Define the weight of each type of packet.
volumes = [1, 8, 6, 5, 4]  # Define the volume of each type of packet.
values = [4, 7, 6, 5, 4]  # Define the value associated with each type of packet.

# Decision Variables
q_vars = LpVariable.dicts("Packet", quantities, lowBound=0, cat='Integer')
# Create a dictionary of decision variables where each key is a packet type (q1 to q5),
# with each variable constrained to be an integer greater than or equal to 0.

# Objective Function
prob += lpSum([values[i] * q_vars[quantities[i]] for i in range(len(quantities))]), "Total Value"
# Set the objective function of the problem to maximize the total value of the packets.
# This is done by summing the product of each packet's value and the corresponding decision variable.

# Constraints
# Define constraints for the total weight and volume of the packets.
weight_constraint = lpSum([weights[i] * q_vars[quantities[i]] for i in range(len(quantities))])  # Calculate the total weight.
volume_constraint = lpSum([volumes[i] * q_vars[quantities[i]] for i in range(len(quantities))])  # Calculate the total volume.
prob += weight_constraint <= 210, "Total Weight"  # Add a constraint that the total weight must not exceed 210 units.
prob += volume_constraint <= 198, "Total Volume"  # Add a constraint that the total volume must not exceed 198 units.

# Solve the problem
prob.solve()  # Solve the optimization problem using PuLP's default solver.

# Print the results
print("---------------------------------------------------------")
print("Status:", LpStatus[prob.status])  # Print the solution status (e.g., Optimal, Infeasible, Unbounded).

# Prepare data for tabulate
table_data = []
for i, quantity in enumerate(quantities):
    units = q_vars[quantity].varValue  # Get the optimized value (number of units) for each packet type.
    # Prepare a row for each packet type with its optimized units, total weight, total volume, and total value.
    row = [f"Packet {i+1}", units, units * weights[i], units * volumes[i], units * values[i]]
    table_data.append(row)

# Print the tabulated results
headers = ["Packet", "Units", "Weight (tons)", "Volume (m^3)", "Value"]  # Define column headers for the output table.
print(tabulate(table_data, headers, tablefmt="grid"))  # Display the table with results in a grid format.

# Calculating and printing the total weight, volume, and value
# Calculate the sum of weights, volumes, and values based on the optimized number of units for each packet type.
total_weight = sum([q_vars[quantity].varValue * weights[i] for i, quantity in enumerate(quantities)])
total_volume = sum([q_vars[quantity].varValue * volumes[i] for i, quantity in enumerate(quantities)])

# Print the total weight, volume, and the objective value (total value of the shipment).
print(f"\nTotal weight of the shipment: {total_weight} tons")
print(f"Total volume of the shipment: {total_volume} m^3")
print("Total value of the shipment: ", value(prob.objective))  # Use the value() function to get the total value from the objective.
print("---------------------------------------------------------")
