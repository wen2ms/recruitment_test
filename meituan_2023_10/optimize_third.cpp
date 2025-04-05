#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int main() {
    int t;

    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n; 

        std::cin >> n;

        std::string table_person_string;
        
        std::cin >> table_person_string;

        int m;
        
        std::cin >> m;

        std::string waiting_people;

        std::cin >> waiting_people;

        std::priority_queue<int, std::vector<int>, std::greater<int>> zero_pick_queue;
        std::priority_queue<int, std::vector<int>, std::greater<int>> one_pick_queue;

        for (int j = 0; j < n; ++j) {
            if (table_person_string[j] == '0') {
                zero_pick_queue.push(j + 1);
            } else if (table_person_string[j] == '1') {
                one_pick_queue.push(j + 1);
            }
        }

        for (int j = 0; j < m; ++j) {
            int satisfied_table;

            if (waiting_people[j] == 'M') {
                if (one_pick_queue.empty()) {
                    satisfied_table = zero_pick_queue.top();
                    zero_pick_queue.pop();

                    one_pick_queue.push(satisfied_table);
                } else {
                    satisfied_table = one_pick_queue.top();
                    one_pick_queue.pop();
                }
            } else {
                if (zero_pick_queue.empty()) {
                    satisfied_table = one_pick_queue.top();
                    one_pick_queue.pop();
                } else {
                    satisfied_table = zero_pick_queue.top();
                    zero_pick_queue.pop();

                    one_pick_queue.push(satisfied_table);
                }
            }

            std::cout << satisfied_table << '\n';
        }
    }

    return 0;
}