#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    int n, q;

    std::cin >> n >> q;

    std::vector<long long> integers(n);
    long long sum = 0;

    int zeros_count = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &integers[i]);

        if (integers[i] == 0) {
            ++zeros_count;
        }

        sum += integers[i];
    }

    for (int i = 0; i < q; ++i) {
        long long left, right;

        scanf("%lld%lld", &left, &right);
        
        long long min_sum = sum + zeros_count * left;
        long long max_sum = sum + zeros_count * right;

        printf("%lld %lld\n", min_sum, max_sum);
    }

    return 0;
}