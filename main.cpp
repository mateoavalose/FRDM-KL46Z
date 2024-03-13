/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>

// Blinking rate in milliseconds
#define BLINKING_RATE 200ms

UnbufferedSerial pc(USBTX, USBRX, 9600);

PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

int main() {

  while (true) {
    // Define the LED periods
    ledR.period(0.1);
    ledG.period(0.1);
    ledB.period(0.1);

    // Ask for the RGB value
    cout << "Enter a Hexadecimal value: " << endl;
    string hexCode;
    cin >> hexCode;

    // Remove the '#' character from the hexadecimal code
    if(hexCode[0] == '#')
        hexCode.erase(0, 1);

    // Convert the hexadecimal code to integer
    int hexValue = std::stoi(hexCode, nullptr, 16);

    // Extract the red, green, and blue values using bitwise operations and bit shifting
    int red = (hexValue >> 16) & 0xFF;
    int green = (hexValue >> 8) & 0xFF;
    int blue = hexValue & 0xFF;

    // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red/255.0;
    float FFGreen = 1 - green/255.0;
    float FFBlue = 1 - blue/255.0;

    // Write a specific color in the LED
    cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
    ledR.write(FFRed);
    ledG.write(FFGreen);
    ledB.write(FFBlue);
    cout << "------------------------------" << endl;
  }
}
