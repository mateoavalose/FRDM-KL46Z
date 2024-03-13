# Mateo Avalos & Santiago Toro
#  BusOut y generación de colores con LED RGB - Arquitectura de Hardware 2023-2
## Generalidades del Proyecto


## Explicación del Código
Aquí hay una explicación de las secciones del código:

### 1. Inicialización de Comunicación Serial
El código establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial`. Esto permite la interacción con el usuario para ingresar el código hexadecimal.
```cpp
#include "mbed.h"
#include <iostream>

UnbufferedSerial pc(USBTX, USBRX, 9600);
```
### 2. Objetos BusOut
Se crean el objeto `BusOut` esto permite agrupar varios pines digitales de salida en un solo objeto y manipularlos de manera colectiva.
```cpp
BusOut displayLED(D8, D7, D6, D5, D4, D3, D2);
```
### 3. Función Principal
El programa comienza pidiéndole al usuario que ingrese un número que desea ver representado en un "display de 7 segmentos". Muestra el mensaje `Type the number you
want to see in the 7 segment display: ` para indicarle al usuario que ingrese un número. Declara una variable `int number` para almacenar el número ingresado por el usuario. Utiliza la función `cin >> number;` para esperar a que el usuario ingrese un número desde el teclado. La entrada del usuario se almacena en la variable `number`.

El programa utiliza un switch para determinar qué número ha ingresado el usuario. Cada caso del switch contiene una serie de instrucciones para activar los segmentos LED correspondientes en el "display de 7 segmentos" virtual `displayLED` con el fin de representar visualmente el número ingresado. Después de que se complete un caso
del switch, el programa vuelve al inicio del bucle while y espera una nueva entrada del usuario. Esto permite que el usuario ingrese otro número y vea su representación en el "display de 7 segmentos".
```cpp

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
```
