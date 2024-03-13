# Mateo Avalos & Santiago Toro
#  Examen Parcial, con implementación de librerias (LCD y Teclado Matricial) - Arquitectura de Hardware 2023-2

## Generalidades del Proyecto
Este proyecto es la implementacion del codigo que se realizo para el examen   parcial, pero optimizado para el uso de las librerias (LCD Y Teclado) creadas con anterioridad 

## Explicación del Código
Aquí hay una explicación de las secciones del código:

### 1. Inclusión de bibliotecas y encabezados necesarios 
Estas líneas de código sirven para configurar las bibliotecas y encabezados necesarios para el programa, se incluyen obviamente las librerias que tuvimos que crear con antelacion. Tambien se establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial` ; Esto permite la interacción con el usuario para ingresar el código hexadecimal. 
```cpp
#include "mbed.h"
#include "Button.h"
#include "TextLCD.h"

#include <iostream>
#include <string>
#include <math.h>

UnbufferedSerial serial(USBTX, USBRX, 9600);
```
### 2. Inicializacion de Objetos
Estas líneas de código inicializan objetos que permiten interactuar con la matriz de botones externa y la pantalla LCD. Estos objetos (butM y lcd) se utilizarán más adelante en el programa para leer la entrada de los botones y mostrar información en la pantalla LCD.
```cpp
// External Button Matrix Inicialization
ButtonM butM(4, 4);

