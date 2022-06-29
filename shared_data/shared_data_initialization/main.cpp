#include "singleton.h"

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void task(void){
    Singleton &s = Singleton::get_singleton();

    // create mutex for correct output by cout;
    static std::mutex mut;
    mut.lock();

    std::cout << &s << std::endl;

    mut.unlock();
}

int main(int argc, char ** argv){
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i){
        threads.push_back(std::thread(task));
    }

    for (auto &it : threads){
        it.join();
    }

    return EXIT_SUCCESS;
}