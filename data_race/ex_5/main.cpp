/*  There are two data races, on x and done.
 *  The compiler optimizes the loop in func2, because it does not know
 * that done can be modified by func1.
 *  It assumes done is a constant. This allows it to generate more efficient
 * code, but causes the loop to run for ever.
 *      * We can declare done as "volatile" to prevent this optimization
 *      * In Java and C#, the volatile keyword means that modifying done will be
 *          performed as an atomic operation. This removes the data race on done
 *      * However, in C++ we use a different keyword for atomic operations. The data
 *          race on done will still exist if it is declared volatile, even though the 
 *          loop will now run correctly
 */

#include <iostream>
#include <thread>

using namespace std::literals;

int x {0};
bool done {false};

void func_1(void){
    std::this_thread::sleep_for(50ms);
    x = 42;
    done = true;
}

void func_2(void){
    std::this_thread::sleep_for(50ms);

    // waiting for x = 42 and done = true;
    while (!done) {}

    std::cout << x << std::endl;
}

int main(int argc, char **argv){
    std::thread t1 (func_1);
    std::thread t2 (func_2);

    t1.join();
    t2.join();

    return 0;
}