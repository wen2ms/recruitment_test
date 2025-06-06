#include <iostream>
#include <string>
#include <vector>

// "abc" 是一个合法的基本单元；
// 如果 s 是合法字符串，则：
// s = x + y（两个合法串拼接）也是合法；
// s = x + "abc" + y 也是合法（注意这里强调的是 "abc" 可以插入到任意合法字符串的中间位置）。

int main() {
    std::string str;

    std::cin >> str;

    std::vector<char> expression;

    for (char ch : str) {
        expression.push_back(ch);

        int size = expression.size();
        if (size >= 3 && expression[size - 3] == 'a' && expression[size - 2] == 'b' && expression[size - 1] == 'c') {
            expression.pop_back();
            expression.pop_back();
            expression.pop_back();
        }
    }

    std::cout << expression.empty() << std::endl;

    return 0;
}
