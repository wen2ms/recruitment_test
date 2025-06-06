#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Solution {
  public:
    bool wordPattern(std::string pattern, std::string s) {
        std::unordered_map<char, std::string> char_map;
        std::unordered_map<std::string, char> string_map;

        std::istringstream stream(s);
        std::string str;

        int i = 0;
        while (stream >> str) {
            if (i >= pattern.size()) {
                return false;
            }

            auto it_char = char_map.find(pattern[i]);

            if (it_char == char_map.end()) {
                char_map.insert(std::make_pair(pattern[i], str));
            } else {
                if (it_char->second != str) {
                    return false;
                }
            }

            auto it_string = string_map.find(str);

            if (it_string == string_map.end()) {
                string_map.insert(std::make_pair(str, pattern[i]));
            } else {
                if (it_string->second != pattern[i]) {
                    return false;
                }
            }

            ++i;
        }

        return i == pattern.size();
    }
};

int main() {
    Solution solution;

    std::cout << solution.wordPattern("abba", "dog cat cat dog") << std::endl;

    std::cout << solution.wordPattern("abba", "dog cat cat fish") << std::endl;

    std::cout << solution.wordPattern("aaaa", "dog cat cat dog") << std::endl;

    std::cout << solution.wordPattern("abba", "dog dog dog dog") << std::endl;

    std::cout << solution.wordPattern("aaa", "aa aa aa aa") << std::endl;

    return 0;
}