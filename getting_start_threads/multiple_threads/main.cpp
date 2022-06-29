#include <iostream>
#include <thread>
#include <chrono>
#include <array>

void print_thread_number(unsigned short thread_number){
    std::this_thread::sleep_for(std::chrono::seconds(thread_number));

    std::cout << "Thread number " << thread_number << std::endl;
}

int main(int argc, char **argv){
    std::array<std::thread, 3> threads;

    size_t threads_count = threads.size();
    for (size_t i = 0; i < threads_count; ++i){
        threads[i] = std::thread(print_thread_number, i + 1);
    }

    for (auto &th : threads){
        th.join();
    }

    return EXIT_SUCCESS;
}