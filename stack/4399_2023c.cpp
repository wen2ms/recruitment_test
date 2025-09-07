#include <iostream>
#include <stack>
#include <string>

int GetBraceMatchCount(const std::string& str) {
    std::stack<int> stack;
    int match_count = 0;
    int len = str.length();

    int index = 0;
    while (index < len) {
        char letter = str[index];
        if (letter == '{') {
            int count = 0;
            while (index < len && str[index] == '{') {
                ++count;
                ++index;
            }
            stack.push(count);
        } else if (letter == '}') {
            int count = 0;
            while (index < len && str[index] == '}') {
                ++count;
                ++index;
            }
            if (!stack.empty() && stack.top() == count) {
                stack.pop();
                ++match_count;
            } else {
                break;
            }
        } else {
            ++index;
        }
    }
    return match_count;
}

int main() {
    std::cout << GetBraceMatchCount("aabbcc") << '\n';
    std::cout << GetBraceMatchCount("{aa{{bb}cc}}") << '\n';
    std::cout << GetBraceMatchCount("{aa{{bb}}cc") << '\n';
    std::cout << GetBraceMatchCount("{aa{{bb}}cc}") << '\n';
    std::cout << GetBraceMatchCount("aa}bb{cc") << '\n';
    std::cout << GetBraceMatchCount("aa{bb}cc") << '\n';
    std::cout << GetBraceMatchCount("aa{{bb}cc}") << '\n';
    std::cout << GetBraceMatchCount("aa{{bb}}cc") << '\n';

    return 0;
}