#include <iostream>
#include <vector>

int count_twos(long long x) {
    int count = 0;
    while (x % 2 == 0 && x > 0) {
        count++;
        x /= 2;
    }
    return count;
}

int count_fives(long long x) {
    int count = 0;
    while (x % 5 == 0 && x > 0) {
        count++;
        x /= 5;
    }
    return count;
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<long long> input_numbers(n + 1);
    std::vector<int> prefix_twos(n + 1, 0), prefix_fives(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        std::cin >> input_numbers[i];
        prefix_twos[i] = prefix_twos[i - 1] + count_twos(input_numbers[i]);
        prefix_fives[i] = prefix_fives[i - 1] + count_fives(input_numbers[i]);
    }

    long long plans_count = 0;

    int total_twos, total_fives;
    int left = 1;
    for (int right = 1; right <= n; ++right) {
        total_twos = prefix_twos[n] - prefix_twos[right] + prefix_twos[left - 1];
        total_fives = prefix_fives[n] - prefix_fives[right] + prefix_fives[left - 1];

        while (left <= right && std::min(total_twos, total_fives) < k) {
            ++left;

            total_twos = prefix_twos[n] - prefix_twos[right] + prefix_twos[left - 1];
            total_fives = prefix_fives[n] - prefix_fives[right] + prefix_fives[left - 1];
        }

        plans_count += right - left + 1;
    }

    std::cout << plans_count << std::endl;

    return 0;
}
