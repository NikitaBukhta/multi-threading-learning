#include "singleton.h"

Singleton::Singleton(void){
    std::cout << "Itinializing singleton" << std::endl;
}

Singleton& Singleton::get_singleton(void){
    static Singleton instance;

    return instance;
}