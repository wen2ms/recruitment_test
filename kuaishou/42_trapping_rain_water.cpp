#include <iostream>
#include <vector>

class Solution {
  public:
    int trap(std::vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_left = height[left];
        int max_right = height[right];
        int water = 0;

        while (left < right) {
            if (max_left < max_right) {
                left++;
                max_left = std::max(max_left, height[left]);

                water += max_left - height[left];
            } else {
                right--;
                max_right = std::max(max_right, height[right]);

                water += max_right - height[right];
            }
        }

        return water;
    }
};

int main() {
    std::vector<int> case_1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::vector<int> case_2 = {4, 2, 0, 3, 2, 5};

    Solution solution;

    std::cout << solution.trap(case_1) << std::endl;

    std::cout << solution.trap(case_2) << std::endl;

    return 0;
}