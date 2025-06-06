#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    bool isMatch(std::string s, std::string p) {
        int n = s.size();
        int m = p.size();
        std::vector<std::vector<bool>> match(n + 1, std::vector<bool>(m + 1, false));

        match[0][0] = true;

        for (int i = 0; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j - 1] == '*') {
                    match[i][j] = match[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && match[i - 1][j]);
                } else {
                    match[i][j] = i > 0 && match[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }

        return match[n][m];
    }
};

int main() {
    Solution solution;

    std::cout << solution.isMatch("aa", "a") << std::endl;

    std::cout << solution.isMatch("aa", "a*") << std::endl;

    std::cout << solution.isMatch("ab", ".*") << std::endl;

    return 0;
}