#include <iostream>
#include <thread>

using namespace std::literals;

std::mutex print_mutex;
std::mutex temp_mutex;

void print(const std::string &str){
    for (int i = 0; i < 5; ++i){
        try{
            std::scoped_lock lk(print_mutex, temp_mutex);

            std::cout << str[0] << str[1] << str[2] << std::endl;

            throw std::exception();

            std::this_thread::sleep_for(50ms);
        }
        catch (std::exception &e){
            //std::cerr << "Error: " << e.what() << std::endl;
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

    //std::cout << sizeof(std::scoped_lock(print_mutex, temp, temp));

    return EXIT_SUCCESS;
}