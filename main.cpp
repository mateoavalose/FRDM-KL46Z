#include "mbed.h"
#include "HTU21D.h"
#include "SLCD.h"
#include "HCSR04.h"
#include <cmath>

//Temperature and Humidity Sensor || SDA pin - SCL pin
HTU21D temphumid(A4, A5); 
int sample_ctemp;
int sample_humid;

// HCSR04 Ultrasonic Sensor || Trigg pin - Echo pin
HCSR04 sonar(A1, A0);

// KL46Z SLCD screen
SLCD lcd;

float distanceTemp(int ktemp, int h, float echoTime){
    float R = 8.3144626181532; // Ideal gas constant, for dry air [J/(kg °k)]
    float Mv = 0.0180153; // Molar mass for the air vapor [kg/mol]
    float y = 1.4; // Heat capacity ratio for the air 

    float Ma = 100 * Mv / h;
    float travelTime = echoTime / 1000000;
    float speed =  sqrt((ktemp * R * y) / Ma); // Speed of sound in the air with current temperature
    printf("Speed calculated [m/s]: %.3f \n", speed);
    float distance = (speed * travelTime/2) * 100;

    return distance;
}

int main() {
    while(true) {
        // Read Temperature and Humidity
        sample_ctemp = temphumid.sample_ctemp();
        sample_humid = temphumid.sample_humid();
        // Print Temperature and Humidity data into console
        printf("Temperature: %d C\r", sample_ctemp);
        printf("Humidity: %d %%\n\r", sample_humid);
        
        // Read and calculate distance from sensor
        float echo = sonar.readEcho();
        float distance = distanceTemp(temphumid.sample_ktemp(), temphumid.sample_humid(), echo);
        // Print distance data into console
        //printf("Detected distance from sensor %.6f cm \n", distance);
        printf("Detected distance from sensor %.6f cm \n", sonar.getCm());
        printf("---------------------------------------\n");

        // Print data into KL46Z SLCD screen: Distance in centimeters
        lcd.clear();
        lcd.CharPosition = 0;
        lcd.printf("%.2f", distance);

        ThisThread::sleep_for(1s);
    }
}