/* This program demonstrate working with atomic;
 * program without atomic is in int_operations_and_threads
 * folder;
 */

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void task(void){
    for (int i = 0; i < 100'000; ++i){
        ++counter;
    }
}

int main(int argc, char **argv){
    std::vector<std::thread> tasks;

    for (int i = 0; i < 10; ++i){
        tasks.push_back(std::move(std::thread(task)));
    }

    for (auto &t : tasks){
        t.join();
    }

    std::cout << counter << std::endl;

    return EXIT_SUCCESS;
}