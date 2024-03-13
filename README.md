# Mateo Avalos & Santiago Toro
#  Examen Parcial Arquitectura de Hardware
## Generalidades del Proyecto

## Explicación del Código
Aquí hay una explicación de las secciones del código:

### 1. Inicialización de Comunicación Serial
El código empieza importando las respectivas librerias que se usaran a lo largo del codigo, ademas establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial`. Esto permite la interacción con el usuario para ingresar el código hexadecimal.
```cpp

#include <iostream>
#include <string>
#include <math.h>
#include "mbed.h"

UnbufferedSerial serial(USBTX, USBRX, 9600);
```

### 2. Objetos BusOut y BusIn
Se crean los objetos `BusOut` y `BusIn` esto permite agrupar varios pines digitales de salida y de entrada en un solo objeto y manipularlos de manera colectiva.
En este caso, nuestros pines seran las filas y columnas del teclado matricial
```cpp

// Detects input
BusIn Row(D11, D10, D9, D8);
// Cycles the columns
BusOut Col(D5, D6, D7);

```
### 3. Definir Funcion Interactiva/Teclado Matricial
Este código es una función diseñada para interactuar con un teclado matricial. Su objetivo es leer las teclas presionadas en el teclado y registrarlas como una secuencia de caracteres. El bucle principal se ejecuta indefinidamente hasta que se presiona el asterisco `*` en el teclado, siendo esta una tecla especial que indica que se ha completado la entrada de datos; Cuando el código detecta que se ha presionado el `*` en el teclado matricial, rompe el bucle y devuelve la secuencia de teclas ingresadas hasta ese momento como una cadena de caracteres.
```cpp

string readKeyboard(){
    string input = "";
    string lastInput = "";
    while (true) {
    // D7 ON
    Col.write(0b011);
    if (Row.read() == 0b0111) {
      input = '1';
      std::cout << "1" << endl;
      while (Row.read() == 0b0111);
    } else if (Row.read() == 0b1011) {
      input = '4';
      std::cout << "4" << endl;
      while (Row.read() == 0b1011);
    } else if (Row.read() == 0b1101) {
      input = '7';
      std::cout << "7" << endl;
      while (Row.read() == 0b1101);
    } else if (Row.read() == 0b1110) {
      input = '*';
      std::cout << "*" << endl;
      while (Row.read() == 0b1110);
    }

    // D6 ON
    Col.write(0b101);
    if (Row.read() == 0b0111) {
      input = '2';
      std::cout << "2" << endl;
      while (Row.read() == 0b0111);
    } else if (Row.read() == 0b1011){
        input = '5';
        std::cout << "5" << endl;
        while (Row.read() == 0b1011);
    } else if (Row.read() == 0b01101){
       input = '8';
       std::cout << "8" << endl;
       while (Row.read() == 0b1101);
    } else if (Row.read() == 0b1110){
        input = '0';
        std::cout << "0" << endl;
        while (Row.read() == 0b1110);
    }

    // D5 ON
    Col.write(0b110);
    if (Row.read() == 0b0111){
        input = '3';
        std::cout << "3" << endl;
        while (Row.read() == 0b0111);
    } else if (Row.read() == 0b1011){
        input = '6';
        std::cout << "6" << endl;
        while (Row.read() == 0b1011);
    } else if (Row.read() == 0b01101){
        input = '9';
        std::cout << "9" << endl;
        while (Row.read() == 0b1101);
    } else if (Row.read() == 0b1110){
        input = '-';
        std::cout << "#" << endl;
        while (Row.read() == 0b1110);
    }
    ThisThread::sleep_for(1s);
    if(input[0] == '*')
        break;
    lastInput += input;
    
  }
  std::cout << lastInput << " returned from readkeyboard" << endl;
  return lastInput;
}

```
## 4. Funcion para El Primer Punto
En esta parte del código, se calculan las raíces de un polinomio cuadrático de la forma `ax^2 + bx + c = 0`, donde el usuario ingresa los valores de los coeficientes `a`, `b`, y `c` desde el teclado matricial.
```cpp

void poliRoots(){
    std::cout << "Ingrese el valor 'a' del polinomio" << endl;
    int a = std::stoi(readKeyboard());
    std::cout << "El valor ingresado para 'a' es de: " << a << endl;

    std::cout << "Ingrese el valor 'b' del polinomio" << endl;
    int b = std::stoi(readKeyboard());
    std::cout << "El valor ingresado para 'b' es de: " << b << endl;

    std::cout << "Ingrese el valor 'c' del polinomio" << endl;
    int c = std::stoi(readKeyboard());
    std::cout << "El valor ingresado para 'c' es de: " << c << endl;
```

Al terminal el registro de los datos mediante el teclado matricial, el codigo procede a realizar los calculos pertinentes, y devuelve los resultados en la consola.
```cpp

    double discr = b*b - 4*a*c;
    if(discr >= 0){
        double x1 = (-b + sqrt(discr))/(2*a);
        double x2 = (-b - sqrt(discr))/(2*a);
        std::cout << "Los valores de las raices del polinomio son: " << x1 << " y " << x2 << endl;
    } else {
        double x1a = -b/(2*a);
        double x1b = sqrt(abs(discr))/(2*a);
        double x2a = -b /(2*a);
        double x2b = -sqrt(abs(discr))/(2*a);
        std::cout << "Sus raices son imaginarias. Los valores de las raices del polinomio son: " << '(' << x1a << ')' << '+' << '(' << x1b << "i) y " << '(' << x2a << ')' << '+' << '(' << x2b << 'i)' << endl;
    }
}
```
## 5. Funcion para El Segundo Punto
En esta parte, el código solicita al usuario ingresar una nota (valor numérico entre 0-10) a través del teclado matricial y luego muestra un mensaje correspondiente a la calificación que representa esa nota, bajo los parametros establecidos en el tema del examen parcial. 
```cpp

