#include <iostream>
#include <thread>
#include <future>

using namespace std::literals;

void produce(std::promise<int> &px){
    try
    {
        int x(42);
        std::this_thread::sleep_for(500ms);
        throw std::out_of_range("some thrown exception!");

        std::cout << "Promise sets shared state to " << x << std::endl;
        px.set_value(x);
    }
    catch(...)
    {
        px.set_exception(std::current_exception());
    }
}

void consume(std::future<int> &fx){
    try
    {
        std::cout << "Future calling get()..." << std::endl;
        int x = fx.get();
        // std::cout << "X = " << fx.get() << std::endl; // segm fault
        std::cout << "X = " << x << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
}

int main(int argc, char **argv){
    std::promise<int> p;
    std::future<int> f(p.get_future());

    std::thread fut(consume, std::ref(f));
    std::thread prom(produce, std::ref(p));

    fut.join();
    prom.join();

    return EXIT_SUCCESS;
}