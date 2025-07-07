#include <climits>
#include <iostream>
#include <vector>

class Solution {
  public:
    int maxProduct(std::vector<int>& nums) {
        int n = nums.size();
        int maximum = std::numeric_limits<int>::min();
        int product = 1;

        for (int i = 0; i < n; ++i) {
            product *= nums[i];

            maximum = std::max(product, maximum);
            if (product == 0) {
                product = 1;
            }
        }

        product = 1;
        for (int i = n - 1; i >= 0; --i) {
            product *= nums[i];

            maximum = std::max(product, maximum);
            if (product == 0) {
                product = 1;
            }
        }

        return maximum;
    }
};

int main() {
    std::vector<int> case_1 = {2, 3, -2, 4};
    std::vector<int> case_2 = {-2, 0, -1};
    std::vector<int> case_3 = {-2, 3, 2, -2};

    Solution solution;

    std::cout << solution.maxProduct(case_1) << std::endl;

    std::cout << solution.maxProduct(case_2) << std::endl;

    std::cout << solution.maxProduct(case_3) << std::endl;

    return 0;
}