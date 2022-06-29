/* Problem from condition_var directory program solved
 * thx to predicate in wait() method;
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string some_useful_data ("Empty");
std::mutex mut;
std::condition_variable cont_work;
bool condition (false);

void read_data(void){
    std::unique_lock ul(mut);
    cont_work.wait(ul, [](void) { return condition; });

    std::cout << "Data: " << some_useful_data << std::endl;
}

void write_data(void){
    std::cout << "Waiting for new data: " << std::endl;

    std::this_thread::sleep_for(2s);
    {
        std::lock_guard lg(mut);

        some_useful_data.clear();
        some_useful_data = "Hello world!";
        //std::getline(std::cin, some_useful_data);

        condition = true;
    }

    cont_work.notify_one();
}

int main(int argc, char **argv){
    //read_data();
    std::thread write_th(write_data);
    std::this_thread::sleep_for(2s);
    std::thread read_th(read_data);

    write_th.join();
    read_th.join();

    return EXIT_SUCCESS;
}