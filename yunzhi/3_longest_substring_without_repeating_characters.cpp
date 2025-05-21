#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int lengthOfLongestSubstring(std::string s) {
        int n = s.size();
        int longest_length = 0;
        std::unordered_set<char> char_set;
        int start = 0;

        for (int end = 0; end < n; ++end) {
            if (char_set.find(s[end]) == char_set.end()) {
                char_set.insert(s[end]);
                longest_length = std::max(longest_length, end - start + 1);
            } else {
                while (char_set.find(s[end]) != char_set.end()) {
                    char_set.erase(s[start]);
                    ++start;
                }

                char_set.insert(s[end]);
            }
        }

        return longest_length;
    }
};

int main() {
    std::string case_1 = "abcabcbb";
    std::string case_2 = "bbbbb";
    std::string case_3 = "pwwkew";

    Solution solution;

    std::cout << solution.lengthOfLongestSubstring(case_1) << std::endl;

    std::cout << solution.lengthOfLongestSubstring(case_2) << std::endl;

    std::cout << solution.lengthOfLongestSubstring(case_3) << std::endl;

    return 0;
}