#ifndef THREAD_QUARD_H
#define THREAD_QUARD_H

#include <thread>

class ThreadQuard{
private:
    std::thread _t;

public:
    // Constructor (std::thread is move-only);
    explicit ThreadQuard(std::thread &&t) : _t(std::move(t)) {}

    ~ThreadQuard(void);

    // Delete copy operator;
    ThreadQuard(const ThreadQuard&) = delete;
    ThreadQuard& operator= (const ThreadQuard&) = delete;

    // Provide move operator;
    ThreadQuard(ThreadQuard &&) noexcept = default;
    ThreadQuard& operator= (ThreadQuard &&) noexcept = default;
};

#endif // !THREAD_QUARD_H