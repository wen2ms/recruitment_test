#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;

    std::cin >> n;

    std::vector<int> input_nubmers(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> input_nubmers[i];
    }

    int operation_count = 0;

    std::sort(input_nubmers.begin(), input_nubmers.end());

    for (int i = 0; i < n; ++i) {
        if (input_nubmers[i] <= 0) {
            operation_count += i + 1 - input_nubmers[i];

        } else {
            operation_count += std::abs(input_nubmers[i] - i - 1);
        }
    }

    std::cout << operation_count << std::endl;

    return 0;
}