import numpy as np
import pandas as pd

# Step 1: Load the data and split into training and verification sets
data = pd.read_csv('\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\ML2023-24-hwk1.csv', delimiter=';')
training_set = data.iloc[:100, :]
verification_set = data.iloc[100:150, :]

# Extract features and target variable for the training set
X_train = training_set.iloc[:, :-1].values  # all columns except the last one
y_train = training_set.iloc[:, -1].values  # the last column

# Add a column of ones to the features to account for the bias (intercept) in the linear model
X_train = np.concatenate([np.ones((X_train.shape[0], 1)), X_train], axis=1)

# Step 2: Calculate the weights using the normal equation
weights = np.linalg.inv(X_train.T @ X_train) @ X_train.T @ y_train

# Print the name of each weight along with its value
feature_names = list(training_set.columns)[:-1]  # Get the feature names excluding the target variable

# Make sure the lengths match or use the shorter length
min_length = min(len(feature_names), len(weights))

for i in range(min_length):
    print(f"{feature_names[i]}: {weights[i]}")
