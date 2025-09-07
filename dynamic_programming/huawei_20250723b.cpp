#include <deque>
#include <iostream>
#include <vector>

int main() {
    int max_jump;
    int size;
    std::cin >> max_jump >> size;

    std::vector<int> energies(size);
    for (int& energy : energies) {
        std::cin >> energy;
    }

    std::vector<int> maximum_collection(size);
    std::deque<int> deque;
    maximum_collection[0] = energies[0];
    deque.push_back(0);

    for (int i = 1; i < size; ++i) {
        if (!deque.empty() && deque.front() < i - max_jump) {
            deque.pop_front();
        }
        maximum_collection[i] = energies[i] + maximum_collection[deque.front()];

        while (!deque.empty() && maximum_collection[deque.back()] <= maximum_collection[i]) {
            deque.pop_back();
        }
        deque.push_back(i);
    }

    std::cout << maximum_collection[size - 1] << '\n';

    return 0;
}