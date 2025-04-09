#include <iostream>
#include <set>

int main() {
    int n;

    std::cin >> n;

    std::set<int> all_integers;
    for (int i = 0; i < n; ++i) {
        int integer;

        std::cin >> integer;
        all_integers.insert(integer);
    }

    for (auto it = all_integers.begin(); it != all_integers.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}