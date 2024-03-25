from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
import pandas as pd
from io import StringIO
import matplotlib.pyplot as plt

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

# Initialize decision tree classifiers for gini and entropy
clf_gini = DecisionTreeClassifier(criterion='gini')
clf_entropy = DecisionTreeClassifier(criterion='entropy')

# Splitting the data into features and target variable
X = df.drop('y', axis=1)
y = df['y']

# Fit the models to the data
clf_gini.fit(X, y)
clf_entropy.fit(X, y)

# Predictions
y_pred_gini = clf_gini.predict(X)
y_pred_entropy = clf_entropy.predict(X)

# Accuracy scores
accuracy_gini = accuracy_score(y, y_pred_gini)
accuracy_entropy = accuracy_score(y, y_pred_entropy)

# We will now visualize the trees
plt.figure(figsize=(16, 8))
plt.subplot(1, 2, 1)
tree.plot_tree(clf_gini, filled=True, feature_names=X.columns, class_names=['-1', '1'])
plt.title(f'Decision Tree using Gini (Accuracy: {accuracy_gini:.2f})')

plt.subplot(1, 2, 2)
tree.plot_tree(clf_entropy, filled=True, feature_names=X.columns, class_names=['-1', '1'])
plt.title(f'Decision Tree using Entropy (Accuracy: {accuracy_entropy:.2f})')

plt.tight_layout()
plt.show()

(accuracy_gini, accuracy_entropy)
