import numpy as np
import matplotlib.pyplot as plt

# Define the means for the two classes and the covariance matrix for part (b)
mu1_b = np.array([-2, 0])
mu2_b = np.array([2, 1])
cov_b = np.array([[1, -0.6], [-0.6, 1]])  # Non-identity covariance matrix

# Number of points to generate for each class
num_points = 200

# Generate sample points for both classes using Gaussian distributions
class1_samples_b = np.random.multivariate_normal(mu1_b, cov_b, num_points)
class2_samples_b = np.random.multivariate_normal(mu2_b, cov_b, num_points)

# Define the decision boundary function for part (b)
def decision_boundary_b(x):
    return (7.1875 * x - 2.65625) / 5.3125  # Rearranged from -7.1875x1 - 5.3125x2 + 2.65625 = 0

# Create a range of values for x to plot the decision boundary line
x_values_b = np.linspace(-6, 6, 400)

# Plotting
plt.figure(figsize=(8, 6))
plt.scatter(class1_samples_b[:, 0], class1_samples_b[:, 1], c='red', label='Class 1')
plt.scatter(class2_samples_b[:, 0], class2_samples_b[:, 1], c='blue', label='Class 2')
plt.plot(x_values_b, decision_boundary_b(x_values_b), 'k-', label='Decision Boundary')
plt.scatter(mu1_b[0], mu1_b[1], s=100, c='black', marker='x', label='Mean of Class 1')
plt.scatter(mu2_b[0], mu2_b[1], s=100, c='black', marker='o', label='Mean of Class 2')
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('Part (b): Decision Boundary and Data Points')
plt.legend()
plt.grid(True)
plt.show()
