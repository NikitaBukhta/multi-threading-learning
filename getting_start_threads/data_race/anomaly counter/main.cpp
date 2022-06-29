#include <iostream>
#include <thread>
#include <array>

const int LOOPS {100000};
const int THREADS_COUNT {10};
size_t counter {0};

void do_some_counting_magic(void){
    for (int i = 0; i < LOOPS; ++i){
        ++counter;
    }
}

int main(int argc, char **argv){
    std::array<std::thread, THREADS_COUNT> threads;
    
    for (auto &it_th : threads){
        it_th = std::thread (do_some_counting_magic);
    }

    for (auto &it_th : threads){
        it_th.join();
    }
    
    std::cout << "X = " << counter << std::endl;

    return EXIT_SUCCESS;
}