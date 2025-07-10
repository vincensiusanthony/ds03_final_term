#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <ctime>

inline void printTime(std::time_t t) {
    char buf[32];
    std::strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", std::localtime(&t));
    std::cout << buf;
}

#endif // HELPER_H