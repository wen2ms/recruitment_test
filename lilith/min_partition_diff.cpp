#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

// 给定一个环形数组，找到一个连续区间（子数组），使得它和剩余元素的和差的绝对值最小。

class Solution {
  public:
    int minPartitionDiff(std::vector<int>& arr) {
        int n = arr.size();
        int total_sum = std::accumulate(arr.begin(), arr.end(), 0);
        std::vector<int> arr2(2 * n);

        for (int i = 0; i < 2 * n; ++i) {
            arr2[i] = arr[i % n];
        }

        std::vector<int> prefix_sum(2 * n + 1);

        for (int i = 0; i < 2 * n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + arr2[i];
        }

        int min_diff = std::numeric_limits<int>::max();

        for (int length = 1; length < n; ++length) {
            for (int start = 0; start < n; ++start) {
                int sub_sum = prefix_sum[start + length] - prefix_sum[start];
                int diff = std::abs(2 * sub_sum - total_sum);

                min_diff = std::min(min_diff, diff);
            }
        }

        return min_diff;
    }
};

int main() {
    std::vector<int> case_1 = {1, 2, 3, 4, 5};

    Solution solution;

    std::cout << solution.minPartitionDiff(case_1) << std::endl;

    return 0;
}