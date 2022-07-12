#include <iostream>
#include <future>
#include <thread>

int sum(int a, int b);

int main(int argc, char **argv){
    std::packaged_task<int(int, int)> ptask(sum);

    // The future for packaged_task's promise
    std::future<int> fut = ptask.get_future();
    // Create thread to run the task;
    std::thread th(std::move(ptask), 6, 7);
    th.join();

    std::cout << "6 + 7 = " << fut.get() << std::endl;

    return EXIT_SUCCESS;
}

int sum(int a, int b){
    return a + b;
}