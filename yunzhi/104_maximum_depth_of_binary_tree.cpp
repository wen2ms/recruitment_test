#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* construct_binary_tree(const std::vector<int>& nodes_values) {
    if (nodes_values.empty() || nodes_values[0] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes_values[0]);
    std::queue<TreeNode*> nodes_queue;

    nodes_queue.push(root);

    int i = 1;
    while (!nodes_queue.empty() && i < nodes_values.size()) {
        TreeNode* current_node = nodes_queue.front();
        nodes_queue.pop();

        if (nodes_values[i] != -1) {
            current_node->left = new TreeNode(nodes_values[i]);
            nodes_queue.push(current_node->left);
        }
        ++i;

        if (i < nodes_values.size() && nodes_values[i] != -1) {
            current_node->right = new TreeNode(nodes_values[i]);
            nodes_queue.push(current_node->right);
        }
        ++i;
    }

    return root;
}

int max_depth(TreeNode* root) {
    int maximum_depth = 0;

    if (root == nullptr) {
        return maximum_depth;
    }

    std::queue<TreeNode*> nodes_queue;

    nodes_queue.push(root);
    
    while (!nodes_queue.empty()) {
        int current_level_count = nodes_queue.size();

        for (int i = 0; i < current_level_count; ++i) {
            TreeNode* current_node = nodes_queue.front();
            nodes_queue.pop();

            if (current_node->left != nullptr) {
                nodes_queue.push(current_node->left);
            }

            if (current_node->right != nullptr) {
                nodes_queue.push(current_node->right);
            }
        }

        ++maximum_depth;
    }

    return maximum_depth;
}

int main() {
    TreeNode* case_1 = construct_binary_tree({3, 9, 20, -1, -1, 15, 7});
    TreeNode* case_2 = construct_binary_tree({1, -1, 2});

    std::cout << max_depth(case_1) << std::endl;

    std::cout << max_depth(case_2) << std::endl;

    return 0;
}