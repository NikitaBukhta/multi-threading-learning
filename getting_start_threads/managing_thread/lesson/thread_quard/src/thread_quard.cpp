#include "thread_quard.h"

ThreadQuard::~ThreadQuard(void){
    if (_t.joinable()){     // Join thread if necessary;
        _t.join();
    }
}