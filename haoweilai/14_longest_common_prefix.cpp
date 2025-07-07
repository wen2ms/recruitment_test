#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::string longest_prefix;
        int n = strs.size();

        std::sort(strs.begin(), strs.end());

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