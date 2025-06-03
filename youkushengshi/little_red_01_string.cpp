#include <iostream>
#include <string>

// 小红拿到了一个01串。所谓01串，指仅由'0'和'1'两种字符组成的字符串。
// 小红可以进行任意次以下操作：
// 选择字符串的一个字符，将其取反（'0'变'1'或者'1'变'0'）。
// 小红定义一个01串为好串，当且仅当该01串不包含"010"子串和"101"子串。
// 例如，"1001"是好串，但"100100"则不是好串。
// 小红想知道，自己最少操作多少次可以将给定字符串变成好串？


int main() {
    std::string str;

    std::cin >> str;

    if (str.size() < 3) {
        std::cout << 0 << std::endl;

        return 0;
    }

    int count = 0;

    for (int i = 2; i < str.size(); ++i) {
        std::string sub_str = str.substr(i - 2, 3);

        if (sub_str == "010" || sub_str == "101") {
            i += 2;

            count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}