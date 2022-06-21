#include <iostream>
#include <vector>

void move_semantic(void){
    auto func = [](int &&x)->void {
        std::cout << "rvalue ref: " << x << std::endl;
    };

    func(2);
    int *y = new int(5);
    //func(y);
    func(std::move(*y));
    std::cout << "y after move to the function: " << *y << std::endl;

    int *x = std::move(y);
    std::cout << "y after move to the x: " << *y << std::endl;
    std::cout << "x: " << *x << std::endl;
}

void move_semantic_for_vector(void){
    auto func = [](std::vector<std::string> arg){
        std::cout << "Argument vector in func has " << arg.size() 
                  << " elements" << std::endl;
    };

    std::vector<std::string> vec(1000000);

    std::cout << "Before calling func, vector has: " 
              << vec.size() << " elements" << std::endl;

    std::cout << "(Copy) "; func(vec);
              
    std::cout << "After calling func, vector has: " 
              << vec.size() << " elements" << std::endl;

    std::cout << "(Move) "; func(std::move(vec));
              
    std::cout << "After calling func, vector has: " 
              << vec.size() << " elements" << std::endl;
}

class RLValueReferenceTest{
public:
    static void Start(void){
        int y{2};

        std::cout << "Argument y:\t\t"; func(y);

        std::cout << "Argument move(y):\t"; func(std::move(y));

        std::cout << "Argument 2:\t\t"; func(2);
    }
private:
    static void func(const int &x){
        std::cout << "Lvalue reference" << std::endl;
    }
    static void func(int &&x){
        std::cout << "Rvalue reference" << std::endl;
    }
};

int main(int argc, char **argv){
    //move_semantic();
    //move_semantic_for_vector();
    RLValueReferenceTest::Start();

    return EXIT_SUCCESS;
}