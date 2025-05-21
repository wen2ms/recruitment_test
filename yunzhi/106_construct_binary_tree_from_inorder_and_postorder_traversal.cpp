#include <iostream>
#include <vector>
#include <map>

struct TreeNode {
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(0), left(left), right(right) {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

void dfs(const TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->val << ' ';

    dfs(root->left);

    dfs(root->right);
}

class Solution {
  public:
    TreeNode* buildTree(const std::vector<int>& inorder, const std::vector<int>& postorder) {
        int n = inorder.size();
        postorder_index_ = n - 1;

        for (int i = 0; i < n; ++i) {
            inorder_map_.insert(std::make_pair(inorder[i], i));
        }

        return inorder_and_postorder_traversal(postorder, 0, n - 1);
    }

  private:
    TreeNode* inorder_and_postorder_traversal(const std::vector<int>& postorder, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(postorder[postorder_index_]);
        --postorder_index_;

        int inorder_index = inorder_map_[root->val];

        root->right = inorder_and_postorder_traversal(postorder, inorder_index + 1, end);

        root->left = inorder_and_postorder_traversal(postorder, start, inorder_index - 1);

        return root;
    }

    std::unordered_map<int, int> inorder_map_;
    int postorder_index_;
};

int main() {
    std::vector<int> case_1_inorder = {9,3,15,20,7};
    std::vector<int> case_1_postorder = {9,15,7,20,3};

    std::vector<int> case_2_inorder = {-1};
    std::vector<int> case_2_postorder = {-1};

    Solution solution_1, solution_2;

    dfs(solution_1.buildTree(case_1_inorder, case_1_postorder));

    std::cout << std::endl;

    dfs(solution_1.buildTree(case_2_inorder, case_2_postorder));

    std::cout << std::endl;

    return 0;
}