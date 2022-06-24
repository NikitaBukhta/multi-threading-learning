#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton{
public:
    Singleton(void);

    static Singleton& get_singleton(void);

private:
    Singleton(const Singleton &other) = delete;

    Singleton& operator= (const Singleton &other) = delete;

    Singleton(Singleton &&other) = delete;

    Singleton& operator= (Singleton &&other) = delete;
};

#endif // !SINGLETON_H