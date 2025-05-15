#include <iostream>
#include <string>
#include <vector>

// 一个由1-9的字符串，给里面填加号，求其中的质数

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void dfs(const std::string& s, int index, int curr_sum, int curr_num, std::string expr, std::vector<std::string>& all_exprs) {
    if (index == s.size()) {
        int total = curr_num + curr_sum;
        if (is_prime(total)) {
            all_exprs.push_back(expr);
        }
        return;
    }

    dfs(s, index + 1, curr_sum + curr_num, s[index] - '0', expr + "+" + s[index], all_exprs);

    dfs(s, index + 1, curr_sum, curr_num * 10 + (s[index] - '0'), expr + s[index], all_exprs);
}

int main() {
    std::string s;
    std::cin >> s;

    std::vector<std::string> prime_exprs;
    dfs(s, 1, 0, s[0] - '0', std::string(1, s[0]), prime_exprs);

    for (const auto& expr : prime_exprs) {
        std::cout << expr << std::endl;
    }

    return 0;
}