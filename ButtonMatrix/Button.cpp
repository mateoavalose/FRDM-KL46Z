#include "Button.h"

ButtonM::ButtonM(int rows, int columns) : rows(rows), columns(columns){
    if(rows == 4 && columns == 3){
        rowPins = new mbed::BusIn(D8, D9, D10, D11);
        columnPins = new mbed::BusOut(D5, D6, D7);
        std::cout << "Button Matrix inicialized. Rows are pins: D8, D9, D10 and D11. Columns are pins: D5, D6 and D7." << endl;
        KeyboardType = 'A';
    } else if(rows == 4 && columns == 4){
        rowPins = new mbed::BusIn(D8, D9, D10, D11);
        columnPins = new mbed::BusOut(D4, D5, D6, D7);
        std::cout << "Button Matrix inicialized. Rows are pins: D8, D9, D10 and D11. Columns are pins: D4, D5, D6 and D7." << endl;
        KeyboardType = 'B';
    } else {
        std::cout << "Button Matrix has to be 4x3 or 4x4 (Rows x Columns). Value provided is " << rows << "x" << columns << endl;
        KeyboardType = 'C';
        rowPins = new mbed::BusIn(D8);
        columnPins = new mbed::BusOut(D5);
    }
    std::cout << "Keyboard is type: " << KeyboardType << endl;
}

char ButtonM::readCharInput(){
    char input = '\0';

    if(KeyboardType == 'A'){ // Keyboard is 4x3
        while(input == '\0'){
            // D7 ON
            columnPins->write(0b011);
            if (rowPins->read() == 0b0111) {
                input = '1';
                std::cout << "1" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011) {
                input = '4';
                std::cout << "4" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b1101) {
                input = '7';
                std::cout << "7" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110) {
                input = '*';
                std::cout << "*" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D6 ON
            columnPins->write(0b101);
            if (rowPins->read() == 0b0111) {
                input = '2';
                std::cout << "2" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '5';
                std::cout << "5" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '8';
                std::cout << "8" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '0';
                std::cout << "0" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D5 ON
            columnPins->write(0b110);
            if (rowPins->read() == 0b0111){
                input = '3';
                std::cout << "3" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '6';
                std::cout << "6" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '9';
                std::cout << "9" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '#';
                std::cout << "#" << endl;
                while (rowPins->read() == 0b1110);
            }
            ThisThread::sleep_for(1s);
        }
    }else if(KeyboardType == 'B'){ // Keyboard is 4x4
        while(input == '\0'){
            // D7 ON
            columnPins->write(0b0111);
            if (rowPins->read() == 0b0111) {
                input = '1';
                std::cout << "1" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011) {
                input = '4';
                std::cout << "4" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b1101) {
                input = '7';
                std::cout << "7" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110) {
                input = '*';
                std::cout << "*" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D6 ON
            columnPins->write(0b1011);
            if (rowPins->read() == 0b0111) {
                input = '2';
                std::cout << "2" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '5';
                std::cout << "5" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '8';
                std::cout << "8" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '0';
                std::cout << "0" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D5 ON
            columnPins->write(0b1101);
            if (rowPins->read() == 0b0111){
                input = '3';
                std::cout << "3" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '6';
                std::cout << "6" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '9';
                std::cout << "9" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '-';
                std::cout << "#" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D4 ON
            columnPins->write(0b1110);
            if (rowPins->read() == 0b0111){
                input = 'A';
                std::cout << "A" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = 'B';
                std::cout << "B" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = 'C';
                std::cout << "C" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = 'D';
                std::cout << "D" << endl;
                while (rowPins->read() == 0b1110);
            }
            ThisThread::sleep_for(1s);
        }
    }else if(KeyboardType == 'C'){
        input = '\0';
        std::cout << "Button Matrix is not the right size. Nothing to read" << endl;
    }
    return input;
}

string ButtonM::readStringInput(){
    string input = "";
    string lastInput = "";
    if(KeyboardType == 'A'){ // Keyboard is 4x3
        while(true){
            // D7 ON
            columnPins->write(0b011);
            if (rowPins->read() == 0b0111) {
                input = '1';
                std::cout << "1" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011) {
                input = '4';
                std::cout << "4" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b1101) {
                input = '7';
                std::cout << "7" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110) {
                input = '*';
                std::cout << "*" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D6 ON
            columnPins->write(0b101);
            if (rowPins->read() == 0b0111) {
                input = '2';
                std::cout << "2" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '5';
                std::cout << "5" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '8';
                std::cout << "8" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '0';
                std::cout << "0" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D5 ON
            columnPins->write(0b110);
            if (rowPins->read() == 0b0111){
                input = '3';
                std::cout << "3" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '6';
                std::cout << "6" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '9';
                std::cout << "9" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '#';
                std::cout << "#" << endl;
                while (rowPins->read() == 0b1110);
            }
            ThisThread::sleep_for(1s);
            if(input[0] == '*')
                break;
            lastInput += input;
        }
    }else if(KeyboardType == 'B'){ // Keyboard is 4x4
        while(true){
            // D7 ON
            columnPins->write(0b0111);
            if (rowPins->read() == 0b0111) {
                input = '1';
                std::cout << "1" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011) {
                input = '4';
                std::cout << "4" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b1101) {
                input = '7';
                std::cout << "7" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110) {
                input = '*';
                std::cout << "*" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D6 ON
            columnPins->write(0b1011);
            if (rowPins->read() == 0b0111) {
                input = '2';
                std::cout << "2" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '5';
                std::cout << "5" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '8';
                std::cout << "8" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '0';
                std::cout << "0" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D5 ON
            columnPins->write(0b1101);
            if (rowPins->read() == 0b0111){
                input = '3';
                std::cout << "3" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = '6';
                std::cout << "6" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = '9';
                std::cout << "9" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = '-';
                std::cout << "#" << endl;
                while (rowPins->read() == 0b1110);
            }

            // D4 ON
            columnPins->write(0b1110);
            if (rowPins->read() == 0b0111){
                input = 'A';
                std::cout << "A" << endl;
                while (rowPins->read() == 0b0111);
            } else if (rowPins->read() == 0b1011){
                input = 'B';
                std::cout << "B" << endl;
                while (rowPins->read() == 0b1011);
            } else if (rowPins->read() == 0b01101){
                input = 'C';
                std::cout << "C" << endl;
                while (rowPins->read() == 0b1101);
            } else if (rowPins->read() == 0b1110){
                input = 'D';
                std::cout << "D" << endl;
                while (rowPins->read() == 0b1110);
            }
            ThisThread::sleep_for(1s);
            if(input[0] == '*')
                break;
            lastInput += input;
        }
    } else if(KeyboardType == 'C'){
        lastInput = '\0';
        std::cout << "Button Matrix is not the right size. Nothing to read" << endl;
    }
    return lastInput;
}