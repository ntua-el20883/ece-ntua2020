from pulp import LpMinimize, LpProblem, LpVariable
from tabulate import tabulate

# Create a LP problem
problem = LpProblem("Production_Planning", LpMinimize)

# Parameters
months = 13
demand = [0, 2100, 1900, 1600, 1500, 1550, 1400, 1250, 1700, 2200, 2300, 2100, 1950]
Cp = 50
Cs = 0.8
Ci = 1.3
Cd = 2
Co = 2.5
Cu = 4
NP = 1800
initial_P = 1600
initial_S = 700

# Decision variables
P = LpVariable.dicts("P", range(months), lowBound=0, cat="Integer")
S = LpVariable.dicts("S", range(months), lowBound=0, cat="Integer")
I = LpVariable.dicts("I", range(months), lowBound=0, cat="Integer")
D = LpVariable.dicts("D", range(months), lowBound=0, cat="Integer")
O = LpVariable.dicts("O", range(months), lowBound=0, cat="Integer")
U = LpVariable.dicts("U", range(months), lowBound=0, cat="Integer")
Bi = LpVariable.dicts("Bi", range(months), cat="Binary")
Bd = LpVariable.dicts("Bd", range(months), cat="Binary")
Bo = LpVariable.dicts("Bo", range(months), cat="Binary")
Bu = LpVariable.dicts("Bu", range(months), cat="Binary")

# Big M method
M = 1000000

# Constraints
problem += S[0] == initial_S
problem += P[0] == initial_P
problem += I[0] == 0
problem += D[0] == 0
problem += O[0] == 0
problem += U[0] == 0
problem += Bi[0] == 0
problem += Bd[0] == 0
problem += Bo[0] == 0
problem += Bu[0] == 0

# More constraints
for i in range(1, 13):
    problem += S[i] == S[i - 1] + P[i] - demand[i]
    problem += I[i] == P[i] - P[i - 1]
    problem += D[i] == P[i - 1] - P[i]
    problem += O[i] == P[i] - NP
    problem += U[i] == NP - P[i]
    problem += Bi[i] + Bd[i] <= 1
    problem += Bo[i] + Bu[i] <= 1
    problem += I[i] <= M * Bi[i]
    problem += D[i] >= - M * Bd[i]
    problem += O[i] <= M * Bo[i]
    problem += U[i] >= - M * Bu[i]

# Objective function
problem += (
    Cp * sum(P[i] for i in range(months))
    + Cs * sum(S[i] for i in range(months))
    + Ci * sum(I[i] for i in range(months))
    + Cd * sum(D[i] for i in range(months))
    + Co * sum(O[i] for i in range(months))
    + Cu * sum(U[i] for i in range(months))
)

# Solve the problem
problem.solve()

# Extract the values of decision variables
P_values = [P[i].value() for i in range(months)]
S_values = [S[i].value() for i in range(months)]
I_values = [I[i].value() for i in range(months)]
D_values = [D[i].value() for i in range(months)]
O_values = [O[i].value() for i in range(months)]
U_values = [U[i].value() for i in range(months)]
Bi_values = [Bi[i].value() for i in range(months)]
Bd_values = [Bd[i].value() for i in range(months)]
Bo_values = [Bo[i].value() for i in range(months)]
Bu_values = [Bu[i].value() for i in range(months)]

# Organize data for tabulation
data = []
for i in range(1,13):
    data.append(
        [i,   P_values[i], S_values[i], demand[i], P_values[i]+S_values[i-1], I_values[i], D_values[i], O_values[i], U_values[i], Bi_values[i], Bd_values[i], Bo_values[i], Bu_values[i]]
    )

# Table headers
headers = ["Month", "Production", "Stock", "Demand", "Packages", "Increase", "Decrease", "Overtime", "Underemployment", "Bin_I", "Bin_D", "Bin_O", "Bin_U"]

# Print the table using tabulate
print(tabulate(data, headers=headers, tablefmt="grid"))
