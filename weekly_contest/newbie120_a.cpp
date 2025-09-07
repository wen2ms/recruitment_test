#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int total_case;
    std::cin >> total_case;
    while (total_case > 0) {
        --total_case;
        std::vector<int> freqs(26);
        int len;
        std::string str;
        std::cin >> len >> str;
        for (const char letter : str) {
            ++freqs[letter - 'a'];
        }
        std::sort(freqs.begin(), freqs.end());
        int index = 1;
        while (index < 26) {
            if (freqs[index - 1] != 0 && freqs[index] != freqs[index - 1] + 1) {
                break;
            }
            ++index;
        }
        std::cout << (index == 26 ? "YES" : "NO") << '\n';
    }

    return 0;
}
