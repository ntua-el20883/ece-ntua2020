import numpy as np
import matplotlib.pyplot as plt

# Define the means for the two classes and the covariance matrix for part (c)
mu1_c = np.array([-2, 0])
mu2_c = np.array([2, 1])
cov_c = np.array([[1, -0.6], [-0.6, 1]])  # Same covariance matrix as in part (b)

# Number of points to generate for each class
num_points = 200

# Generate sample points for both classes using Gaussian distributions
class1_samples_c = np.random.multivariate_normal(mu1_c, cov_c, num_points)
class2_samples_c = np.random.multivariate_normal(mu2_c, cov_c, num_points)

# Define the quadratic decision boundary function for part (c)
def decision_boundary_c(x1, x2):
    return 3.59375 * x1**2 + 2.65625 * x1 * x2 - 3.9262 * x2**2 + 2.65625

# Create a grid of values for x1 and x2 to plot the decision boundary curve
x1_values_c, x2_values_c = np.meshgrid(np.linspace(-6, 6, 400), np.linspace(-6, 6, 400))
z_values_c = decision_boundary_c(x1_values_c, x2_values_c)

# Plotting
plt.figure(figsize=(8, 6))
plt.scatter(class1_samples_c[:, 0], class1_samples_c[:, 1], c='red', label='Class 1')
plt.scatter(class2_samples_c[:, 0], class2_samples_c[:, 1], c='blue', label='Class 2')
plt.contour(x1_values_c, x2_values_c, z_values_c, levels=[0], colors='k')  # Decision boundary
plt.scatter(mu1_c[0], mu1_c[1], s=100, c='black', marker='x', label='Mean of Class 1')
plt.scatter(mu2_c[0], mu2_c[1], s=100, c='black', marker='o', label='Mean of Class 2')
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('Part (c): Quadratic Decision Boundary and Data Points')
plt.legend()
plt.grid(True)
plt.show()
