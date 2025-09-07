#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

int main() {
    int size;
    std::cin >> size;
    std::unordered_map<int64_t, int> total_freqs;
    std::unordered_map<int64_t, int> freqs1;
    int64_t minimum = std::numeric_limits<int64_t>::max();

    for (int i = 0; i < size; ++i) {
        int64_t stuff;
        std::cin >> stuff;
        ++total_freqs[stuff];
        ++freqs1[stuff];
        minimum = std::min(minimum, stuff);
    }

    for (int i = 0; i < size; ++i) {
        int64_t stuff;
        std::cin >> stuff;
        ++total_freqs[stuff];
        minimum = std::min(minimum, stuff);
    }

    for (const auto& [stuff, count] : total_freqs) {
        if (count % 2 == 1) {
            std::cout << -1 << '\n';
            return 0;
        }
    }

    std::vector<int64_t> surplus1;
    std::vector<int64_t> surplus2;
    for (const auto& [stuff, count] : total_freqs) {
        int target_count = count / 2;
        const auto& iter = freqs1.find(stuff);
        int count1 = (iter == freqs1.end() ? 0 : iter->second);

        if (count1 > target_count) {
            for (int i = 0; i < count1 - target_count; ++i) {
                surplus1.push_back(stuff);
            }
        } else if (count1 < target_count) {
            for (int i = 0; i < target_count - count1; ++i) {
                surplus2.push_back(stuff);
            }
        }
    }

    std::sort(surplus1.begin(), surplus1.end());
    std::sort(surplus2.begin(), surplus2.end());

    int64_t total_cost = 0;
    for (int i = 0; i < surplus1.size(); ++i) {
        int64_t direct_swap_cost = std::min(surplus1[i], surplus2[i]);
        int64_t indirect_swap_cost = 2 * minimum;
        total_cost += std::min(direct_swap_cost, indirect_swap_cost);
    }

    std::cout << total_cost << '\n';

    return 0;
}