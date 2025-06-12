#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    int subarraySum(std::vector<int>& nums, int k) {
        int n = nums.size();
        int sum = 0;

        int total_subarrays = 0;
        std::unordered_map<int, int> prefix_count_map;

        prefix_count_map[0] = 1;

        for (int i = 0; i < n; ++i) {
            sum += nums[i];

            auto it = prefix_count_map.find(sum - k);
            if (it != prefix_count_map.end()) {
                total_subarrays += it->second;
            }

            prefix_count_map[sum]++;
        }

        return total_subarrays;
    }
};

int main() {
    std::vector<int> case_1 = {1, 1, 1};
    std::vector<int> case_2 = {1, 2, 3};
    std::vector<int> case_3 = {1, 1, 1, -1, 1, -1};

    Solution solution;

    std::cout << solution.subarraySum(case_1, 2) << std::endl;
    std::cout << solution.subarraySum(case_2, 3) << std::endl;
    std::cout << solution.subarraySum(case_3, 2) << std::endl;

    return 0;
}