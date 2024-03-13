#include "mbed.h"
#include "HTU21D.h"
#include "HCSR04.h"
#include <cmath>

// Serial Communication
UnbufferedSerial pc(USBTX, USBRX, 9600);

// Temperature and Humidity Sensor || SDA pin - SCL pin
HTU21D temphumid(A4, A5); 
int sample_ctemp;
int sample_ktemp;
int sample_humid;

// HCSR04 Ultrasonic Sensor || Trigg pin - Echo pin
HCSR04 sonar(A1, A0);

// Function to calculate distance with temperature and humidity
float distanceTemp(int ktemp, int h, float echoTime){
    float R = 8.3144626181532; // Ideal gas constant, for dry air [J/(kg °k)]
    float Mv = 0.0180153; // Molar mass for the air vapor [kg/mol]
    float y = 1.4; // Heat capacity ratio for the air 

    float Ma = 100 * Mv / h;
    float travelTime = echoTime / 1000000;
    float speed =  sqrt((ktemp * R * y) / Ma); // Speed of sound in the air with current temperature
    float distance = (speed * travelTime/2) * 100;

    return distance;
}

int main() {
    Timer time;
    float timePassed = 0.0;
    DigitalIn button1(PTC3);
    // Read and print Temperature and Humidity in Console
    sample_ctemp = temphumid.sample_ctemp();
    sample_humid = temphumid.sample_humid();
    sample_ktemp = temphumid.sample_ktemp();
    
    while(true) {
        while(!button1){
            time.start(); // Start measuring time
            float echo = sonar.readEcho(); // Read and calculate distance from sensor
            timePassed = float(time.elapsed_time().count()) / 1000000;
            float distance = distanceTemp(sample_ktemp, sample_humid, echo);
            printf("%f, %.6f \n", timePassed, distance);
        }
        time.stop();
        time.reset();
        ThisThread::sleep_for(100ms);
    }
}