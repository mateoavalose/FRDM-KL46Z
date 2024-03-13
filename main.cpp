/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include <iostream>
#include <string>
#include <math.h>
#include "mbed.h"

UnbufferedSerial serial(USBTX, USBRX, 9600);

// Detects input
BusIn Row(D11, D10, D9, D8);
// Cycles the columns
BusOut Col(D5, D6, D7);

#define WAITING_TIME 200ms

//Function to read the keyboard input
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

//First Application
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

    double discr = b*b - 4*a*c;
    if(discr >= 0){
        double x1 = (-b + sqrt(discr))/(2*a);
        double x2 = (-b - sqrt(discr))/(2*a);
        std::cout << "Los valores de las raices del polinomio son: " << x1 << " y " << x2 << endl;
    } else {
        double x1a = -float(b)/(2*a);
        double x1b = sqrt(abs(discr))/(2*a);
        double x2a = -float(b) /(2*a);
        double x2b = -sqrt(abs(discr))/(2*a);
        std::cout << "Sus raices son imaginarias. Los valores de las raices del polinomio son: " << '(' << x1a << ')' << '+' << '(' << x1b << "i) y " << '(' << x2a << ')' << '+' << '(' << x2b << "i)" << endl;
    }
}

//Second Application
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

//Third Application
void RGBLED(){
    std::cout << "Ingrese el valor de rojo (0 - 255): " << endl;
    int red = std::stoi(readKeyboard());
    std::cout << "Ingrese el valor de verde (0 - 255): " << endl;
    int green = std::stoi(readKeyboard());
    std::cout << "Ingrese el valor de azul (0 - 255): " << endl;
    int blue = std::stoi(readKeyboard());

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
    cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << endl;
    ledR.write(FFRed);
    ledG.write(FFGreen);
    //ledB.write(FFBlue);
}

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