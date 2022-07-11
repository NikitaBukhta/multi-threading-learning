#include <vector>
#include <list>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::literals;

template <typename T>
class LockFreeQueue {
private:
	std::list<T> list;
	typename std::list<T>::iterator iHead, iTail;

public:
	LockFreeQueue(void) {
		list.push_back(T());		         // Add dummy separator
		iHead = list.begin();
		iTail = list.end();
	}
	void Produce(const T& t) {
		list.push_back(t);		            // Add the new item
		iTail = list.end();		            // Publish it
		list.erase(list.begin(), iHead);	// Trim unused nodes
	}
	bool Consume(T& t) {
		auto iNext = iHead;
		++iNext;
		if (iNext != iTail) {		        // If queue is nonempty
			iHead = iNext;			        // Publish that we took an item
			t = *iHead;			            // Copy it back to the caller
			return true;			        // And report success
		}
		return false;			            // Else report queue was empty
	}
	// Function to print out all the elements
	// Start at iHead, print out current element, then advance to next element
	void Print() {
		auto head = iHead;
		++head;
		for (auto el = head; el != iTail; ++el)
			std::cout << *el << ", ";
		std::cout << std::endl;
	}
}; // End of class definition

int main() {
	LockFreeQueue<int> lfq;
	int j;
	
	for (int i = 0; i < 10; ++i) {
		// Run the member functions of LockFreeQueue in threads
		// Syntax for member function with std::thread:
		// First argument is a pointer to the member function
		// Second argument is the address of the object the member function is called on
		// (this will be the "this" pointer in the member function)
		// Then the arguments to the member function. These are passed as reference to int
		// so we need to wrap them in std::ref()
		std::thread produce(&LockFreeQueue<int>::Produce, &lfq, std::ref(i));
		std::thread consume(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
		//std::thread print(LockFreeQueue<int>::Print, &lfq);
		// Wait for the threads to complete
		produce.join();
		consume.join();
		//print.join();
		lfq.Print();
	}
}