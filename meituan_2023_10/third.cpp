#include <iostream>
#include <vector>

int main() {
    int t;

    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n; 

        std::cin >> n;

        std::string table_person_nubmers;
        
        std::cin >> table_person_nubmers;

        int m;
        
        std::cin >> m;

        std::string waiting_people;

        std::cin >> waiting_people;


        for (int j = 0; j < m; ++j) {
            bool is_first_found_table = false;
            int satisfied_table;

            if (waiting_people[j] == 'M') {
                for (int k = 0; k < n; ++k) {
                    if (table_person_nubmers[k] == '1') {
                        table_person_nubmers[k]++;

                        is_first_found_table = true;
                        satisfied_table = k + 1;
                        break;
                    }
                }

                if (!is_first_found_table) {
                    for (int k = 0; k < n; ++k) {
                        if (table_person_nubmers[k] == '0') {
                            table_person_nubmers[k]++;

                            satisfied_table = k + 1;
                            break;
                        }
                    }
                }
            } else {
                for (int k = 0; k < n; ++k) {
                    if (table_person_nubmers[k] == '0') {
                        table_person_nubmers[k]++;

                        is_first_found_table = true;
                        satisfied_table = k + 1;
                        break;
                    }
                }

                if (!is_first_found_table) {
                    for (int k = 0; k < n; ++k) {
                        if (table_person_nubmers[k] == '1') {
                            table_person_nubmers[k]++;
                            satisfied_table = k + 1;

                            break;
                        }
                    }
                }
            }

            std::cout << satisfied_table << std::endl;
        }
    }

    return 0;
}