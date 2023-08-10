/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>

// Obect to stablish serial communication with the computer
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;
    
    DigitalOut ledR(LED1, 1);
    DigitalOut ledG(LED2, 1);
    DigitalOut ledB(LED3, 1);

    int counterR = 0;
    int expected_valueR = 0;

    int counterG = 0;
    int expected_valueG = 0;

    int counterB = 0;
    int expected_valueB = 0;

    // Interruption functions for every led
    void timerR_interrupt() {
        ledR = !ledR; // Inverts the state of the red LED
        counterR++; 
    }

    void timerG_interrupt() {
        ledG = !ledG; // Inverts the state of the green LED
        counterG++; 
    }

    void timerB_interrupt(){
        ledB = !ledB; // Inverts the state of the blue LED
        counterB++;
    }

int main()
{
    cout << "Enter a blinking time for the red LED: (in milliseconds): ";
    int BlinkingRateRed;
    cin >> BlinkingRateRed;
    BlinkingRateRed = BlinkingRateRed*1000;

    cout << "Enter a blinking time for the green LED (in milliseconds): ";
    int BlinkingRateGreen;
    cin >> BlinkingRateGreen;
    BlinkingRateGreen = BlinkingRateGreen*1000;

    cout << "Enter a blinking time for the blue LED (in milliseconds): ";
    int BlinkingRateBlue;
    cin >> BlinkingRateBlue;
    BlinkingRateBlue = BlinkingRateBlue*1000;

    Ticker tickerR;
    Ticker tickerG;
    Ticker tickerB;

    tickerR.attach_us(timerR_interrupt, BlinkingRateRed); // Interrupción para el LED rojo
    tickerG.attach_us(timerG_interrupt, BlinkingRateGreen); // Interrupción para el LED verde
    tickerB.attach_us(timerB_interrupt, BlinkingRateBlue); // Interrupción para el LED azul

    while (true)
    {
        if (expected_valueR != counterR) {
            cout << "RLed = " << BlinkingRateRed/1000*counterR << endl;
            expected_valueR = counterR;
        }

        if (expected_valueG != counterG) {
            cout << "GLed = " << BlinkingRateGreen/1000*counterG << endl;
            expected_valueG = counterG;
        }

        if (expected_valueB != counterB) {
            cout << "BLed = " << BlinkingRateBlue/1000*counterB << endl;
            expected_valueB = counterB;
        }

        ThisThread::sleep_for(1ms);
    }
}