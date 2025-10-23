#include <array>
#include <cstdint>
#include <iostream>

int main() {
    std::array<int64_t, 3> player1;
    std::array<int64_t, 3> player2;
    for (int64_t& count : player1) {
        std::cin >> count;
    }
    for (int64_t& count : player2) {
        std::cin >> count;
    }
    int64_t result = std::min(player1[0], player2[1]) + std::min(player1[1], player2[2]) + std::min(player1[2], player2[0]);
    std::cout << result << '\n';

    return 0;
}