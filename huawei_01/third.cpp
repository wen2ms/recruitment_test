#include <iostream>
#include <string>
#include <cmath>

int main() {
    std::string hexadecimal;

    std::cin >> hexadecimal;

    int decimal = 0;
    for (int i = hexadecimal.size() - 1, j = 0; i >= 2; --i, ++j) {
        int base;

        if (hexadecimal[i] >= 'A' && hexadecimal[i] <= 'F') {
            base = hexadecimal[i] - 'A' + 10;
        } else if (hexadecimal[i] >= '0' && hexadecimal[i] <= '9') {
            base = hexadecimal[i] - '0';
        }

        decimal += base * pow(16, j);
    }

    std::cout << decimal << std::endl;

    return 0;
}