#include <iostream>
#include <thread>
#include <future>

using namespace std::literals;

void produce(std::promise<int> &px){
    int x(42);
    std::this_thread::sleep_for(500ms);
    std::cout << "Promise sets shared state to " << x << std::endl;
    px.set_value(x);
}

void consume(std::future<int> &fx){
    std::cout << "Future calling get()..." << std::endl;
    int x = fx.get();
    // std::cout << "X = " << fx.get() << std::endl; // segm fault
    std::cout << "X = " << x << std::endl;
}

int main(int argc, char **argv){
    std::promise<int> p;
    auto f = p.get_future();

    std::thread fut(consume, std::ref(f));
    std::thread prom(produce, std::ref(p));

    fut.join();
    prom.join();

    return EXIT_SUCCESS;
}