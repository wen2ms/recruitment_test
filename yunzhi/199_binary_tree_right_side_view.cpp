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

TreeNode* construct_binary_tree(const std::vector<int>& nodes_vec) {
    if (nodes_vec.empty() || nodes_vec[0] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes_vec[0]);
    std::queue<TreeNode*> nodes_queue;

    nodes_queue.push(root);

    int i = 1;
    while (!nodes_queue.empty() && i < nodes_vec.size()) {
        TreeNode* current_node = nodes_queue.front();
        nodes_queue.pop();

        if (nodes_vec[i] != -1) {
            current_node->left = new TreeNode(nodes_vec[i]);
            nodes_queue.push(current_node->left);
        }
        ++i;

        if (i < nodes_vec.size() && nodes_vec[i] != -1) {
            current_node->right = new TreeNode(nodes_vec[i]);
            nodes_queue.push(current_node->right);
        }
        ++i;
    }

    return root;
}

std::vector<int> right_side_view(TreeNode* root) {
    std::vector<int> right_side_nodes;

    if (root == nullptr) {
        return right_side_nodes;
    }

    std::queue<TreeNode*> nodes_queue;

    nodes_queue.push(root);
    while (!nodes_queue.empty()) {
        int level_nodes_count = nodes_queue.size();

        for (int i = 0; i < level_nodes_count; ++i) {
            TreeNode* current_node = nodes_queue.front();
            nodes_queue.pop();

            if (current_node->left != nullptr) {
                nodes_queue.push(current_node->left);
            }

            if (current_node->right != nullptr) {
                nodes_queue.push(current_node->right);
            }

            if (i == level_nodes_count - 1) {
                right_side_nodes.push_back(current_node->val);
            }
        }
    }

    return right_side_nodes;
}

auto print_vec = [](const std::vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
};

int main() {
    TreeNode* case_1 = construct_binary_tree({1, 2, 3, -1, 5, -1, 4});
    TreeNode* case_2 = construct_binary_tree({1, 2, 3, 4, -1, -1, -1, 5});
    TreeNode* case_3 = construct_binary_tree({1, -1, 3});
    TreeNode* case_4 = construct_binary_tree({});

    print_vec(right_side_view(case_1));

    print_vec(right_side_view(case_2));

    print_vec(right_side_view(case_3));

    print_vec(right_side_view(case_4));

    return 0;
}