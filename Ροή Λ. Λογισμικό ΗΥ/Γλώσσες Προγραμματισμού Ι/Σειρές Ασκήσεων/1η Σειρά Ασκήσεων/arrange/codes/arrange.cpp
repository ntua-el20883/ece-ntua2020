#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void parseTree(TreeNode* &node, istringstream &iss) {
    int value;
    if (!(iss >> value)) return;
    if (value == 0) {
        node = nullptr;
    } else {
        node = new TreeNode(value);
        parseTree(node->left, iss);
        parseTree(node->right, iss);
    }
}

void inOrderTraversal(TreeNode* node, vector<int>& result) {
    if (!node) return;

    // Vectors to compare in-order traversal outcomes with and without swaps
    vector<int> left, right;
    inOrderTraversal(node->left, left);
    inOrderTraversal(node->right, right);

    // Compare scenarios: no swap vs swap
    vector<int> normal_order, swapped_order;
    normal_order.insert(normal_order.end(), left.begin(), left.end());
    normal_order.push_back(node->val);
    normal_order.insert(normal_order.end(), right.begin(), right.end());

    swapped_order.insert(swapped_order.end(), right.begin(), right.end());
    swapped_order.push_back(node->val);
    swapped_order.insert(swapped_order.end(), left.begin(), left.end());

    // Choose the lexicographically smaller one
    if (lexicographical_compare(normal_order.begin(), normal_order.end(), swapped_order.begin(), swapped_order.end())) {
        result.insert(result.end(), normal_order.begin(), normal_order.end());
    } else {
        result.insert(result.end(), swapped_order.begin(), swapped_order.end());
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./arrange <filename>" << endl;
        return 1;
    }
    
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Failed to open file: " << argv[1] << endl;
        return 1;
    }
    
    int N;
    file >> N;
    string treeData;
    getline(file, treeData); // Skip to the end of the first line
    getline(file, treeData); // Read the tree data line
    
    TreeNode* root = nullptr;
    istringstream iss(treeData);
    parseTree(root, iss);
    
    vector<int> result;
    inOrderTraversal(root, result);
    
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
    
    return 0;
}
