#include <iostream>
#include <mutex>
#include <thread>

std::mutex mut;
std::recursive_mutex recursive_mut;

// Waiting while promgra alive
int bad_factorial(int n){
    std::lock_guard lk (mut);

    if (n < 0){
        return 0;
    }
    else if (n == 0){
        return 1;
    }
    else{
        int ret = bad_factorial(n - 1) * n;
        std::cout << ret << std::endl;
        return ret;
    }
}

// works good;
int good_factorial(int n){
    std::lock_guard lk (recursive_mut);

    if (n < 0){
        return 0;
    }
    else if (n == 0){
        return 1;
    }
    else{
        int ret = good_factorial(n - 1) * n;
        std::cout << ret << std::endl;
        return ret;
    }
}

int main(int argc, char **argv){
    std::thread t1(good_factorial, 10);
    std::thread t2(good_factorial, 11);

    t1.join();
    t2.join();
}