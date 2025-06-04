#include <iostream>
#include <string>

// 描述
// 小红拿到了一个01串，她每次可以选择一个长度为2的连续子串取反（0变1，1变0），她想知道，是否能在有限的操作次数内使得所有字符相同？
// 共有
// q
// q组询问。
// 输入描述：
// 第一行输入一个正整数
// q
// q，代表询问次数。
// 每次询问输入一个字符串，仅由'0'和'1'组成。
// 所有字符串长度之和不超过200000。
// 输出描述：
// 对于每次询问，如果该字符串可以通过有限的操作使得所有字符相同，则输出"Yes"，否则输出"No"。

int main() {
    int q;

    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        std::string s;

        std::cin >> s;

        int count_one = 0;
        int count_zero = 0;

        for (char c : s) {
            if (c == '1') {
                count_one++;
            } else if (c == '0') {
                count_zero++;
            }
        }

        if (count_one % 2 == 0 || count_zero % 2 == 0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}