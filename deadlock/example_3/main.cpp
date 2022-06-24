// Deadlock free;

#include <thread>
#include <mutex>
#include <iostream>

std::mutex mutex_1;
std::mutex mutex_2;

void func_1(void) {
	std::cout << "Thread 1 locking mutexes..." << std::endl;
	std::lock(mutex_1, mutex_2);				               			// Lock both mutexes
	std::cout << "Thread 1 has locked the mutexes..."
			  << std::endl;

	std::unique_lock<std::mutex> lk1(mutex_1, std::adopt_lock); 	// Associate each mutex
	std::unique_lock<std::mutex> lk2(mutex_2, std::adopt_lock); 	// with a unique_lock
	std::cout << "Thread 1 releasing mutexes..." << std::endl;
}

void func_2(void) {
	std::cout << "Thread 2 locking mutexes..." << std::endl;
	std::lock(mutex_2, mutex_1);				               				// Lock both mutexes
	std::cout << "Thread 2 has locked the mutexes..." 
			  << std::endl;

	std::unique_lock<std::mutex> lk1(mutex_1, std::adopt_lock);	// Associate each mutex
	std::unique_lock<std::mutex> lk2(mutex_2, std::adopt_lock);  // with a unique_lock
	std::cout << "Thread 2 releasing mutexes..." << std::endl;
}

int main() {
	std::thread t1(func_1);
	std::thread t2(func_2);
	t1.join();
	t2.join();
}