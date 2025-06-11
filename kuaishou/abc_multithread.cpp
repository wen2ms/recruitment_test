#include <iostream>
#include <thread>
#include <condition_variable>

// 多线程循环打印ABC

std::mutex mutex;
std::condition_variable condition;
int turn = 0;

void print_letter(char letter) {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);

        condition.wait(lock, [&]() {
            return turn == letter - 'A';
        });

        std::cout << letter << " thread_id = " << std::this_thread::get_id() << std::endl;

        turn = (turn + 1) % 3;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        condition.notify_all();
    }
}

int main() {
    std::thread t_a(print_letter, 'A');
    std::thread t_b(print_letter, 'B');
    std::thread t_c(print_letter, 'C');

    t_a.join();
    t_b.join();
    t_c.join();

    return 0;
}