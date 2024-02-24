import pulp as pl  # Import PuLP library for linear programming.
from tabulate import tabulate  # Import tabulate for pretty-printing tables.

# Create a linear programming model
problem = pl.LpProblem("4 Stage Stochastic Problem", pl.LpMaximize)

# Define fixed parameters for the problem
V = 1000                    # Penalty cost for each MWh of unmet demand.
MC = [10, 50]               # Marginal costs for each of the two generators.
P = [60, 100]               # Maximum production capacities (in MWh) for each generator.
D = [50, 100, 120, 180]     # Demand requirements (in MWh) for each of the four periods.
E = 50                      # Maximum storage capacity (in MWh) of the hydro unit.
H = [0, 1, 2, 4, 8]         # Number of stages (scenarios) in each of the four periods.
prob = [                    # Probability of each stage occurring in each period.
    [],
    [1],
    [0.5, 0.5],
    [0.35, 0.15, 0.15, 0.35],
    [0.28, 0.07, 0.06, 0.09, 0.105, 0.045, 0.07, 0.28]
]
R = [                        # Initial reservoir levels (in MWh) for hydro storage in each period.
    [],
    [5],
    [10, 0],
    [15, 5, 5, 0],
    [20, 10, 10, 0, 10, 0, 5, 0],
]

# Initialize decision variables
d = {}      # Unmet demand (in MWh) in each stage of each period.
p = {}      # Production (in MWh) from each generator in each stage of each period.
e = {}      # Amount of energy stored (in MWh) in the hydro unit in each stage of each period.
pH = {}     # Energy transferred from hydro unit to load (in MWh) in each stage of each period.
dH = {}     # Energy transferred from generators to hydro unit (in MWh) in each stage of each period.
pH_div_etta = {}  # Placeholder for hydro output divided by efficiency factor (not directly used due to PuLP constraints).

# Define decision variables for each stage of each period
for i in range(1, 5):
    # Variables for unmet demand, generator production, hydro storage, and energy transfers
    d[i] = pl.LpVariable.dicts(f"d_{i}", (range(H[i])), lowBound=0)
    p[i] = {(n, g): pl.LpVariable(f"p_{i}_{n}_{g}", lowBound=0) for n in range(H[i]) for g in range(2)}
    e[i] = pl.LpVariable.dicts(f"e_{i}", (range(H[i])), lowBound=0)
    pH[i] = pl.LpVariable.dicts(f"pH_{i}", (range(H[i])), lowBound=0)
    dH[i] = pl.LpVariable.dicts(f"dH_{i}", (range(H[i])), lowBound=0)
    pH_div_etta[i] = pl.LpVariable.dicts(f"pH_div_etta_{i}", (range(H[i])), lowBound=0)

# Adding constraints to the model
for i in range(1, 5):
    for n in range(H[i]):
        # Production capacity constraints for each generator
        for g in range(2):
            problem += p[i][n, g] <= P[g], f"max_prod_capacity_{i}_{n}_{g}"

        # Hydro storage constraints, taking into account inflows, outflows, and previous period storage
        if i == 1:
            # Initial period has no previous storage to consider
            problem += e[i][n] == R[i][n] + dH[i][n] - pH[i][n]*1.25, f"hydro_storage_{i}_{n}"
        else:
            # Subsequent periods include storage from the previous period
            problem += e[i][n] == R[i][n] + dH[i][n] - pH[i][n]*1.25 + e[i - 1][n // 2], f"hydro_storage_{i}_{n}"

        # Ensuring hydro unit does not exceed its storage capacity
        problem += e[i][n] <= E, f"hydro_capacity_{i}_{n}"

        # Balancing demand with production and hydro energy exchanges
        problem += d[i][n] + dH[i][n] - p[i][n, 0] - p[i][n, 1] - pH[i][n] == 0, f"demand_balance_{i}_{n}"

        # Limiting unmet demand to not exceed demand requirements
        problem += d[i][n] <= D[i - 1], f"max_demand_not_met_{i}_{n}"

# Specific constraints for hydro storage levels at certain stages
problem += e[2][0] == 20
problem += e[2][1] == 20
problem += e[3][0] == 25

# Define the objective function
# Objective aims to minimize the total expected cost, considering penalties for unmet demand and production costs
objective = pl.lpSum(prob[i][n] * (V * d[i][n] - MC[0] * p[i][n, 0] - MC[1] * p[i][n, 1]) for i in range(1, 5) for n in range(H[i]))

# Set and solve the objective
problem += objective, "Total Cost"
problem.solve()

# Function to extract and format variable values for tabulation
def extract_period_values(var_dict, H, is_two_dim=False):
    period_values = []
    for period in range(1, 5):
        if is_two_dim:
            # Concatenate values for two-dimensional variables (generator production)
            values = [', '.join([str(pl.value(var_dict[period][(n, g)])) if (n, g) in var_dict[period] else "-"
                                for g in range(2)]) for n in range(H[period])]
        else:
            # Directly retrieve values for one-dimensional variables
            values = [pl.value(var_dict[period][j]) if j in var_dict[period] else None for j in range(H[period])]
        # Adjust list length for tabulation
        values += [None] * (max(H) - len(values))
        period_values.append(values)
    return period_values

# Print tables for each variable, showing values across periods and stages
variables = [("d", d), ("p", p), ("e", e), ("pH", pH), ("dH", dH)]
for name, var_dict in variables:
    is_two_dim = name == "p"
    variable_values = extract_period_values(var_dict, H, is_two_dim=is_two_dim)
    headers = [f"{name}_{i}" for i in range(1, max(H) + 1)]
    table_str = tabulate(variable_values, headers=headers, tablefmt="fancy_grid")
    print(table_str)
    print()

# Print the optimized objective function value
print(f"Optimal Objective Function Value: {pl.value(problem.objective)}")
