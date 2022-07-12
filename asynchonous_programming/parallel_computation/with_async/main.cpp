#include <iostream>
#include <future>
#include <vector>
#include <random>
#include <array>

const char THREADS_COUNT(4);

template <typename T>
T random_number(T a, T b);

double accum(double *beg, double *end, double init);

double task(std::vector<double> &numbers);

int main(int argc, char **argv){
    std::vector<double> test(16);
    // generate number from 1 to 16 in vector;
    std::generate(std::begin(test), std::end(test), [a = 0]() mutable{
        return ++a;
    });

    std::vector<double> task_numbers(10'000);
    // generate random number from 0 to 1;
    std::generate(std::begin(task_numbers), std::end(task_numbers), [](){
        return random_number(0.0, 1.0);
    });

    auto main_res = std::async(std::launch::async, task, std::ref(task_numbers));
    auto test_res = std::async(std::launch::async, task, std::ref(test));
 
    std::cout << "sum: " << test_res.get() << std::endl;
    std::cout << "sum: " << main_res.get() << std::endl;

    return EXIT_SUCCESS;
}

template <typename T>
T random_number(T a, T b){
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution<T> dist(a, b);

    return dist(mt);
}

double accum(double *beg, double *end, double init) {
    return std::accumulate(beg, end, init);
}

double task(std::vector<double> &numbers){
    unsigned short step (numbers.size() / THREADS_COUNT);
    double sum = 0;
    
    auto new_begin = &numbers[0];
    auto new_end = new_begin + step;

    std::array<std::future<double>, THREADS_COUNT> results;
    // make 4 threads to calculate the sum of vector faster;
    for (auto &res : results){
        res = std::async(std::launch::async, accum, new_begin, new_end, 0);
        new_begin = new_end;
        new_end += step;
    }

    // calculate total sum;
    for (auto &res : results){
        sum += res.get();
    }

    return sum;
}