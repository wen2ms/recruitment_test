#include <iostream>
#include <vector>

class Solution {
  public:
    int longestMountain(std::vector<int>& arr) {
        int n = arr.size();
        int longest_length = 0;
        int up = 0;
        int down = 0;

        for (int i = 1; i < n; ++i) {
            if ((down > 0 && arr[i] > arr[i - 1]) || arr[i] == arr[i - 1]) {
                up = down = 0;
            }

            up += (arr[i] > arr[i - 1]);

            down += (arr[i] < arr[i - 1]);

            if (up > 0 && down > 0) {
                longest_length = std::max(longest_length, up + down + 1);
            }
        }

        return longest_length;
    }
};

int main() {
    std::vector<int> case_1 = {2, 1, 4, 7, 3, 2, 5};
    std::vector<int> case_2 = {2, 2, 2};

    Solution solution;

    std::cout << solution.longestMountain(case_1) << std::endl;

    std::cout << solution.longestMountain(case_2) << std::endl;

    return 0;
}