void Grades(){
    while(true){
        int N = std::stoi(readKeyboard());
        if(0 <= N && N <= 3){
            std::cout << "Su nota es A" << endl;
        } else if(3 < N && N <= 4){
            std::cout << "Su nota es B" << endl;
        } else if(4 < N && N <= 5){
            std::cout << "Su nota es C" << endl;
        } else if(5 < N && N <= 7){
            std::cout << "Su nota es D" << endl;
        } else if(7 < N && N < 9){
            std::cout << "Su nota es E" << endl;
        } else if(9 <= N && N <= 10) {
            std::cout << "Su nota es F" << endl;
        } else {
            std::cout << "La nota ingresada no es valida" << endl;
        }
    }
}
```
## 6. Funcion para El Tercer Punto
Esta parte del código es una función que permite al usuario ingresar valores de intensidad para los componentes de color rojo, verde y azul (RGB) de un LED, este valor debe ser entre 0-255.
```cpp

void RGBLED(){
    std::cout << "Ingrese el valor de rojo (0 - 255): " << endl;
    int red = std::stoi(readKeyboard());
    std::cout << "Ingrese el valor de verde (0 - 255): " << endl;
    int green = std::stoi(readKeyboard());
    std::cout << "Ingrese el valor de azul (0 - 255): " << endl;
    int blue = std::stoi(readKeyboard());
```
Siguiendo el procedimiento, se configura la salida `PWM (modulación por ancho de pulso)` para los LEDs rojo, verde y azul (ledR, ledG y LedB) utilizando la clase PwmOut, tambien se le establece un período de 0.1 para la modulación `PWM `.
```cpp
    PwmOut ledR(LED_RED);
    PwmOut ledG(LED_GREEN);
    PwmOut ledB(LED3);

    ledR.period(0.1);
    ledG.period(0.1);
    ledB.period(0.1);
```
Para finalizar la funcion convierte los valores ingresados (recordar que es de 0-255) mediante operaciones matematicas, a un rango de 0-1, representando al final un porcentaje de intensidad. Ademas, Se muestra en la consola el valor ingresado para cada componente de color (rojo, verde y azul) esto ultimo es con el fin de mostrar que efectivamente si se ingresaron los valores deseados.  
La intensidad del LED rojo se establece utilizando el valor convertido de FFRed, la intensidad del LED verde se establece utilizando FFGreen y la intensidad del LED azul se establece utilizando FFBlue; con las funciónes `ledR.write()`, `ledG.write()` y `ledB.write()`.
```cpp
 // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red/255.0;
    float FFGreen = 1 - green/255.0;
    float FFBlue = 1 - blue/255.0;

    // Write a specific color in the LED
    cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
    ledR.write(FFRed);
    ledG.write(FFGreen);
    ledB.write(FFBlue);
```
## 7. Funcionamiento del Main
El main del programa presenta un menú de opciones en la consola y permite al usuario seleccionar una de las tres opciones disponibles (mediante el teclado matricial). Cada opción corresponde a una funcionalidad diferente. Siendo estas:

`-Raíces de un Polinomio:` Si el usuario elige la opción `1`, el programa calculará las raíces de un polinomio y mostrará los resultados.

`-Clasificación de Notas:` Si el usuario elige la opción `2`, el programa le permitirá ingresar una nota y luego mostrará la calificación correspondiente (A, B, C, etc).

`-Color RGB:` Si el usuario elige la opción `3`, el programa permitirá al usuario configurar la intensidad de tres colores (rojo, verde y azul) para un LED RGB y mostrará el resultado de la configuración.
```cpp
int main()
{
    std::cout << "Ingrese la opcion deseada en el teclado: " << endl;
    string option = readKeyboard();

    if(option == "1"){
        std::cout << "Raices de un Polinomio" << endl;
        poliRoots();
    } else if(option == "2"){
        std::cout << "Clasificacion de Notas" << endl;
        Grades();
    } else if(option == "3"){
        std::cout << "Color RGB" << endl;
        RGBLED();
    }
    //ThisThread::sleep_for(WAITING_TIME);
    
}
```

