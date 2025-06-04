#include <iostream>
#include <string>

// 给定一个字符串 s 和一个整数 k，要求构造一个字符串 t，使得：
// s 在 t 中恰好出现 k 次（作为子串，不是子序列）；
// t 的长度尽可能短；
// 返回任意一个满足条件的最短字符串 t。

int main() {
    std::string s;
    int k;

    std::cin >> s >> k;

    int n = s.size();
    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        pi[i] = j;
    }

    int overlap_len = pi[n - 1];
    std::string suffix = s.substr(overlap_len);
    std::string res = s;

    for (int i = 1; i < k; ++i) {
        res += suffix;
    }

    std::cout << res << std::endl;

    return 0;
}