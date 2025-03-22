#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main() {
    std::string input_string;
    std::set<char> mirror_letters = {'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y'};

    std::cin >> input_string;

    int mirror_string_count = 0;

    for (int i = 0; i < input_string.size(); ++i) {
        for (int j = i + 1; j < input_string.size(); ++j) {
            std::string sub_str = input_string.substr(i, j - i + 1);

            int sub_str_size = sub_str.size();

            int k = 0, l = sub_str_size - 1;
            while (k <= l) {
                if (sub_str[k] != sub_str[l] || mirror_letters.find(sub_str[k]) == mirror_letters.end()
                || mirror_letters.find(sub_str[l]) == mirror_letters.end()) {
                    break;
                }

                ++k;
                --l;
            }

            if (k > l) {
                ++mirror_string_count;
            }
        }
    }

    std::cout << mirror_string_count << std::endl;

    return 0;
}