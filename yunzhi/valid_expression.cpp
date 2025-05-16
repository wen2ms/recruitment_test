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

int parse_number(const std::string& s, int start, bool allow_negative, bool& ended_with_single_zero) {
    if (start >= s.size()) {
        return -1;
    }

    if (allow_negative && s[start] == '-') {
        start++;
        if (start >= s.size() || !isdigit(s[start])) {
            return -1;
        }
    } else if (!isdigit(s[start])) {
        return -1;
    }

    int end = start;
    while (end < s.size() && isdigit(s[end])) {
        end++;
    }

    if (end - start > 1 && s[start] == '0') {
        ended_with_single_zero = true;
        return start + 1;
    }

    return end;
}

int main() {
    std::string s;

    std::cin >> s;

    int i = 0;
    int last_valid = 0;
    bool ended_with_single_zero = false;

    int next = parse_number(s, i, true, ended_with_single_zero);
    if (next == -1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    last_valid = next;
    if (ended_with_single_zero) {
        std::cout << last_valid << std::endl;
        return 0;
    }

    i = next;
    while (i < s.size()) {
        if (s[i] != '+' && s[i] != '-') {
            break;
        }

        i++;

        ended_with_single_zero = false;
        next = parse_number(s, i, false, ended_with_single_zero);
        if (next == -1) {
            break;
        }

        last_valid = next;
        if (ended_with_single_zero) {
            break;
        }

        i = next;
    }

    std::cout << last_valid << std::endl;

    return 0;
}