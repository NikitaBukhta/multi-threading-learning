// There is data rase is not free;

#include <iostream>
#include <thread>
#include <array>

using namespace std::literals;

void print_thread_id(void){
    std::cout << "Thread id:\t" << std::this_thread::get_id() 
              << std::endl;
    
    std::this_thread::sleep_for(50ms);
}

int main(int argc, char **argv){
    std::array<std::thread, 3> threads;

    for (auto &it_th : threads){
        it_th = std::thread(print_thread_id);
    }

    for (auto &it_th : threads){
        it_th.join();
    }

    return 0;
}