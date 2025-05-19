#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(0), left(left), right(right) {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* construct_binary_tree(const std::vector<int>& tree_nodes) {
    if (tree_nodes.empty() || tree_nodes[0] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(tree_nodes[0]);

    std::queue<TreeNode*> nodes_queue;

    nodes_queue.push(root);

    int i = 1;
    while (!nodes_queue.empty() && i < tree_nodes.size()) {
        TreeNode* current_node = nodes_queue.front();
        nodes_queue.pop();

        if (tree_nodes[i] != -1) {
            current_node->left = new TreeNode(tree_nodes[i]);

            nodes_queue.push(current_node->left);
        }
        ++i;

        if (i < tree_nodes.size() && tree_nodes[i] != -1) {
            current_node->right = new TreeNode(tree_nodes[i]);

            nodes_queue.push(current_node->right);
        }
        ++i;
    }

    return root;
}

void postorder_traversal(const TreeNode* root, std::vector<int>& postorder_nodes) {
    if (root == nullptr) {
        return;
    }

    postorder_traversal(root->left, postorder_nodes);
    postorder_traversal(root->right, postorder_nodes);

    postorder_nodes.push_back(root->val);
}

int main() {
    TreeNode* case_1_root = construct_binary_tree({1, 2, 3, 4, 5});
    std::vector<int> case_1_vec;

    TreeNode* case_2_root = construct_binary_tree({1, 2, 3, -1, 4, 5, 6});
    std::vector<int> case_2_vec;

    postorder_traversal(case_1_root, case_1_vec);
    std::for_each(case_1_vec.begin(), case_1_vec.end(), [](int val) {
        std::cout << val << ' ';
    });
    std::cout << std::endl;

    postorder_traversal(case_2_root, case_2_vec);
    std::for_each(case_2_vec.begin(), case_2_vec.end(), [](int val) {
        std::cout << val << ' ';
    });
    std::cout << std::endl;

    return 0;
}