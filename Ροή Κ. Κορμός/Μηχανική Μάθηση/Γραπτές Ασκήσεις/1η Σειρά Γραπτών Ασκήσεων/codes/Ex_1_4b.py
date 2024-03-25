import matplotlib.pyplot as plt
import numpy as np

# Define the figure and axis
fig, ax = plt.subplots(figsize=(6, 6))

# Set the limits and labels of the plot
ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_xticks(np.arange(-5, 6, 1))
ax.set_yticks(np.arange(-5, 6, 1))
ax.set_xlabel('x1')
ax.set_ylabel('x2')

# Draw the grey positive area including the boundary
ax.fill_between(x=[0, 4], y1=0, y2=4, color='grey', alpha=0.3)
ax.fill_betweenx(y=[0, -4], x1=-4, x2=0, color='grey', alpha=0.3)

# Draw the neurons as circles
ax.scatter([0, 0], [2, -2], s=1000, c='orange', alpha=0.6, edgecolors='black', zorder=5)

# Annotate the neurons with their weights and polarizations
ax.annotate('N1\nw1=1, w2=0\nbias=0', xy=(0, 2), xytext=(-1, 2),
            arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12, ha='center')
ax.annotate('N2\nw1=0, w2=1\nbias=0', xy=(0, -2), xytext=(-1, -2),
            arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12, ha='center')

# Draw the output neuron as a square
ax.scatter([2], [0], s=1200, c='blue', alpha=0.6, edgecolors='black', marker='s', zorder=5)

# Annotate the output neuron
ax.annotate('N3\nw1=1, w2=-1\nbias=0.5', xy=(2, 0), xytext=(3, 0),
            arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12, ha='center')

# Plot the vertical and horizontal lines representing the decision boundaries
ax.axvline(x=0, color='black', linestyle='--')
ax.axhline(y=0, color='black', linestyle='--')

# Add a legend to explain the colors
ax.legend(['Decision Boundary', 'Neuron', 'Output Neuron'], loc='upper left')

# Show the plot with the network topology
plt.grid(True)
plt.title('Neural Network Topology for 2D Space Partition')
plt.show()
