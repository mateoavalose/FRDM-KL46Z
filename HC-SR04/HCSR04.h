/**
 * @author Nestor Pereira-Neto  Team: SalvadorEngenharia
 *
 * @section LICENSE
 *
 * Copyright (c) 2010 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Biblioteca para uso do sonar HC-SR04, possui rotinas para permitir medições 
 * de distências retornado valores em centímetros, polegadas ou o tempo 
 * percorrido pelo som (em microsegundos).
 * Esta biblioteca pode ser usada com qualquer pino do microcontrolador.
 */


#ifndef HCSR04_H
#define HCSR04_H

#include "mbed.h"



/** 
 * Sonar HC-SR04 example.
 * @code
 * #include "mbed.h"
 * #include "HCSR04.h"
 *
 * DigitalOut myled(LED1);
 * Serial pc(USBTX,USBRX);     
 *
 * HCSR04 sonar(PTD5, PTA13);
 *
 * int main() {
 *     while(1) {
 *         printf("Detected distance from sensor %.2f cm \n", sonar.getCm()); 
 *         ThisThread::sleep_for(1000ms);
 *     }
 * }
 *
 * @endcode
*/

class HCSR04 {    
    public:    
        /** Constructor, creates HCSR04 instance 
          *
          * @param trigger TRIG pin
          * @param echo ECHO pin
          */
        HCSR04(PinName trigger, PinName echo);
 
        /** Sonar reading
          * 
          * @returns Pulse echo time in microseconds*/
        float readEcho(void);
        
        /** It measures the distance in centimeter "cm" 
          *
          *@returns Distance in centimeter
          */
        float getCm(void);
        
        /** Measures distance in inches "in" 
          *
          *@returns Distance in inches*/
        float getIn(void);
        
    private:
        float tdist;        // Time passed reading
        float distcm;       // Saves the measured distance in cm
        float distin;       // Saves the measured distance in In
        
        DigitalOut trigger;      // Trigger pin configuration
        DigitalIn echo;       // Echo pin configuration
        Timer time;       // Timer Object
        
};

#endif