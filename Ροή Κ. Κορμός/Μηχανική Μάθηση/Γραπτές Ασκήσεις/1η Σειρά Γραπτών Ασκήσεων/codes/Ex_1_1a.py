import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# Step 1) Load the data
data_path = '\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\ML2023-24-hwk1.csv'  
data = pd.read_csv(data_path, delimiter=';')

# Step 2) Normalize the data manually
data_features = data.iloc[:, :-1]  # Exclude the target variable 'quality'
data_features_normalized = (data_features - data_features.mean()) / data_features.std()
data_features_normalized = pd.DataFrame(data_features_normalized, columns=data.columns[:-1])

# Step 3) Calculate the correlation coefficient between the 9th and 10th features and print the matrix
correlation_matrix_normalized = data_features_normalized.corr()
correlation_coefficient_normalized = correlation_matrix_normalized.iloc[8, 9]  # pH is the 9th, sulphates the 10th
print("Normalized Correlation Coefficient (pH and sulphates):", correlation_coefficient_normalized)
print("Correlation Matrix:\n", correlation_matrix_normalized)

# Step 4) The normalized correlation coefficient has been printed in Step 4.

# Step 5) Create and save the heatmap and scatter plot
# Heatmap
plt.figure(figsize=(12, 10))
sns.heatmap(correlation_matrix_normalized, annot=True, fmt=".2f", cmap='coolwarm', square=True)
heatmap_file_path = '\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\correlation_heatmap.png'  # Replace with your actual file path
plt.savefig(heatmap_file_path)
plt.close()

# Scatter plot for pH and sulphates
plt.figure(figsize=(6, 6))
sns.scatterplot(data=data_features_normalized, x='pH', y='sulphates')
scatterplot_file_path = '\\code\\pythonProjects\\myvenv\\Shmmy\\Machine_Learning_1st\\ph_sulphates_scatterplot.png'  # Replace with your actual file path
plt.savefig(scatterplot_file_path)
plt.close()
