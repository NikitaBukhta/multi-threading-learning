/* The same code as double-checked_locking_reprise
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class some_type{
public:
    some_type(void){
        std::cout << "Init" << std::endl;
    }

    ~some_type(void){
        std::cout << "Destroy" << std::endl;
    }

    void do_it(void){
        std::cout << "Do some action!" << std::endl;
    }
};

std::atomic<some_type*> ptr(nullptr);
std::mutex process_mutex;

void process(void){
    // double-check locking
    if (!ptr){
        std::lock_guard<std::mutex> guard(process_mutex);

        if (!ptr){
            ptr = new some_type;    // init
        }
    }

    some_type *sp = ptr;
    sp->do_it();
}

int main(int argc, char **argv){
    std::vector<std::thread> threads(0);
    
    {
        const char THREADS_COUNT = 5;
        threads.resize(THREADS_COUNT);
    }

    for (auto &th : threads){
        th = std::move(std::thread(process));
    }

    for (auto &th : threads){
        th.join();
    }

    if(ptr){
        delete ptr;
    }

    return EXIT_SUCCESS;
}