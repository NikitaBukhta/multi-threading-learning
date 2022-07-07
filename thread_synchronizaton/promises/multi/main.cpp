#include <iostream>
#include <thread>
#include <future>
#include <mutex>

using namespace std::literals;

void produce(std::promise<int> &px){
    int x(42);
    std::this_thread::sleep_for(5s);

    std::cout << "Prommise sets shared state to " << x << std::endl;
    px.set_value(x);
}

void consume(std::shared_future<int> &fx){
    std::cout << "Thread " << std::this_thread::get_id()
              << " calling get()..." << std::endl;

    int x(fx.get());
    static std::mutex consume_mut;
    std::lock_guard lg(consume_mut);
    std::cout << "Thread " << std::this_thread::get_id()
              << " returns from calling get()" << std::endl;

    std::cout << "Thread " << std::this_thread::get_id()
              << " has answer: " << x << std::endl;
}

int main(int argc, char const **argv){
    using namespace std;

    promise<int> p;
    shared_future<int> sf1(p.get_future());   // Move p's future into a shared future
    shared_future<int> sf2 = sf1;                     // Create a separate instance of shared future

    thread fut1{consume, std::ref(sf1)};         // Start two consumer threads, each with
    thread fut2{consume, std::ref(sf2)};         // its own shared future instance
    thread prom{produce, std::ref(p)};           // Start the producer thread

    fut1.join();
    fut2.join();
    prom.join();
    
    return EXIT_SUCCESS;
}
