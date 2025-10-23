#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    int num_of_points;
    std::cin >> num_of_points;
    std::vector<std::pair<int, int>> points(num_of_points);
    for (auto& [first, second] : points) {
        std::cin >> first >> second;
    }
    int result = 0;
    for (int i = 0; i < num_of_points; ++i) {
        for (int j = 0; j < num_of_points; ++j) {
            if (j == i) {
                continue;
            }
            for (int k = j + 1; k < num_of_points; ++k) {
                if (k == i) {
                    continue;
                }
                std::pair<int64_t, int64_t> side1 = {points[j].first - points[i].first, points[j].second - points[i].second};
                std::pair<int64_t, int64_t> side2 = {points[k].first - points[i].first, points[k].second - points[i].second};
                int64_t product = side1.first * side2.first + side1.second * side2.second;
                int64_t sum = (side1.first * side1.first + side1.second * side1.second) *
                              (side2.first * side2.first + side2.second * side2.second);
                if (product < 0 && product * product < sum) {
                    ++result;
                }
            }
        }
    }
    std::cout << result << '\n';

    return 0;
}