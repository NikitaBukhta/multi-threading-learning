#include <iostream>
#include <thread>
#include <future>

using namespace std::literals;

void produce(std::promise<int> &prom, int a, int b);

void consume(std::future<int> &f_x);

int main(int argc, char **argv){
    std::promise<int> prom;
    std::future<int> f_x = prom.get_future();

    std::thread prod(produce, std::ref(prom), 3, 4);
    std::thread cons(consume, std::ref(f_x));

    prod.join();
    cons.join();
    
    return EXIT_SUCCESS;
}

void produce(std::promise<int> &prom, int a, int b){
    std::this_thread::sleep_for(1s);
    prom.set_value(a + b);
}

void consume(std::future<int> &f_x){
    int x(f_x.get());
    std::cout << "Value is: " << x << std::endl;
}