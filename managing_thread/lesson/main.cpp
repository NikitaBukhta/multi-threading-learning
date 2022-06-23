#include "thread_quard.h"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

void some_func(void){
    for (char i = 0; i < 10; ++i){
        std::cout << static_cast<int>(i) << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main(int argc, char **argv){
    std::thread t {some_func};
    /*t.detach();     /* In this case, if we make ThreadQuard object,
                     * no errors will occure, because there is check
                     * for thread joinable. So that works good;
                     */

    ThreadQuard th(std::move(t));   /* in both cases: with or without join()
                                     * and detach() no errors will occure,
                                     * because there is check for joinable 
                                     * in destructor();
                                     */

    return 0;
}