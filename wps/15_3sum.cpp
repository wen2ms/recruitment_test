#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<std::vector<int>> triplets;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum > 0) {
                    k--;
                } else if (sum < 0) {
                    j++;
                } else {
                    triplets.push_back({nums[i], nums[j], nums[k]});
                    j++;

                    while (j < k && nums[j] == nums[j - 1]) {
                        j++;
                    }
                }
            }
        }

        return triplets;
    }
};

class PrintNums {
  public:
    void operator()(const std::vector<std::vector<int>>& nums_vec) {
        for (std::vector<int> nums : nums_vec) {
            for (int num : nums) {
                std::cout << num << ' ';
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::vector<int> case_1 = {-1, 0, 1, 2, -1, -4};
    std::vector<int> case_2 = {0, 1, 1};
    std::vector<int> case_3 = {0, 0, 0};

    Solution solution;
    PrintNums print_nums;

    print_nums(solution.threeSum(case_1));
    std::cout << std::endl;

    print_nums(solution.threeSum(case_2));
    std::cout << std::endl;

    print_nums(solution.threeSum(case_3));
    std::cout << std::endl;

    return 0;
}