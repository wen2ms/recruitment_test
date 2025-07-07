#include <iostream>
#include <string>

class Solution {
  public:
    int maxDepth(std::string s) {
        int maximum_depth = 0;
        int count = 0;

        for (char c : s) {
            if (c == ')') {
                --count;
            } else if (c == '(') {
                ++count;
                
                maximum_depth = std::max(maximum_depth, count);
            }
        }

        return maximum_depth;
    }
};

int main() {
    Solution solution;

    std::cout << solution.maxDepth("(1+(2*3)+((8)/4))+1") << std::endl;

    std::cout << solution.maxDepth("(1)+((2))+(((3)))") << std::endl;

    std::cout << solution.maxDepth("()(())((()()))") << std::endl;

    return 0;
}