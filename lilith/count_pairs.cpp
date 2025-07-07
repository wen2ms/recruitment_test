#include <algorithm>
#include <iostream>
#include <vector>

// 给定数组 arr 和一个值 k，要找满足 i < j 且 arr[i] + arr[j] <= k 的组合数。

class Solution {
  public:
    int count_pairs(std::vector<int>& arr, int k) {
        std::sort(arr.begin(), arr.end());

        int n = arr.size();
        int left = 0;
        int right = n - 1;
        int count = 0;

        while (left < right) {
            if (arr[left] + arr[right] <= k) {
                count += right - left;

                ++left;
            } else {
                --right;
            }
        }

        return count;
    }
};

int main() {
    std::vector<int> case_1 = {1, 2, 3, 4, 5};
    
    Solution solution;

    std::cout << solution.count_pairs(case_1, 6) << std::endl;

    return 0;
}