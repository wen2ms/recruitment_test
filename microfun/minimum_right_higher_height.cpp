#include <iostream>
#include <stack>
#include <vector>

// 给定一个整数数组 heights，对数组中的每一个元素 heights[i]，找出它右边第一个比它高的最小值。

int main() {
    std::vector<int> heights = {3, 1, 4, 2, 5};

    int n = heights.size();
    std::vector<int> result(n, -1);
    std::stack<int> higher_stack;

    for (int i = n - 1; i >= 0; --i) {
        while (!higher_stack.empty() && higher_stack.top() <= heights[i]) {
            higher_stack.pop();
        }

        if (!higher_stack.empty()) {
            result[i] = higher_stack.top();
        }

        higher_stack.push(heights[i]);
    }

    for (int num : result) {
        std::cout << num << ' ';
    }    
    std::cout << std::endl;

    return 0;
}