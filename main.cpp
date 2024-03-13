/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>

UnbufferedSerial pc(USBTX, USBRX, 9600);

BusOut displayLED(D8, D7, D6, D5, D4, D3, D2);

int main() {

  while (true) {
    cout << "Type the number you want to see in the 7 segment display: " << endl;
    int number;
    cin >> number;

    switch(number){
        case 1:
            displayLED.write(48);
            break;
        case 2:
            displayLED.write(109);
            break;
        case 3:
            displayLED.write(121);
            break;
        case 4:
            displayLED.write(51);
            break;
        case 5:
            displayLED.write(91);
            break;
        case 6:
            displayLED.write(95);
            break;
        case 7:
            displayLED.write(112);
            break;
        case 8:
            displayLED.write(127);
            break;
        case 9:
            displayLED.write(123);
            break;
        case 0:
            displayLED.write(126);
            break;
    }
  }
}
