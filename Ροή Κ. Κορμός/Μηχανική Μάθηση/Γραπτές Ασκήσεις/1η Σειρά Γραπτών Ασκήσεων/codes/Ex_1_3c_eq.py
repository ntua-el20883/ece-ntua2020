import numpy as np

# Define the means and the covariance matrix given in part (b)
mu1 = np.array([-2, 0])
mu2 = np.array([2, 1])
cov_b = np.array([[1, -0.6], [-0.6, 1]])

# Calculate the inverse of the covariance matrix
cov_b_inv = np.linalg.inv(cov_b)

# Misclassification costs
lambda12 = 1
lambda21 = 0.5

# Compute the coefficients for the quadratic decision boundary
A_c = -0.5 * (cov_b_inv @ (mu1 - mu2))
B_c = (mu1 - mu2).T @ cov_b_inv @ (mu1 + mu2) - 2 * np.log(lambda21 / lambda12)
C_c = -0.5 * (mu1.T @ cov_b_inv @ mu1 - mu2.T @ cov_b_inv @ mu2)

# Return the coefficients of the quadratic decision boundary
print(A_c)
print(B_c)
print(C_c)