#ifndef FIZZ_BUZZ_H
#define FIZZ_BUZZ_H

#include <iostream>

namespace game
{
    class FizzBuzz{
    private:
        unsigned int _current_number;
        unsigned int _end;

    public:
        FizzBuzz(unsigned int end = 0) : _current_number(0), _end(end) {}

        int start(void);

        void set_end(unsigned int new_end);
    };
}

#endif // !FIZZ_BUZZ_H