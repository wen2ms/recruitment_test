#include <iostream>
#include <limits>

int main() {
    int star_id;
    int visit_time;
    int prev_visit_time = 0;

    int max_interval = -1;
    int min_interval = std::numeric_limits<int>::max();
    int max_id;
    int min_id;

    while (std::cin >> star_id >> visit_time) {
        int interval = visit_time - prev_visit_time;
        if (interval < min_interval) {
            min_interval = interval;
            min_id = star_id;
        } else if (interval == min_interval) {
            min_id = std::min(min_id, star_id);
        }

        if (interval > max_interval) {
            max_interval = interval;
            max_id = star_id;
        } else if (interval == max_interval) {
            max_id = std::min(max_id, star_id);
        }

        prev_visit_time = visit_time;
    }

    std::cout << min_id << ' ' << max_id << '\n';

    return 0;
}