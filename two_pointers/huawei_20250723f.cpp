#include <iostream>
#include <vector>

int main() {
    int size;
    std::cin >> size;
    std::vector<int> heights(size);
    for (int& height : heights) {
        std::cin >> height;
    }
    if (size < 3) {
        std::cout << 0 << '\n';
        return 0;
    }

    int max_degree = 0;
    int left = 0;
    int mid = 0;
    int right = 0;
    while (left < size - 1) {
        while (left < size - 1 && heights[left] >= heights[left + 1]) {
            ++left;
        }
        mid = left;
        while (mid < size - 1 && heights[mid] <= heights[mid + 1]) {
            ++mid;
        }
        right = mid;
        while (right < size - 1 && heights[right] >= heights[right + 1]) {
            ++right;
        }
        if (mid < size - 1) {
            max_degree = std::max(max_degree, heights[mid] - std::min(heights[left], heights[right]));
        }
        left = right;
    }
    std::cout << max_degree << '\n';

    return 0;
}