#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>

class some_type {
	// ...
public:
    some_type(void){
        std::cout << "Init" << std::endl;
    }

	void do_it(void){ 
        std::cout << "some action" << std::endl; 
    }
};

std::atomic<some_type*> ptr(nullptr);            // Variable to be lazily initialized
std::mutex process_mutex;

void process(void){
    if (!ptr) {                     // First check of ptr
        std::lock_guard<std::mutex> lk(process_mutex);
        
        if (!ptr){                  // Second check of ptr
            ptr = new some_type;   // Initialize ptr
        }
    }
    some_type *unboxing_ptr = ptr;
	unboxing_ptr->do_it();
}

int main(int argc, char **argv){
    std::vector<std::thread> threads;
    const int threads_count = 5;

    for (int i = 0; i < threads_count; ++i){
        threads.push_back(std::thread(process));
    }

    threads.shrink_to_fit();

    for (auto &th : threads){
        th.join();
    }

    if (!ptr){
        delete ptr;
    }

    return EXIT_SUCCESS;
}