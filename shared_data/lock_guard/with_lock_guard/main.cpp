#include <iostream>
#include <thread>

using namespace std::literals;

std::mutex print_mutex;

void print(const std::string &str){
    for (int i = 0; i < 5; ++i){
        try{
            std::lock_guard<std::mutex> lk(print_mutex);

            std::cout << str[0] << str[1] << str[2] << std::endl;

            throw std::exception();

            std::this_thread::sleep_for(50ms);
        }
        catch (std::exception &e){
        }
    }
}

int main(int argc, char **argv){
    std::thread t1 (print, "abc");
    std::thread t2 (print, "def");
    std::thread t3 (print, "xyz");

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}