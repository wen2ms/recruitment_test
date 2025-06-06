#include <iostream>
#include <unordered_map>
#include <string>

// 一个01字符串，求出现0、1出现次数相等的最长子串长度

int main() {
    std::string str;

    std::cin >> str;

    int longest_len = -1;
    std::unordered_map<int, int> count_index_map;

    count_index_map[0] = -1;
    
    int count = 0;

    for (int i = 0; i < str.length(); ++i) {
        count += (str[i] == '1') ? 1 : -1;

        auto it = count_index_map.find(count);
        if (it != count_index_map.end()) {
            longest_len = std::max(longest_len, i - it->second);
        } else {
            count_index_map.insert(std::pair(count, i));
        }
    }

    std::cout << longest_len << std::endl;

    return 0;
}