# Mateo Avalos & Santiago Toro
# PWM and color generation with RBG LED - Hardware Architecture 2023-2
## Project Overview
This project uses the `Pulse-Width Modulation (PWM)` function to generate a color on the RGB LED of the mbed microcontroller **FRDM-K64F** and **FRDM-KL25Z**. The code receives a hexadecimal code of the desired color, obtains the numerical value of each color and writes them to each color of the LED. The code is written in C++ and uses the functionalities of the mbed platform.

## Code Explanation
Here's a breakdown of the code's sections:

### 1. Serial Communication Initialization
The code establishes serial communication with the computer using an `UnbufferedSerial` object. This enables interaction with the user to input the hexadecimal code.
```cpp
#include "mbed.h"
#include <iostream>

UnbufferedSerial pc(USBTX, USBRX, 9600);
```

### 2. PwmOut Objects
Three `PwmOut` objects are created to control the time period that the LEDs are going to be on, and so, be able to control the apparent intensity for each component of the RGB LED.
```cpp
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);
```

### 3. Main Function
The first thing the main function does is set the pulse-width modulation (PWM) period for each color of the RGB LED. The main function consists of an infinite loop that asks the user to enter a hexadecimal value that represents a color, and then checks if the user entered the corresponding **'#'** code. If so, it removes it.

Then it uses the `std::stoi` function to convert the hexadecimal code to an integer value: the code string is passed and it is specified that it is in base 16. With this value obtained and using `bitwise` with `bitshifting`, the value of each color (red, green and blue) is extracted in its form from 0 to 255. What is done in the `hexValue >> 16` instruction is to shift the bits of **hexValue** 16 positions to the right, discarding the green and blue values in **hexValue**. After, the `& 0xFF` operation performs a **bitwise** and an operation with **_0xFF_**, which results in only keeping the last 8 most significant bits, the red component. Similarly, the values for green and blue are extracted, but modifying the number of bits that **hexValue** will be shifted and keeping the 8 most significant bits.

To convert the values of each color to a percentage, they are divided by 255 and that value is subtracted from 1, to have the complement and compensate for the reverse logic of **C++**.

To finish, the values of each color are printed on the screen, and they are written with the `.write()` function to specify the percentage of the period that the LED will be on.

```cpp
int main() {
  // Define the LED periods
  ledR.period(0.1);
  ledG.period(0.1);
  ledB.period(0.1);

  while (true) {
    // Ask for the RGB value
    cout << "Enter a Hexadecimal value: " << endl;
    string hexCode;
    cin >> hexCode;

    // Remove the '#' character from the hexadecimal code
    if (hexCode[0] == '#')
      hexCode.erase(0, 1);

    // Convert the hexadecimal code to integer
    int hexValue = std::stoi(hexCode, nullptr, 16);

    // Extract the red, green, and blue values using bitwise operations and bit shifting
    int red = (hexValue >> 16) & 0xFF;
    int green = (hexValue >> 8) & 0xFF;
    int blue = hexValue & 0xFF;

    // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red / 255.0;
    float FFGreen = 1 - green / 255.0;
    float FFBlue = 1 - blue / 255.0;

    // Write a specific color in the LED
    cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
    ledR.write(FFRed);
    ledG.write(FFGreen);
    ledB.write(FFBlue);
    cout << "------------------------------" << endl;
  }
}
```

---

#  PWM y generación de colores con LED RGB - Arquitectura de Hardware 2023-2
## Generalidades del Proyecto
Este proyecto utiliza la función de `Modulación por Ancho de Pulsos (PWM)` para generar un color en el LED RGB de el microcontrolador mbed **FRDM-K64F** y el **FRDM-KL25Z**. El código recibe un código hexadecimal del color deseado, obtiene el valor numérico de cada color y los escribe a cada color del LED. El código está escrito en C++ y utiliza las funcionalidades de la plataforma de mbed.

## Explicación del Código
Aquí hay una explicación de las secciones del código:

### 1. Inicialización de Comunicación Serial
El código establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial`. Esto permite la interacción con el usuario para ingresar el código hexadecimal.
```cpp
#include "mbed.h"
#include <iostream>

UnbufferedSerial pc(USBTX, USBRX, 9600);
```

### 2. Objetos PwmOut
Se crean tres objetos `PwmOut` para controlar qué tiempo del periodo estarán prendidos los LEDs, y así, controlar la intensidad aparente de cada componente del LED RGB.
```cpp
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);
```

### 3. Función Principal
Lo primero que hace la función principal es ajustar el período de modulación de ancho de pulso (PWM) para cada color del LED RGB. La función principal consta con un ciclo infinito que le solicita al usuario ingresar un valor hexadecimal que represente un color, y luego verifica si el usuario ingresó el **'#'** correspindieinte al código. De ser así, lo elimina. 

Luego utiliza la función `std::stoi` para convertir el código hexadecimal a un valor entero: se entrega el _string_ del código y se especifíca que está en base 16. Con este valor obtenido y utilizando `bitwise` con `bitshifting`, se extrae el valor de cada color (rojo, verde y azul) en su valor de 0 a 255. Lo que se hace en la instrucción de `hexValue >> 16` es correr los bits de **hexValue** 16 posiciones a la derecha, descartando los valores de verde y azul en **hexValue**. Después, la operación `& 0xFF` realiza un **bitwise** y una operación con **_0xFF_**, lo que resulta en solo mantener los últimos 8 bits más significantes, el componente rojo. Así mismo, se extraen los valores para el verde y el azul, pero modificando la candidad de bits que se correrá **hexValue** y manteniendo los 8 bits más significativos.

Para convertir los valores de cada color a un porcentaje, se dividen entre 255 y se resta ese valor de 1, para tener el complemento y compensar la lógica inversa de **C++**.

Para terminar se imprime por consola los valores de cada color, y se escriben con la función `.write()` para especificar el porcentaje de el periodo que el LED estará encendido. 
```cpp
int main() {
  // Define the LED periods
  ledR.period(0.1);
  ledG.period(0.1);
  ledB.period(0.1);

  while (true) {
    // Ask for the RGB value
    cout << "Enter a Hexadecimal value: " << endl;
    string hexCode;
    cin >> hexCode;

    // Remove the '#' character from the hexadecimal code
    if (hexCode[0] == '#')
      hexCode.erase(0, 1);

    // Convert the hexadecimal code to integer
    int hexValue = std::stoi(hexCode, nullptr, 16);

    // Extract the red, green, and blue values using bitwise operations and bit shifting
    int red = (hexValue >> 16) & 0xFF;
    int green = (hexValue >> 8) & 0xFF;
    int blue = hexValue & 0xFF;

    // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red / 255.0;
    float FFGreen = 1 - green / 255.0;
    float FFBlue = 1 - blue / 255.0;

    // Write a specific color in the LED
    cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
    ledR.write(FFRed);
    ledG.write(FFGreen);
    ledB.write(FFBlue);
    cout << "------------------------------" << endl;
  }
}
```
