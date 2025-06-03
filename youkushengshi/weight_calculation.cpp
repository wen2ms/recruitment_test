#include <iostream>
#include <vector>

// 题目描述：
// 有一棵 n 个节点的无向树，每个节点都有一个初始的权值。接下来进行 q 次操作，每次操作是选定一个节点 m 和一个乘数 x，将节点 m
// 以及所有与 m 直接相邻的节点的权值乘以 x（也就是说，只乘以 m 以及它的邻居节点，不是整棵子树）。
// 所有操作完成之后，对于每个节点 i，计算一个乘积 Pi，定义为：
// Pi = 节点 i 的权值 × 所有与 i 相邻的节点的权值
// 也就是说，Pi 是以节点 i 为中心，将自己和相邻节点权值相乘的结果。然后，输出这个乘积 Pi 的末尾有多少个连续的 0。
// 注意：末尾的 0 是指十进制表示中连续的 0 的个数，比如 4500 的末尾有 2 个 0，100000 有 5 个 0。

// 输入格式：
// 第一行一个整数 n，表示节点数。
// 第二行 n 个整数，表示每个节点的初始权值（从节点 1 到节点 n）。
// 接下来 n-1 行，每行两个整数 u 和 v，表示一条无向边，连接节点 u 和节点 v。
// 再接下来一行一个整数 q，表示有 q 次操作。
// 接下来 q 行，每行两个整数 m 和 x，表示将节点 m 以及它所有邻居的权值乘以 x。

int main() {
    int n;

    std::cin >> n;

    std::vector<long long> weights(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    std::vector<std::vector<int>> adjcent(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;

        std::cin >> u >> v;

        u--;
        v--;

        adjcent[u].push_back(v);
        adjcent[v].push_back(u);
    }

    int q;

    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        int m;
        long long x;

        std::cin >> m >> x;

        m--;

        weights[m] *= x;
        for (int neighbor : adjcent[m]) {
            weights[neighbor] *= x;
        }
    }

    std::vector<int> nums_two(n);
    std::vector<int> nums_five(n);

    for (int i = 0; i < n; ++i) {
        long long value = weights[i];
        int count_two = 0, count_five = 0;

        while (value % 2 == 0 && value > 0) {
            count_two++;
            value /= 2;
        }

        value = weights[i];

        while (value % 5 == 0 && value > 0) {
            count_five++;
            value /= 5;
        }

        nums_two[i] = count_two;
        nums_five[i] = count_five;
    }

    for (int i = 0; i < n; ++i) {
        int total_two = nums_two[i];
        int total_five = nums_five[i];

        for (int neighbor : adjcent[i]) {
            total_two += nums_two[neighbor];
            total_five += nums_five[neighbor];
        }

        std::cout << std::min(total_two, total_five) << std::endl;
    }

    return 0;
}