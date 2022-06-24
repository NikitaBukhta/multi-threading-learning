#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void func_1() {
    std::unique_lock<std::mutex> lk1(mutex1, std::defer_lock);	// Associate mutex with lock...
    std::unique_lock<std::mutex> lk2(mutex2, std::defer_lock);	// ...but don’t lock it yet
    std::lock(lk1, lk2);										// Now lock both of them
}

void func_2() {
    std::unique_lock<std::mutex> lk2(mutex2, std::defer_lock);	// Associate mutex with lock...
    std::unique_lock<std::mutex> lk1(mutex1, std::defer_lock);	// ...but don’t lock it yet
    std::lock(lk1, lk2);										// Now lock both of them
}

int main() {
	std::thread t1(func_1);
	std::thread t2(func_2);
	t1.join();
	t2.join();
}