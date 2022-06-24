// Deadlock free;

#include <thread>
#include <mutex>
#include <iostream>

using namespace std::literals;

std::mutex mutex_1;
std::mutex mutex_2;

void func_1() {
	std::cout << "Thread 1 locking mutexes..." << std::endl;
	std::scoped_lock lk1(mutex_1, mutex_2);
	std::cout << "Thread 1 has locked mutexes..." << std::endl;
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 1 releasing mutexes..." << std::endl;
}

void func_2() {
	std::cout << "Thread 2 locking mutexes..." << std::endl;
	std::scoped_lock lk1(mutex_2, mutex_1);
	std::cout << "Thread 2 has locked mutexes..." << std::endl;
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread 2 releasing mutexes..." << std::endl;
}

int main() {
	std::thread t1(func_1);
	std::thread t2(func_2);
	t1.join();
	t2.join();
}