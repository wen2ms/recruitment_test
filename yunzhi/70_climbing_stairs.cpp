#include <iostream>
#include <vector>

int climb_stairs(int n) {
    if (n <= 3) {
        return n;
    }

    int prev1 = 2;
    int prev2 = 3;
    int current_total_ways = 0;

    for (int i = 3; i < n; ++i) {
        current_total_ways += prev1 + prev2;

        prev1 = prev2;
        prev2 = current_total_ways;
    }

    return current_total_ways;
}

int main() {
    std::cout << climb_stairs(2) << std::endl;

    std::cout << climb_stairs(4) << std::endl;

    return 0;
}