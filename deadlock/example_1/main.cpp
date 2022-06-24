// Deadlock example;

#include <thread>
#include <mutex>
#include <iostream>

using namespace std::literals;

std::mutex mutex_1;
std::mutex mutex_2;

void func_1(void) {
	std::cout << "Thread 1 locking mutex 1..." << std::endl;
	std::unique_lock lk1(mutex_1);       // Acquire lock on mutex_1;
	std::cout << "Thread 1 has locked mutex 1" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;

	std::cout << "Thread 1 locking mutex 2..." << std::endl;
	std::unique_lock lk2(mutex_2);		// Wait for lock on mutex_2;
	std::cout << "Thread 1 has locked mutex 2" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;
	std::cout << "Thread 2 releases locks" << std::endl;
}

void func_2(void) {
	std::cout << "Thread 2 locking mutex 2..." << std::endl;
	std::unique_lock lk1(mutex_2);	    // Acquire lock on mutex_2;
	std::cout << "Thread 2 has locked mutex 2" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;

	std::cout << "Thread 2 locking mutex 1..." << std::endl;
	std::unique_lock lk2(mutex_1);	    // Wait for lock on mutex_1;
	std::cout << "Thread 2 has locked mutex 1" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;
	std::cout << "Thread 2 releases locks" << std::endl;
}

/* Deadlock free!!!
void func_2(void) {
	std::cout << "Thread 2 locking mutex 1..." << std::endl;
	std::unique_lock lk1(mutex_1);	    // Acquire lock on mutex_2;
	std::cout << "Thread 2 has locked mutex 1" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;

	std::cout << "Thread 2 locking mutex 2..." << std::endl;
	std::unique_lock lk2(mutex_2);	    // Wait for lock on mutex_1;
	std::cout << "Thread 2 has locked mutex 2" << std::endl;

	std::this_thread::sleep_for(50ms);	// Do some work;
	std::cout << "Thread 2 releases locks" << std::endl;
}*/

int main() {
	std::thread t1(func_1);
	std::thread t2(func_2);
	t1.join();
	t2.join();

    return EXIT_SUCCESS;
}