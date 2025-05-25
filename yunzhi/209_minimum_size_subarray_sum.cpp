#include <iostream>
#include <vector>

class Solution {
  public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int left = 0;
        int current_sum = 0;
        int n = nums.size();
        int minimum_length = n + 1;

        for (int right = 0; right < n; ++right) {
            current_sum += nums[right];

            while (current_sum >= target) {
                minimum_length = std::min(right - left + 1, minimum_length);

                current_sum -= nums[left];
                left++;
            }
        }

        return minimum_length == n + 1 ? 0 : minimum_length;
    }
};

int main() {
    std::vector<int> case_1 = {2, 3, 1, 2, 4, 3};
    std::vector<int> case_2 = {1, 4, 4};
    std::vector<int> case_3 = {1, 1, 1, 1, 1, 1, 1, 1};

    Solution solution;

    std::cout << solution.minSubArrayLen(7, case_1) << std::endl;

    std::cout << solution.minSubArrayLen(4, case_2) << std::endl;

    std::cout << solution.minSubArrayLen(11, case_3) << std::endl;

    return 0;
}