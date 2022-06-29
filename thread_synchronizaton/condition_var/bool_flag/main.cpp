#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string some_useful_data ("Empty");
std::mutex mut;
bool written_made;

void read_data(void){
    std::unique_lock ul(mut);
    while (!written_made){
        ul.unlock();
        std::this_thread::sleep_for(10ms);
        ul.lock();
    }
    
    std::cout << "Data: " << some_useful_data << std::endl;
    written_made = false;
}

void write_data(void){
    std::cout << "Waiting for new data: " << std::endl;
    std::lock_guard lg(mut);

    some_useful_data.clear();
    std::getline(std::cin, some_useful_data);
    written_made = true;
}

int main(int argc, char **argv){
    //read_data();

    std::thread read_th(read_data);
    std::thread write_th(write_data);

    write_th.join();
    read_th.join();

    return EXIT_SUCCESS;
}