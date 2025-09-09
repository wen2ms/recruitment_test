#include <deque>
#include <iostream>
#include <vector>

void process_segment(const int start, const int end, const std::vector<int>& nums, std::vector<std::pair<int, int>>& results,
                     int& max_len) {
    std::deque<int> min_deque;
    std::deque<int> max_deque;
    int left = start;
    for (int right = start; right <= end; ++right) {
        while (!min_deque.empty() && nums[min_deque.back()] >= nums[right]) {
            min_deque.pop_back();
        }
        min_deque.push_back(right);
        while (!max_deque.empty() && nums[max_deque.back()] <= nums[right]) {
            max_deque.pop_back();
        }
        max_deque.push_back(right);

        while (nums[max_deque.front()] - nums[min_deque.front()] > 4) {
            if (min_deque.front() == left) {
                min_deque.pop_front();
            }
            if (max_deque.front() == left) {
                max_deque.pop_front();
            }
            ++left;
        }
        int current_len = right - left + 1;
        if (current_len > max_len) {
            max_len = current_len;
            results.clear();
            results.emplace_back(left, right);
        } else if (current_len == max_len) {
            results.emplace_back(left, right);
        }
    }
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> nums(size);
    for (int& num : nums) {
        std::cin >> num;
    }
    std::vector<std::pair<int, int>> results;
    int max_len = 0;
    int segment_start = 0;
    for (int i = 0; i < size; ++i) {
        if (nums[i] < 18 || nums[i] > 24) {
            process_segment(segment_start, i - 1, nums, results, max_len);
            segment_start = i + 1;
        }
    }

    process_segment(segment_start, size - 1, nums, results, max_len);

    for (const auto& [start, end] : results) {
        std::cout << start << ' ' << end << '\n';
    }

    return 0;
}