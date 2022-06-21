#include <iostream>
#include <thread>
#include <string>

void print_hello(void){
    std::cout << "Hello, thread!\n";
}

void print(const std::string str){
    std::cout << str;
}

// change string value to xyz;
void change_str_value(std::string &str){
    std::cout << "Change string!\n";
    str = "xyz";
}

void change_owner(std::string &&str){
    std::cout << "Ownership of \"" << str 
              << "\" trasferred to thread!\n";
}

class TestClass{
public:
    void print_class_msg(void){
        std::cout << "Hello, Member Function!\n";
    }

    static void print_static_class_msg(void){
        std::cout << "Static method of class called!\n";
    }
};

int main(int argc, char **argv){
    std::string some_string = "abc";
    std::string temp_string = "that is temp string!";

    TestClass test_class_obj;

    std::thread t (print_hello);
    std::thread t2 (print, "Hello from second daughter thread!\n");
    std::thread t3 (change_str_value, std::ref(some_string));
    std::thread t4 (change_owner, std::move(some_string));
    std::thread t5(&TestClass::print_class_msg, &test_class_obj);
    std::thread t6(TestClass::print_static_class_msg);

    std::cout << "Doing some work in main thread...\n";
    
    /* Should alwais call join() when you create a thread
     * in order to escape the fatal error (main thread is 
      * finishing task earlier, that daughter thread);
     */
    t.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "\n\n";

    std::cout << "some_string after changes: " << some_string 
              << std::endl;
    std::cout << "temp_string after moving: " << temp_string 
              << std::endl;

    return EXIT_SUCCESS;
}