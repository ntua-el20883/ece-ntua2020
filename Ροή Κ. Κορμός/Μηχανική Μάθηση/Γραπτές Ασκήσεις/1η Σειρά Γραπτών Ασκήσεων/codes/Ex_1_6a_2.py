from sklearn import tree
import matplotlib.pyplot as plt
import numpy as np

# Generating a dataset for the function fn: (x1 AND x2) XOR (x3 AND NOT x4)
# Each feature can be either 0 (false) or 1 (true)
X = np.array([[0, 0, 0, 0],
              [0, 0, 0, 1],
              [0, 0, 1, 0],
              [0, 0, 1, 1],
              [0, 1, 0, 0],
              [0, 1, 0, 1],
              [0, 1, 1, 0],
              [0, 1, 1, 1],
              [1, 0, 0, 0],
              [1, 0, 0, 1],
              [1, 0, 1, 0],
              [1, 0, 1, 1],
              [1, 1, 0, 0],
              [1, 1, 0, 1],
              [1, 1, 1, 0],
              [1, 1, 1, 1]])

# Labels based on the fn: (x1 AND x2) XOR (x3 AND NOT x4)
Y_xor = (X[:, 0] & X[:, 1]) != (X[:, 2] & ~X[:, 3])

# Create and train the decision tree classifier
clf_xor = tree.DecisionTreeClassifier()
clf_xor = clf_xor.fit(X, Y_xor)

# Plotting the tree
plt.figure(figsize=(12,8))
tree.plot_tree(clf_xor, filled=True, feature_names=['x1', 'x2', 'x3', 'x4'], class_names=['False', 'True'])
plt.show()
