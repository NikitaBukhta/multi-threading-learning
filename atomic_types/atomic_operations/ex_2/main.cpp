#include <iostream>
#include <thread>
#include <atomic>
#include <array>

#define in :

using namespace std::literals;

std::atomic_flag task_flag = ATOMIC_FLAG_INIT;

void task(int n){
    std::this_thread::sleep_for(50ms);      // look busy;

    while (task_flag.test_and_set());       // waiting while funciton is not free;

    std::cout << "I am a task with argument " << n << std::endl;

    task_flag.clear();
}

int main(int argc, char **argv){
    std::array<std::thread, 5> threads;

    short threads_count = threads.size();
    for(short i = 0; i < threads_count; ++i){
        threads[i] = std::move(std::thread(task, i));
    }

    for (auto &th in threads){
        th.join();
    }

    return EXIT_SUCCESS;
}