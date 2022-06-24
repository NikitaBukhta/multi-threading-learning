#include <thread>
#include <mutex>
#include <iostream>
#include <string>

using namespace std::literals;

std::timed_mutex mutex1, mutex2;

void func1() {
	std::this_thread::sleep_for(10ms);
	bool locked{false};
    while (!locked) {
        std::lock_guard lk(mutex1);		 // Lock mutex1
        std::this_thread::sleep_for(1s);	    
        std::cout << "After you, Claude!" << std::endl;
		locked = mutex2.try_lock_for(5ms);			// Try to get a lock on mutex2
	}
	if (locked)
		std::cout << "Thread1 has locked both mutexes" << std::endl;
}

void func2() {
    bool locked{false};
    while (!locked) {
        std::lock_guard lk(mutex2);		 // Lock mutex2
        std::this_thread::sleep_for(1s);	    
        std::cout << "No, after you, Cecil!" << std::endl;
		locked = mutex1.try_lock_for(5ms);			// Try to get a lock on mutex1
	}
	if (locked)
		std::cout << "Thread2 has locked both mutexes" << std::endl;
}

int main() {
	std::thread t1(func1);
	std::this_thread::sleep_for(10ms);
	std::thread t2(func2);
	t1.join();
	t2.join();
}