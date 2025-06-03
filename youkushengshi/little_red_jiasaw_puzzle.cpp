#include <iostream>
#include <vector>

// 小红拼图
// 题目描述
// 小红用拼图组件拼图，每个组件可以通过顺时针旋转 90度的倍数（0°、90°180° 270°）得到不同形态，对应字符为：
// •w：0度（初始方向）
// •D：90度
// •S: 180度
// •A: 270度

// 拼图规则：
// 1.相邻的两个组件必须凸凹互补（即不能同时凸或同时凹）。
// 2.* 表示空格，无需考虑相邻关系。
// 输入多组测试用例，判断能否用给定的拼图图案合法拼接。
// 输入格式
// •第一行输入 t (1st<10)，表示测试用例数量。
// •每组用例：
// 第一行输入n和m (1≤n, m ≤ 100），表示拼图的行数和列数。
// 接下来 n 行，每行一个长度为 m 的字符串，宇符为 “W'，‘A'，"S‘，‘D‘，•*

// 输出格式
// 每组用例输出 "ves”或"No”，表示能否合法拼接。

std::vector<int> get_edges(char block) {
    switch (block) {
        case 'W':
            return {1, 0, 1, 1};
        case 'D':
            return {1, 1, 0, 1};
        case 'S':
            return {0, 1, 1, 1};
        case 'A':
            return {1, 1, 1, 0};
    }

    return {};
}

int main() {
    int t;

    std::cin >> t;

    while (t--) {
        int n, m;

        std::cin >> n >> m;

        std::vector<std::string> grid(n);

        for (int i = 0; i < n; ++i) {
            std::cin >> grid[i];
        }

        bool valid = true;

        for (int i = 0; i < n && valid; ++i) {
            for (int j = 0; j < m; ++j) {
                char cur = grid[i][j];

                if (cur == '*') {
                    continue;
                }

                std::vector<int> cur_edges = get_edges(cur);

                if (j + 1 < m && grid[i][j + 1] != '*') {
                    std::vector<int> right_edges = get_edges(grid[i][j + 1]);

                    if (cur_edges[3] + right_edges[2] != 1) {
                        valid = false;
                        break;;
                    }
                }

                if (i + 1 < n && grid[i + 1][j] != '*') {
                    std::vector<int> down_edges = get_edges(grid[i + 1][j]);

                    if (cur_edges[1] + down_edges[0] != 1) {
                        valid = false;
                        break;;
                    }
                }
            }
        }

        std::cout << (valid ? "Yes" : "No") << std::endl;
    }

    return 0;
}