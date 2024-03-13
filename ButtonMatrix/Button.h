#ifndef BUTTONM_H
#define BUTTONM_H
#include "mbed.h"
#include <iostream>
#include <string>

class ButtonM{
    private:
        int rows;
        int columns;
    public:
        char KeyboardType;
        BusIn *rowPins;
        BusOut *columnPins;
        explicit ButtonM(int rows, int columns);
        std::string readStringInput();
        char readCharInput();
};

#endif