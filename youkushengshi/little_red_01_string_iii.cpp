#include <iostream>
#include <vector>

// 小红定义一个字符串是好串，当且仅当该字符串任意一对相邻字符都不同。
// 现在小红拿到了一个01串，请你帮小红求出有多少个长度不小于2的连续子串是好串。

int main() {
    std::string s;

    std::cin >> s;

    long long total = 0;
    long long res = 0;

    for (int i = 1; i < s.length(); ++i) {
        if (s[i] != s[i - 1]) {
            total++;
            res += total;
        } else {
            total = 0;
        }
    }

    std::cout << res << std::endl;

    return 0;
}