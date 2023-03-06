#ifndef SRC_ALY_HELPER_H
#define SRC_ALY_HELPER_H

#include <iostream>
#include <ctime>

namespace helper {
time_t h_UseTime() 
{
    time_t current_time;
    time(&current_time);
    return current_time;
}
}

#endif