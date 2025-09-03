#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int required_energy;
    int limit;
    int num_of_mediums;
    std::cin >> required_energy >> limit >> num_of_mediums;

    std::vector<std::pair<int, int>> medium(num_of_mediums);
    for (auto& [energy, mana] : medium) {
        std::cin >> energy >> mana;
    }

    std::vector<int> max_energies(limit + 1, -1);
    max_energies[0] = 0;

    for (const auto& [energy, mana] : medium) {
        for (int i = limit; i >= mana; --i) {
            if (max_energies[i - mana] != -1) {
                max_energies[i] = std::max(max_energies[i], max_energies[i - mana] + energy);
            }
        }
    }

    for (int i = 1; i <= limit; ++i) {
        if (max_energies[i] >= required_energy) {
            std::cout << i << ' ' << max_energies[i] << '\n';
            return 0;
        }
    }
    std::cout << "0 0" << '\n';

    return 0;
}