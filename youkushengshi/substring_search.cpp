#include <iostream>
#include <string>

// 统计一个子串在一个字符串中出现的次数
// 字符串：abababab
// 子串：aba
// 出现次数：3

int main() {
    std::string str, sub_string;

    std::cin >> str >> sub_string;

    int count = 0;
    int pos = 0;
    while ((pos = str.find(sub_string, pos)) != std::string::npos) {
        count++;
        pos++;
    }

    std::cout << count << std::endl;

    return 0;
}