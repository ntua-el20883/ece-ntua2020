import numpy as np
from tabulate import tabulate

# Fixed prices for buying and selling newspapers
buying_price = 2  # Cost price per newspaper.
selling_price = 3  # Selling price per newspaper.

# Generating a range of possible demand values to simulate different scenarios.
demand_range = np.arange(100, 1100, 100)  # Possible demand values, from 100 to 1000, in 100-unit steps.

# Function to calculate profit based on ordered quantity and actual demand
def calculate_profit(order_quantity, demand):
    sold_quantity = min(order_quantity, demand)  # The quantity sold is the lesser of demand or the order quantity.
    return (sold_quantity * selling_price) - (order_quantity * buying_price)  # Profit calculation formula.

# Iteration over possible order quantities to evaluate performance
order_quantities = demand_range  # Using the same range for order quantities as for demand.
expected_profits = []  # List to store the expected profit for each order quantity.

# Data containers for displaying results
full_table_data = []
expected_profits_table = []

# Headers for displaying results using tabulate
expected_headers = ["Order Quantity"] + list(demand_range)
full_headers = ["Demand"] + list(demand_range)

for order_quantity in order_quantities:
    # Calculate and store profits for each demand scenario given an order quantity.
    profits = [calculate_profit(order_quantity, d) for d in demand_range]
    full_table_data.append([f"Profit for ordering: {order_quantity}"] + profits)

    # Calculate the expected profit for this order quantity as the mean of all scenario profits.
    expected_profit = np.mean(profits)
    expected_profits.append(expected_profit)

# Displaying expected profits for each order quantity
expected_profits_table.append([f"Expected Profit"] + expected_profits)
print("Profit for each possible Demand and Order Quantity:")
print(tabulate(full_table_data, full_headers, tablefmt="fancy_grid"))
print("\nExpected Profits per Order Quantity:")
print(tabulate(expected_profits_table, expected_headers, tablefmt="fancy_grid"))

# Identifying the optimal order quantity and its corresponding expected profit
optimal_order_quantity = order_quantities[np.argmax(expected_profits)]
optimal_expected_profit = max(expected_profits)
print(f"\nOptimal Order Quantity: {optimal_order_quantity} newspapers")
print(f"Expected Profit (SP): €{optimal_expected_profit:.2f}")

# Analysis under the expected demand scenario
expected_demand = np.mean(demand_range)  # Calculate the average demand to represent the expected demand.
expected_demand_profits = [calculate_profit(expected_demand, d) for d in demand_range]
WSS = np.mean(expected_demand_profits)
print(f"Expected demand: {expected_demand:.2f}")
print(f"Expected Demand Profit (WSS): €{WSS:.2f}")

# Calculating the Value of Stochastic Solution (VSS)
VSS = optimal_expected_profit - WSS
print(f"Value of Stochastic Solution (VSS = SP - WSS): €{VSS:.2f}")

# Calculating the Expected Value of Perfect Information (EVPI)
perfect_information_profits = [calculate_profit(d, d) for d in demand_range]
EVPI = np.mean(perfect_information_profits) - optimal_expected_profit
print(f"Perfect Information Expected Profit (WS): €{np.mean(perfect_information_profits)}")
print(f"Expected Value of Perfect Information (EVPI = WS - SP): €{EVPI:.2f}")