// External LCD Inicialization
TextLCD lcd(A0, A1, A2, A3, A4, A5, TextLCD::LCD16x2);
```
### 3. Función: Raices de un Polinomio
Esta primera parte de la funcion estae destinada a recopilar los coeficientes de un polinomio cuadrático (a, b y c) de un usuario a través de la pantalla LCD y almacenarlos en las variables `a`, `b` y `c`.
```cpp
//First Application
 void poliRoots(){
    lcd.cls();
    lcd.printf("ingrese el valor 'a'");
    int a = std::stoi(butM.readStringInput());
    lcd.cls();
    lcd.printf("valor de 'a' es: %d", a);
    ThisThread::sleep_for(5s);

    lcd.cls();
    lcd.printf("ingrese el valor 'b'");
    int b = std::stoi(butM.readStringInput());
    lcd.cls();
    lcd.printf("valor de 'b' es: %d", b);
    ThisThread::sleep_for(5s);

    lcd.cls();
    lcd.printf("ingrese el valor 'c'");
    int c = std::stoi(butM.readStringInput());
    lcd.cls();
    lcd.printf("valor de 'c' es: %d", c);
    ThisThread::sleep_for(5s);
    lcd.cls();

```
La siguiente parte del codigo, es el proceso matematico que se encarga de calcular las raices del polinomio; de acuerdo a los parametros a,b y c que se digitaron mediante el teclado anteriormente. Al final, la funcion utiliza el `lcd.printf(...);` para mostrar en la pantalla del LCD, las raices del polinomio. 
```cpp
 double discr = b*b - 4*a*c;
    if(discr >= 0){
        double x1 = (-b + sqrt(discr))/(2*a);
        double x2 = (-b - sqrt(discr))/(2*a);
        lcd.printf("raices: %f, %f", x1, x2);
    } else {
        double x1a = -float(b)/(2*a);
        double x1b = sqrt(abs(discr))/(2*a);
        double x2a = -float(b) /(2*a);
        double x2b = -sqrt(abs(discr))/(2*a);
        lcd.printf("raices: %f+(%f)i, %f+(%f)i", x1a, x1b, x2a, x2b);
    }
}
```
### 4. Función: Notas
Esta parte del codigo es la funcion que nos permite digitar y analizar notas. En resumen, la función permite al usuario ingresar una nota y le proporciona una calificación basada en los rangos establecidos en las condiciones if-else. Un agregado de esta funcion es el bucle infinito; este asegura que el usuario pueda ingresar múltiples notas y obtener calificaciones una tras otra hasta que la función se detenga manualmente.
```cpp
//Second Application
void Grades(){
    while(true){
        lcd.cls();
        lcd.printf("ingrese una nota:");
        int N = std::stoi(butM.readStringInput());
        lcd.cls();
        if(0 <= N && N <= 3){
            lcd.printf("Su nota es A");
        } else if(3 < N && N <= 4){
            lcd.printf("Su nota es B");
        } else if(4 < N && N <= 5){
            lcd.printf("Su nota es C");
        } else if(5 < N && N <= 7){
            lcd.printf("Su nota es D");
        } else if(7 < N && N < 9){
            lcd.printf("Su nota es E");
        } else if(9 <= N && N <= 10) {
            lcd.printf("Su nota es F");
        } else {
            lcd.printf("nota ingresada  no es valida");
        }
        ThisThread::sleep_for(5s);
    }
}
```
### 5. Función: RGB LED
La ultima funcion del codigo, esta diseñada para controlar un `LED RGB` a través de tres pines `PWM` , uno para cada componente de color: rojo, verde y azul. La primera parte del codigo, empieza pidiendo los valores RGB por separado, La función espera a que el usuario proporcione una entrada numérica a través del teclado matricial, y luego convierte la entrada en un entero y lo almacena en la variable `int red = std::stoi(butM.readStringInput());`. Luego, se borra la pantalla LCD y se repiten los mismos pasos para los componentes de color verde y azul.
```cpp
//Third Application
void RGBLED(){
    lcd.cls();
    lcd.printf("valor de rojo: ");
    int red = std::stoi(butM.readStringInput());
    lcd.cls();
    lcd.printf("valor de verde: ");
    int green = std::stoi(butM.readStringInput());
    lcd.cls();
    lcd.printf("valor de azul: ");
    int blue = std::stoi(butM.readStringInput());

    PwmOut ledR(LED_RED);
    PwmOut ledG(LED_GREEN);
    PwmOut ledB(LED3);
```
Para la siguiente parte de la funcion, primero se establece el período de los objetos ledR, ledG y ledB en 0.1, lo que determina la frecuencia de la señal PWM que controla los componentes de color rojo, verde y azul del LED RGB.
```cpp
    ledR.period(0.1);
    ledG.period(0.1);
    ledB.period(0.1);
```
Luego se calculan los valores de intensidad normalizados para los componentes de color rojo, verde y azul (FFRed, FFGreen y FFBlue) dividiendo los valores proporcionados por el usuario por 255.0 y restando el resultado de 1.0. Esto convierte los valores de 0-255 en un rango de 0 a 1. Por ultimo se muestra en la pantalla LCD los valores de los componentes de color rojo, verde y azul proporcionados por el usuario, Se utiliza el método `write()` de los objetos ledR, ledG y ledB para establecer la intensidad de los componentes de color rojo y verde del LED RGB. Los valores normalizados FFRed, FFGreen y FFBlue se utilizan para controlar la intensidad de estos componentes.

```cpp
   // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red/255.0;
    float FFGreen = 1 - green/255.0;
    float FFBlue = 1 - blue/255.0;

    // Write a specific color in the LED
    lcd.cls();
    lcd.printf("Red: %d, Green: %d, Blue: %d", red, green, blue);
    ledR.write(FFRed);
    ledG.write(FFGreen);
    ledB.write(FFBlue);
}
```
### 6. Main
El Main, es la parte que controla todas las opciones; realmente es facil entender el codigo. El codigo empieza mostrando las diferentes opciones en la pantalla LCD. "1: raices de un polinomio", "2: clasificacion de las notas" y "3: color desde  codigos rgb". Luego de que la pantalla termina de mostrar estos mensajes, se queda estatico en el mensaje "ingrese la opcion deseada" hasta que el sistema registre una respuesta.
```cpp
int main()
{
    lcd.cls();
    lcd.printf("1: raices de un polinomio");
    ThisThread::sleep_for(3s);
    lcd.cls();
    lcd.printf("2: clasificacion de las notas");
    ThisThread::sleep_for(3s);
    lcd.cls();
    lcd.printf("3: color desde  codigos rgb");
    ThisThread::sleep_for(3s);
    lcd.cls();
    lcd.printf("ingrese la opcion deseada");
    char option = butM.readCharInput();
    lcd.cls();

```
Para terminar, se implementa una estructura if-else para determinar qué función ejecutar en función de la opción ingresada por el usuario. Las opciones se corresponden con las tres funcionalidades mencionadas:
-Si el usuario ingresa '1', se ejecuta la función poliRoots() para calcular las raíces de un polinomio.
-Si el usuario ingresa '2', se ejecuta la función Grades() para clasificar notas.
-Si el usuario ingresa '3', se ejecuta la función RGBLED() para controlar un LED RGB.
```cpp
  if(option == '1'){
        lcd.printf("raices de un polinomio");
        ThisThread::sleep_for(3s);
        poliRoots();
    } else if(option == '2'){
        lcd.printf("clasificacion de notas");
        ThisThread::sleep_for(3s);
        Grades();
    } else if(option == '3'){
        lcd.printf("color rgb");
        ThisThread::sleep_for(3s);
        RGBLED();
    }
}
```


