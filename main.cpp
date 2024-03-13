#include "mbed.h"
#include <iostream>
#include "Button.h"

UnbufferedSerial serial(USBTX, USBRX, 9600);

int main()
{
    // Button Matrix Size
    int rows;
    int columns;
    std::cout << "Type the number of rows for the Button Matrix" << endl; 
    std::cin >> rows;
    std::cout << "Type the number of columns for the Button Matrix" << endl; 
    std::cin >> columns;

    // Button Matrix Inicialization
    ButtonM buttM(rows, columns);
    std::cout << endl;
    while (true) {
        std::cout << "Reading keyboard 'char' input, press a key" << endl;
        buttM.readCharInput();
        std::cout << endl;
        std::cout << "Reading keyboard 'string' input, press a key. To finish the string, press '*'" << endl;
        buttM.readStringInput();
        std::cout << "--------------------------------------------------------------------------------------------" << endl;
        ThisThread::sleep_for(100ms);
    }
}
