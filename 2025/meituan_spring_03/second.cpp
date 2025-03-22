#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int t;

    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        
        std::cin >> n;

        std::vector<int> p(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> p[j];
        }

        int good_permutations_count = 0;

        for (int k = 0; k < n; ++k) {
            for (int l = k; l < n; ++l) {
                int mid = (l + k) / 2;

                if (p[mid] >= *std::max_element(p.begin() + k, p.begin() + mid) && p[mid] <= *std::min_element(p.begin() + mid, p.begin() + l + 1)
                    && ((l - k + 1) % 2 == 1)) {
                    ++good_permutations_count;
                }
            }
        }

        std::cout << good_permutations_count << std::endl;
    }

    return 0;
}