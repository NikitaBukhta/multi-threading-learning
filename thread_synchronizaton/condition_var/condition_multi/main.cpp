/* There is one problem in program: if one thread start waiting
 * another thread after his finished, the first thread must waiting
 * forever
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string some_useful_data ("Empty");
std::mutex mut;
std::condition_variable cont_work;
bool condition (false);

void read_data(void){
    std::unique_lock ul(mut);
    cont_work.wait(ul, [](void) { return condition; });

    std::cout << "Thread (" << std::this_thread::get_id() 
              << ")\n\tData: " << some_useful_data << std::endl;
}

void write_data(void){
    std::cout << "Waiting for new data: " << std::endl;

    std::this_thread::sleep_for(2s);
    {
        std::lock_guard lg(mut);

        some_useful_data.clear();
        some_useful_data = "Hello world!";
        //std::getline(std::cin, some_useful_data);

        condition = true;
    }

    //cont_work.notify_one();
    cont_work.notify_all();
}

int main(int argc, char **argv){
    using namespace std;

    //read_data();
    thread read1{read_data};
	this_thread::sleep_for(10ms);
	thread read2{read_data};
	this_thread::sleep_for(10ms);
	thread read3{read_data};
	this_thread::sleep_for(10ms);
	thread write{write_data};
    
	read1.join();
	read2.join();
	read3.join();
	write.join();

    return EXIT_SUCCESS;
}