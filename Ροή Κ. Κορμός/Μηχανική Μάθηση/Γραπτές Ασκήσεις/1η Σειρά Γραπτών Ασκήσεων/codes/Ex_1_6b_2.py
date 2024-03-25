from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
import pandas as pd
from io import StringIO
import matplotlib.pyplot as plt

# For subquery 2, we need to compute optimal decision trees using gini and entropy criteria with a height of at most 2.

# Given data in the table format as shown in the image provided
data = """
x1,x2,x3,x4,y
1,0,1,0,1
0,1,0,1,1
1,0,1,0,1
1,0,1,1,1
0,1,0,0,1
1,0,1,1,-1
0,1,1,0,-1
0,0,0,0,-1
0,0,1,0,-1
1,0,0,0,-1
"""

# Read the data into a pandas DataFrame
df = pd.read_csv(StringIO(data))

# Splitting the data into features and target variable
X = df.drop('y', axis=1)
y = df['y']

# Initialize decision tree classifiers for gini and entropy with max_depth parameter set to 2
clf_gini_max2 = DecisionTreeClassifier(criterion='gini', max_depth=2)
clf_entropy_max2 = DecisionTreeClassifier(criterion='entropy', max_depth=2)

# Fit the models to the data
clf_gini_max2.fit(X, y)
clf_entropy_max2.fit(X, y)

# Predictions
y_pred_gini_max2 = clf_gini_max2.predict(X)
y_pred_entropy_max2 = clf_entropy_max2.predict(X)

# Accuracy scores for the constrained trees
accuracy_gini_max2 = accuracy_score(y, y_pred_gini_max2)
accuracy_entropy_max2 = accuracy_score(y, y_pred_entropy_max2)

# We will now visualize the trees with a maximum height of 2
plt.figure(figsize=(16, 8))
plt.subplot(1, 2, 1)
tree.plot_tree(clf_gini_max2, filled=True, feature_names=X.columns, class_names=['-1', '1'])
plt.title(f'Gini Criterion Decision Tree (Max Depth: 2, Accuracy: {accuracy_gini_max2:.2f})')

plt.subplot(1, 2, 2)
tree.plot_tree(clf_entropy_max2, filled=True, feature_names=X.columns, class_names=['-1', '1'])
plt.title(f'Entropy Criterion Decision Tree (Max Depth: 2, Accuracy: {accuracy_entropy_max2:.2f})')

plt.tight_layout()
plt.show()

(accuracy_gini_max2, accuracy_entropy_max2)
