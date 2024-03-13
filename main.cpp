#include "mbed.h"
#include "Button.h"
#include "TextLCD.h"

#include <iostream>
#include <string>
#include <math.h>

UnbufferedSerial serial(USBTX, USBRX, 9600);

#define WAITING_TIME 200ms

// External Button Matrix Inicialization
ButtonM butM(4, 4);

// External LCD Inicialization
TextLCD lcd(A0, A1, A2, A3, A4, A5, TextLCD::LCD16x2);

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
    //PwmOut ledB(LED3);

    ledR.period(0.1);
    ledG.period(0.1);
    //ledB.period(0.1);

    // Turn the 0 - 255 values into a 0 - 1 percentage
    float FFRed = 1 - red/255.0;
    float FFGreen = 1 - green/255.0;
    float FFBlue = 1 - blue/255.0;

    // Write a specific color in the LED
    lcd.cls();
    lcd.printf("Red: %d, Green: %d, Blue: %d", red, green, blue);
    ledR.write(FFRed);
    ledG.write(FFGreen);
    //ledB.write(FFBlue);
}

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