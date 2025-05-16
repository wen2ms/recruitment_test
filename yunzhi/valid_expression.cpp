#include <iostream>
#include <ctype.h>

// 合法计算式
// 输入一个只含有 '+'、'-' 和数字的字符串， 求从第 1 个字符开始组成的最大合法计算式的长度。
// 例如，
// 输入：+348-234
// 输出：0
// 解释：从首个字符开始无合法计算式。
// 输入：2+072
// 输出：1
// 解释：合法计算式为 2（ 072 不合法）。
// 输入：234-+21
// 输出：3

int prase_number(const std::string& s, int start) {
    if (start >= s.size() || !isdigit(s[start])) {
        return -1;
    }

    int end = start;
    while (end < s.size() && isdigit(s[end])) {
        end++;
    }

    if (end - start > 1 && s[start] == '0') {
        return -1;
    }

    return end;
}

int main() {
    std::string s;

    std::cin >> s;

    int i = 0;
    int last_valid = 0;

    int next = prase_number(s, i);
    if (next == -1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    last_valid = next;
    i = next;

    while (i < s.size()) {
        if (s[i] != '+' && s[i] != '-') {
            break;
        }

        i++;

        next = prase_number(s, i);
        if (next == -1) {
            break;
        }

        last_valid = next;
        i = next;
    }

    std::cout << last_valid << std::endl;

    return 0;
}