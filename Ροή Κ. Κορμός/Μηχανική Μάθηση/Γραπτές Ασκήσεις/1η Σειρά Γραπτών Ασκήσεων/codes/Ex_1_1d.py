import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Function to calculate linear regression weights
def linear_regression_weights(X, y):
    return np.linalg.inv(X.T.dot(X)).dot(X.T).dot(y)

# Function to calculate ridge regression weights
def ridge_regression_weights(X, y, lambd):
    identity_matrix = np.eye(X.shape[1])
    # Apply regularization to all except the intercept term
    identity_matrix[0, 0] = 0
    return np.linalg.inv(X.T.dot(X) + lambd * identity_matrix).dot(X.T).dot(y)

# Load the data and split into training and verification sets
data = pd.read_csv('\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\ML2023-24-hwk1.csv', delimiter=';')
training_set = data.iloc[:100, :]
verification_set = data.iloc[100:150, :]

# Extract features and target variable for the training set
X_train = training_set.iloc[:, :-1].values  # all columns except the last one
y_train = training_set.iloc[:, -1].values  # the last column

# Normalize the features of the training set
X_train_normalized = (X_train - np.mean(X_train, axis=0)) / np.std(X_train, axis=0)

# Add a column of ones to the features to account for the bias (intercept) in the linear model
X_train_normalized = np.hstack([np.ones((X_train_normalized.shape[0], 1)), X_train_normalized])

# Calculate linear regression weights
linear_weights = linear_regression_weights(X_train_normalized, y_train)

# Regularization parameters for ridge regression
lambdas = [10, 100, 200]

# Calculate ridge regression weights for each lambda
ridge_weights = {lambd: ridge_regression_weights(X_train_normalized, y_train, lambd) for lambd in lambdas}

# Collect all weights into one dictionary for plotting
all_weights = {'Linear': linear_weights}
all_weights.update(ridge_weights)

# Convert the dictionary of weights into a DataFrame for easy plotting
weights_df = pd.DataFrame(all_weights).T
feature_names = ['Bias'] + list(data.columns[:-1])  # Construct feature names list with 'Bias' and all feature names
weights_df.columns = feature_names

# Plotting the weights
plt.figure(figsize=(15, 10))

# Plot each set of weights
for method, weight_vector in weights_df.iterrows():
    plt.plot(weight_vector, label=method)

plt.title('Comparison of Weights: Linear vs Ridge Regression')
plt.xlabel('Features')
plt.ylabel('Weight Value')
plt.xticks(ticks=np.arange(len(feature_names)), labels=feature_names, rotation=45)
plt.legend()
plt.grid(True)

# Save the plot to a file
weights_comparison_file_path = '\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\weights_comparison_plot.png'
plt.savefig(weights_comparison_file_path)
plt.close()  # Close the plot to avoid displaying it in the notebook output

weights_comparison_file_path
