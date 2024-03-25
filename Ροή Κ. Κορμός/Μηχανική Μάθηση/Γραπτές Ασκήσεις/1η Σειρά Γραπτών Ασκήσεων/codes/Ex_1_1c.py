import numpy as np
import pandas as pd

# Step 1: Load the data and split into training and verification sets
data = pd.read_csv('\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\ML2023-24-hwk1.csv', delimiter=';')
training_set = data.iloc[:100, :]
verification_set = data.iloc[100:150, :]

# Extract features and target variable for the training set
X_train = training_set.iloc[:, :-1].values
y_train = training_set.iloc[:, -1].values

# Manual normalization of features
means = np.mean(X_train, axis=0)
stds = np.std(X_train, axis=0)

# Avoid division by zero for features with zero standard deviation
stds[stds == 0] = 1

X_train_normalized = (X_train - means) / stds

# Add a column of ones to the normalized features to account for the bias (intercept) in the linear model
X_train_normalized = np.concatenate([np.ones((X_train_normalized.shape[0], 1)), X_train_normalized], axis=1)

# Define the function to calculate Ridge Regression weights
def calculate_ridge_weights(X, y, lambd):
    identity_matrix = np.eye(X.shape[1])
    # Apply regularization to all except the intercept term
    identity_matrix[0, 0] = 0
    ridge_weights = np.linalg.inv(X.T.dot(X) + lambd * identity_matrix).dot(X.T).dot(y)
    return ridge_weights

# Regularization parameters
lambdas = [10, 100, 200]

# Calculate weights for each value of lambda
ridge_weights_dict = {lambd: calculate_ridge_weights(X_train_normalized, y_train, lambd) for lambd in lambdas}

# Print the results with labels
for lambd, weights in ridge_weights_dict.items():
    print(f"For λ={lambd}:\n")
    print("    Bias (Intercept): {:.4f}".format(weights[0]))
    for i, weight in enumerate(weights[1:], start=1):
        print(f"    {training_set.columns[i-1]}: {weight:.4f}")
    print("\n")

