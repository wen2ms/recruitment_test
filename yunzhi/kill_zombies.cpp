#include <iostream>
#include <vector>

// 给你一个数组，数组内每个元素为一个棋盘，棋盘内每个格子有一个数字（0 <= × <=
// 9）代表格子内的僵尸数目，你有很多导弹，每个导弹打到的格子
// 与其相邻的上下左右四个格子僵尸归零，需要找到每个棋盘内需要的最少导弹数，及其对应的最大单颗导弹击杀数例子：数组中只有一个棋盘，为：
// 4 0 1
// 0 9 0
// 6 0 5
// 最少导弹数为 5，最大击杀数为9

const int dx[5] = {0, 1, -1, 0, 0};
const int dy[5] = {0, 0, 0, 1, -1};

int get_kill(const std::vector<std::vector<int>>& board, int x, int y) {
    int total = 0;
    int n = board.size(), m = board[0].size();
    for (int d = 0; d < 5; ++d) {
        int new_x = x + dx[d], new_y = y + dy[d];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
            total += board[new_x][new_y];
        }
    }
    return total;
}

void aplly_kill(std::vector<std::vector<int>>& board, int x, int y) {
    int n = board.size(), m = board[0].size();
    for (int d = 0; d < 5; ++d) {
        int new_x = x + dx[d], new_y = y + dy[d];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
            board[new_x][new_y] = 0;
        }
    }
}

std::pair<int, int> kill_zombies(std::vector<std::vector<int>>& board) {
    int missle_count = 0;
    int max_kill = 0;
    int n = board.size(), m = board[0].size();

    while (true) {
        int best_x = -1, best_y = -1, best_kill = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int kill = get_kill(board, i, j);
                if (kill > best_kill) {
                    best_kill = kill;
                    best_x = i;
                    best_y = j;
                }
            }
        }

        if (best_kill == 0) {
            break;
        }

        missle_count++;
        max_kill = std::max(max_kill, best_kill);
        aplly_kill(board, best_x, best_y);
    }

    return {missle_count, max_kill};
}

int main() {
    std::vector<std::vector<std::vector<int>>> boards = {{{4, 0, 1}, {0, 9, 0}, {6, 0, 5}}};

    for (int i = 0; i < boards.size(); ++i) {
        std::pair<int, int> res = kill_zombies(boards[i]);
        std::cout << res.first << ' ' << res.second << std::endl;
    }

    return 0;
}
