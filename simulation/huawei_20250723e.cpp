#include <deque>
#include <iostream>
#include <sstream>
#include <string>

void read_line(std::deque<int>& deque) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream string_stream(line);
    int num;
    while (string_stream >> num) {
        deque.push_back(num);
    }
}

int main() {
    std::deque<int> supplements;
    std::deque<int> consumers;
    read_line(supplements);
    read_line(consumers);

    while (!supplements.empty() && !consumers.empty()) {
        int current_supply = supplements.front();
        supplements.pop_front();

        int attemps = 0;
        int max_attemps = consumers.size();
        while (!consumers.empty() && attemps < max_attemps) {
            int current_consumer = consumers.front();
            if (current_supply < current_consumer) {
                consumers.push_back(current_consumer);
                consumers.pop_front();
                ++attemps;
                continue;
            }
            if (current_supply == current_consumer) {
                consumers.pop_front();
            } else {
                int sum = 0;
                int count = 0;
                for (int consumer : consumers) {
                    if (consumer + sum <= current_supply) {
                        sum += consumer;
                        ++count;
                    } else {
                        break;
                    }
                }
                for (int i = 0; i < count; ++i) {
                    consumers.pop_front();
                }
            }
            break;
        }
    }

    std::cout << consumers.size() << '\n';

    return 0;
}