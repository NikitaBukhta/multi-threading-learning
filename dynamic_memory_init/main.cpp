#include <iostream>
#include <thread>
#include <array>
#include <mutex>

class SomeClass;

SomeClass *ptr (nullptr);
std::once_flag ptr_flag;

void process(void);

int main(int argc, char **argv){
    std::array<std::thread, 100> threads;

    for (auto &it : threads){
        it = std::thread(process);
    }

    for (auto &it : threads){
        it.join();
    }
}

class SomeClass{
public:
    SomeClass(void){
        std::cout << "New instance: " << this << std::endl;
    }

    void do_it(){
        // realization;
    }
};

/* not data race free!
void process(void){
    if (ptr == nullptr){
        ptr = new SomeClass();
    }

    ptr->do_it();
}*/

/* data race free, but will always lock
 * even if the object was created;
void process(void){
    static std::mutex mut;

    mut.lock();
    if (ptr == nullptr){
        ptr = new SomeClass();
    }

    mut.unlock();

    ptr->do_it();
}*/

/* not data race free!
void process(void){
    static std::mutex mut;
    if (ptr == nullptr){
        std::lock_guard lg(mut);
        ptr = new SomeClass();
    }

    ptr->do_it();
}*/

/* Data race free (mb?), but we can do that more easy
void process(void){
    static std::mutex mut;
    if (ptr == nullptr){
        std::lock_guard lg(mut);

        if (ptr == nullptr){
            ptr = new SomeClass();
        }
    }

    ptr->do_it();
}*/

// the best solution (or not?);
void process(void){
    std::call_once(ptr_flag, []() {
        ptr = new SomeClass();
    });

    ptr->do_it();
}