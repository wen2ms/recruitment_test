#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string longest_prefix;

        std::sort(strs.begin(), strs.end());

        int n = strs.size();

        std::string first = strs[0];
        std::string last = strs[n - 1];

        int min_len = std::min(first.size(), last.size());

        for (int i = 0; i < min_len; ++i) {
            if (first[i] != last[i]) {
                return longest_prefix;
            }

            longest_prefix += first[i];
        }

        return longest_prefix;
    }
};

int main() {
    std::vector<std::string> case_1 = {"flower", "flow", "flight"};
    std::vector<std::string> case_2 = {"dog", "racecar", "car"};

    Solution solution;

    std::cout << solution.longestCommonPrefix(case_1) << std::endl;

    std::cout << solution.longestCommonPrefix(case_2) << std::endl;

    return 0;
}