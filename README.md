# LEDs and Serial Communication - Hardware Arquitecture 2023-2
## Project Overview
This project demonstrates a way to control the blinking rates of three LEDs (red, green, and blue) using the mbed microcontroller **FRDM-K64F** and the **FRDM-KL25Z**. The provided code uses interrupt-driven timers to toggle the LEDs' states and calculates the time each LED has been on based on the number of interrupts. The code is written in C++ and utilizes the mbed platform's functionalities.

## Code Explanation
Here's a breakdown of the code's sections:

### 1. Serial Communication Initialization
The code establishes serial communication with the computer using an `UnbufferedSerial` object. This enables interaction with the user to input the blinking rates for each LED.
```cpp
#include "mbed.h"
#include <iostream>

// Obect to stablish serial communication with the computer
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;
```

### 2. LED Objects and Counters
Three `DigitalOut` objects are created to control the red, green, and blue LEDs. Additionally, counters are initialized to keep track of the number of interrupts and expected values for each LED.
```cpp
DigitalOut ledR(LED1, 1);
DigitalOut ledG(LED2, 1);
DigitalOut ledB(LED3, 1);

int counterR = 0;
int expected_valueR = 0;

int counterG = 0;
int expected_valueG = 0;

int counterB = 0;
int expected_valueB = 0;
```

### 3. Interrupt Service Routines (ISRs)
The code defines three ISRs, one for each LED. These ISRs toggle the states of the LEDs and increment the corresponding counters. The LED toggling is accomplished by inverting the current LED state.
```cpp
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
```
### 4. Main Function

The main function is where the program starts its execution. Inside the main loop, the code interacts with the user to input the desired blinking rates for each LED. It then creates `Ticker` objects and attaches the previously defined ISRs to these tickers with the specified blinking rates.
The main loop continuously monitors each of the counter values and calculates when was the last time it changed state based on the user-defined blinking rates. This information is printed to the console.
```cpp
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

   tickerR.attach_us(timerR_interrupt, BlinkingRateRed); // Red Led Interruption
   tickerG.attach_us(timerG_interrupt, BlinkingRateGreen); // Green Led Interruption
   tickerB.attach_us(timerB_interrupt, BlinkingRateBlue); // Blue Led Interruption

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
```

# LEDs y Comunicación Serial - Arquitectura de Hardware 2023-2
## Generalidades del Proyecto
Este proyecto demuestra una forma de controlar los tiempos de parpadeo de los tres LEDs (rojo, verde y azul) utilizando el microcontrolador mbed **FRDM-K64F** y el **FRDM-KL25Z**. El código utiliza unos temporizadores controlados por interrupciones para cambiar el estado de los LEDs y calcular en qué momento del temporizador se realizó la interrupción. El código está escrito en C++ y utiliza las funcionalidades de la plataforma de mbed.

## Explicación del Código
Aquí hay una explicación de las secciones del código:

### 1. Inicialización de Comunicación Serial
El código establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial`. Esto permite la interacción con el usuario para ingresar las tasas de parpadeo para cada LED.
```cpp
#include "mbed.h"
#include <iostream>

// Objeto para establecer la comunicación serial con la computadora
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;
```

### 2. Objetos de LED y Contadores
Se crean tres objetos `DigitalOut` para controlar los LEDs rojo, verde y azul. Además, se inicializan contadores para realizar un seguimiento del número de interrupciones y los valores esperados para cada LED.
```cpp
DigitalOut ledR(LED1, 1);
DigitalOut ledG(LED2, 1);
DigitalOut ledB(LED3, 1);

int counterR = 0;
int expected_valueR = 0;

int counterG = 0;
int expected_valueG = 0;

int counterB = 0;
int expected_valueB = 0;
```

### 3. Rutinas de Servicio de Interrupción (ISRs)
El código define tres ISRs, una para cada LED. Estas ISRs cambian los estados de los LEDs e incrementan los contadores correspondientes. El cambio de estado de los LEDs se logra invirtiendo el estado actual del LED.
```cpp
// Funciones de interrupción para cada LED
void timerR_interrupt() {
    ledR = !ledR; // Invierte el estado del LED rojo
    counterR++; 
}

void timerG_interrupt() {
    ledG = !ledG; // Invierte el estado del LED verde
    counterG++; 
}

void timerB_interrupt(){
    ledB = !ledB; // Invierte el estado del LED azul
    counterB++;
}
```

### 4. Función Principal
La función principal es donde el programa comienza su ejecución. Dentro del ciclo principal, el código interactúa con el usuario para ingresar las tasas de parpadeo deseadas para cada LED. Luego, crea objetos `Ticker` y adjunta las ISRs previamente definidas a estos tickers con las tasas de parpadeo especificadas.
El ciclo principal monitorea continuamente los valores de los contadores y calcula cuándo fue la última vez que cambió de estado en función de las tasas de parpadeo definidas por el usuario. Esta información se imprime en la consola.
```cpp
int main()
{
    cout << "Ingrese el tiempo de parpadeo para el LED rojo (en milisegundos): ";
    int BlinkingRateRed;
    cin >> BlinkingRateRed;
    BlinkingRateRed = BlinkingRateRed * 1000;

    cout << "Ingrese el tiempo de parpadeo para el LED verde (en milisegundos): ";
    int BlinkingRateGreen;
    cin >> BlinkingRateGreen;
    BlinkingRateGreen = BlinkingRateGreen * 1000;

    cout << "Ingrese el tiempo de parpadeo para el LED azul (en milisegundos): ";
    int BlinkingRateBlue;
    cin >> BlinkingRateBlue;
    BlinkingRateBlue = BlinkingRateBlue * 1000;

    Ticker tickerR;
    Ticker tickerG;
    Ticker tickerB;

    tickerR.attach_us(timerR_interrupt, BlinkingRateRed);
    tickerG.attach_us(timerG_interrupt, BlinkingRateGreen);
    tickerB.attach_us(timerB_interrupt, BlinkingRateBlue);

    while (true)
    {
        if (expected_valueR != counterR) {
            cout << "RLed = " << BlinkingRateRed / 1000 * counterR << endl;
            expected_valueR = counterR;
        }

        if (expected_valueG != counterG) {
            cout << "GLed = " << BlinkingRateGreen / 1000 * counterG << endl;
            expected_valueG = counterG;
        }

        if (expected_valueB != counterB) {
            cout << "BLed = " << BlinkingRateBlue / 1000 * counterB << endl;
            expected_valueB = counterB;
        }

        ThisThread::sleep_for(1ms);
    }
}
```
