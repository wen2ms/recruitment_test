#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

class Solution {
  public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        std::vector<int> min_len(n, std::numeric_limits<int>::max());
        int current_minimum_len = std::numeric_limits<int>::max();

        int i = 0, sum = 0;
        int res = std::numeric_limits<int>::max();

        for (int j = 0; j < n; ++j) {
            sum += arr[j];

            while (sum > target) {
                sum -= arr[i];

                ++i;
            }

            if (sum == target) {
                int curr_len = j - i + 1;

                if (i > 0 && min_len[i - 1] != std::numeric_limits<int>::max()) {
                    res = std::min(res, min_len[i - 1] + curr_len);
                }

                current_minimum_len = std::min(current_minimum_len, curr_len); 
            }

            min_len[j] = current_minimum_len; 
        }

        return res == std::numeric_limits<int>::max() ? -1 : res;
    }
};

int main() {
    std::vector<int> case_1 = {3, 2, 2, 4, 3};
    std::vector<int> case_2 = {7, 3, 4, 7};
    std::vector<int> case_3 = {4, 3, 2, 6, 2, 3, 4};

    Solution solution;

    std::cout << solution.minSumOfLengths(case_1, 3) << std::endl;

    std::cout << solution.minSumOfLengths(case_2, 7) << std::endl;

    std::cout << solution.minSumOfLengths(case_3, 6) << std::endl;

    return 0;
}