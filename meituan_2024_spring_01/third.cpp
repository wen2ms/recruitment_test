#include <iostream>
#include <string>

int main() {
    int n, k;
    std::string input_string;

    std::cin >> n >> k >> input_string;

    int count = 0;
    for (auto& letter : input_string) {
        if (letter != 'M' && letter != 'T' && k > 0) {
            ++count;
            --k;
        } else if (letter == 'M' || letter == 'T') {
            ++count;
        }
    }

    std::cout << count << std::endl;

    return 0;
}