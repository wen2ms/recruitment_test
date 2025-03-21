#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
  public:
    void mystery_decoder() {
        init_cases();

        for (int i = 0; i < cases_count_; ++i) {
            std::string decoder_string;

            for (int j = 0; j < encoder_strings_[i].size(); ++j) {
                if (encoder_strings_[i][j] == 'R') {
                    std::reverse(decoder_string.begin(), decoder_string.end());
                } else if (encoder_strings_[i][j] == 'Z' && j != 0) {
                    if (encoder_strings_[i][j - 1] == 'R') {
                        std::reverse(decoder_string.begin(), decoder_string.end());
                    } else {
                        decoder_string.pop_back();
                    }
                } else if (encoder_strings_[i][j] == 'Z' && j == 0) {
                    continue;
                } else {
                    decoder_string.push_back(encoder_strings_[i][j]);
                }
            }

            std::cout << decoder_string << std::endl;
        }
    }

  private:
    void init_cases() {
        std::cin >> cases_count_;

        for (int i = 0; i < cases_count_; ++i) {
            std::string current_string;

            std::cin >> current_string;

            encoder_strings_.push_back(current_string);
        }
    }

    int cases_count_;
    std::vector<std::string> encoder_strings_;
};

int main() {
    Solution solution_1;

    solution_1.mystery_decoder();

    return 0;
}