#include <iostream>
#include <string>

// 统计一个子串在一个字符串中出现的次数
// 字符串：abababab
// 子串：aba
// 出现次数：3

int main() {
    std::string str, sub_string;

    std::cin >> str >> sub_string;

    int m = sub_string.size();
    std::vector<int> pi(m, 0);

    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];

        while (j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }

        if (str[i] == str[j]) {
            ++j;
        }

        pi[i] = j;
    }

    int count = 0;
    int n = str.size();
    int j = 0;

    for (int i = 0; i < n; ++i) {
        while (j > 0 && str[i] != sub_string[j]) {
            j = pi[j - 1];
        }

        if (str[i] == sub_string[j]) {
            ++j;
        }

        if (j == m) {
            count++;
            j = pi[j - 1];
        }
    }

    std::cout << count << std::endl;

    return 0;
}