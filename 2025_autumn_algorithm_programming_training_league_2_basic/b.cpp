#include <iostream>
#include <string>

int main() {
    int len;
    std::string str;
    std::cin >> len >> str;
    int num_of_sixes = 0;
    int num_of_ones = 0;
    for (const char letter : str) {
        if (letter == '1') {
            ++num_of_ones;
        } else if (letter == '6') {
            ++num_of_sixes;
        }
    }
    std::cout << (num_of_sixes == 0 ? 0 : std::min(num_of_sixes - 1, num_of_ones)) << '\n';

    return 0;
}