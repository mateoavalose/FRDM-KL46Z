# Mateo Avalos & Santiago Toro
#  Examen Final Arquitectura de Hardware
## Generalidades del Proyecto

## Explicación del Código
Aquí hay una explicación de las secciones del código:

### Explicación Codigo cpp
Empezaremos explicando la funcionalidad del codigo realizado en .cpp

### 1. Configuración del entorno 
Esta primera parte, nos ayuda a configurar un entorno para interactuar con un microcontrolador utilizando Mbed y sensores HTU21D y HCSR04 junto con funciones matemáticas estándar para aplicarlo en la medición de temperatura, humedad y distancia.
```cpp
#include "mbed.h"
#include "HTU21D.h"
#include "HCSR04.h"
#include <cmath>
```
Ademas se establece la comunicación serial con la computadora utilizando un objeto `UnbufferedSerial`
```cpp
// Serial Communication
UnbufferedSerial pc(USBTX, USBRX, 9600);
```
 ### 2. Inicializacion de Sensores (mediante objetos)
Este fragmento de código inicializa un objeto del sensor HTU21D para medir temperatura y humedad, junto con variables para almacenar las muestras de temperatura en Celsius y Kelvin. También inicializa un objeto del sensor HCSR04 para medir distancias ultrasónicas.

```cpp
// Temperature and Humidity Sensor || SDA pin - SCL pin
HTU21D temphumid(A4, A5); 
int sample_ctemp;
int sample_ktemp;
int sample_humid;

// HCSR04 Ultrasonic Sensor || Trigg pin - Echo pin
HCSR04 sonar(A1, A0);
```
### 3. Calculos matematicos necesarios (Función)
Esta parte sera explicada por pasos, esto debido a ser la parte matematica del codigo. Para empezar; La función toma tres parámetros: ktemp (temperatura en kelvin), h (humedad) y echoTime (tiempo de eco medido por el sensor ultrasónico en microsegundos).
```cpp
float distanceTemp(int ktemp, int h, float echoTime){
```
Continuando, se definen algunas constantes y parámetros (como la constante del gas ideal, la masa molar para el vapor de aire y la razón de capacidad calorífica para el aire).
```cpp
    float R = 8.3144626181532; // Ideal gas constant, for dry air [J/(kg °k)]
    float Mv = 0.0180153; // Molar mass for the air vapor [kg/mol]
    float y = 1.4; // Heat capacity ratio for the air 
```
Casi finalizando, calcula la masa molar del aire utilizando la fórmula: Ma = 100 * Mv / h, donde Mv es la masa molar del vapor de agua.
```cpp
 float Ma = 100 * Mv / h;
```
Y finalmente, se calcula la velocidad del sonido en el aire utilizando la fórmula de velocidad del sonido en función de la temperatura, la constante del gas ideal y la masa molar del aire. Ademas , calculamos la distancia utilizando la fórmula de distancia basada en la velocidad del sonido y el tiempo de eco, y la devuelve como resultado de la función.
```cpp
    float travelTime = echoTime / 1000000;
    float speed =  sqrt((ktemp * R * y) / Ma); // Speed of sound in the air with current temperature
    float distance = (speed * travelTime/2) * 100;

    return distance;
}
```
### 4. Main
El ejecutor del programa realmente es la parte donde usamos todas las herramientas, anteriormente explicadas. Por ende, la explicaremos por pasos. Empezamos creando un objeto `Timer` llamado time que se utiliza para medir el tiempo. Declaramos una variable `timePassed` inicializada en 0.0 para almacenar el tiempo transcurrido. e inicializamos un objeto DigitalIn llamado button1 que está conectado al pin `PTC3`, para leer el estado del interruptor (boton).
```cpp
 Timer time;
    float timePassed = 0.0;
    DigitalIn button1(PTC3);
```
Pasando a la siguiente parte, realizamos múltiples llamadas a las funciones (sample_ctemp, sample_humid, sample_ktemp) del objeto temphumid, para obtener los datos de temperatura y humedad de los sensores.
```cpp
   // Read and print Temperature and Humidity in Console
    sample_ctemp = temphumid.sample_ctemp();
    sample_humid = temphumid.sample_humid();
    sample_ktemp = temphumid.sample_ktemp();
```
Llegamos al bucle principal, siempre y cuando el interruptor siga presionado. Se lee el valor del eco (echo) proveniente del sensor ultrasónico `sonar.readEcho()` para calcular la distancia. Se calcula el tiempo transcurrido `timePassed` desde que se inició el temporizador. Se llama a una función `distanceTemp()` para calcular la distancia utilizando los valores de temperatura (sample_ktemp), humedad (sample_humid) y el eco del sensor. Se imprime en la consola el tiempo transcurrido `timePassed` y la distancia calculada `distance`.
```cpp
  while(true) {
        while(!button1){
            time.start(); // Start measuring time
            float echo = sonar.readEcho(); // Read and calculate distance from sensor
            timePassed = float(time.elapsed_time().count()) / 1000000;
            float distance = distanceTemp(sample_ktemp, sample_humid, echo);
            printf("%f, %.6f \n", timePassed, distance);
        }
```
Finalmente, Se detiene el temporizador `time.stop()`. Se reinicia el temporizador `time.reset()`. Se pausa la ejecución por 100 milisegundos `ThisThread::sleep_for(100ms)`.
```cpp
 time.stop();
        time.reset();
        ThisThread::sleep_for(100ms);
    }
}
```


### Explicación Codigo .py
El propósito es adquirir datos de tiempo y distancia del dispositivo, visualizar estos datos en un gráfico de dispersión y guardarlos en un archivo CSV utilizando las bibliotecas serial, matplotlib.pyplot, y csv.

## 1. Importación bibliotecas de Python 
`import serial` Esta biblioteca te permite acceder a puertos seriales para la comunicación con dispositivos externos, con esta biblioteca podemos enviar y recibir datos a través de un puerto serie. `import matplotlib.pyplot as plt` Matplotlib es una biblioteca muy utilizada en Python para la visualización de datos. matplotlib.pyplot es un módulo específico que proporciona funciones para crear gráficos y visualizaciones y al importar plt, estámos asignando un alias comúnmente utilizado para este módulo, lo que facilita el uso de sus funciones. Y por ultimo; `import csv` La biblioteca csv brinda funcionalidades para trabajar con archivos CSV (valores separados por comas) en Python.
```cpp
import serial
import matplotlib.pyplot as plt
import csv
```
## 2. Funcion para guardar los datos en csv
Se define una función llamada save_points_to_csv. Esta función toma dos argumentos: `points y filename`. La función tiene la tarea de guardar datos en un archivo CSV. `points` Es una lista de datos. Cada elemento en esta lista representa un conjunto de datos, un par de valores como el tiempo y la distancia. `filename` Es el nombre del archivo en el que se guardarán los datos.
```cpp
def save_points_to_csv(points, filename):
```
Dentro de la funcion: 
```cpp 
with open(filename, 'w', newline='') as file
```
Este bloque de código abre un archivo en modo escritura ('w'). Si el archivo especificado no existe, se creará. Si ya existe, el modo de escritura borrará su contenido existente. El parámetro `newline=''` se utiliza para manejar el formato de nueva línea en el archivo CSV. `csv_writer = csv.writer(file)` Se crea un objeto csv_writer utilizando la función csv.writer() que escribirá en el archivo abierto. `csv_writer.writerow(['time [s]', 'distance [m]'])` Escribe una fila en el archivo CSV que actúa como encabezado. En este caso, los encabezados son 'time [s]' y 'distance [m]'.

## 3. Conexión con el Puerto Serial
En esta sección del código, se está abriendo una conexión con el puerto serial del dispositivo para establecer la comunicación entre el programa Python y el dispositivo. Usando `arduino_port = 'COM4'` para establecer el puerto serial que estamos usando. Y `ser = serial.Serial(arduino_port, baudrate=9600, timeout=2)` lo usamos para especificar el puerto serial al que nos conectamos, la velocidad de comunicacion en baudios y establecemos el tiempo de espera (2 segundos) para la lectura del puerto serial que establecimos con anterioridad
```cpp
# Open a connection to the Arduino's serial port
arduino_port = 'COM4'  # Replace with the actual port of your Arduino
ser = serial.Serial(arduino_port, baudrate=9600, timeout=2)
```

## 4. Creacion de Listas
Está parte trata de la creacion de tres listas vacías que se utilizarán para almacenar los datos adquiridos del dispositivo. Serian las listas para el tiempo: `time_data: float = []`. Distancia:  `distance_data: float = [] ` y el `pointsArr = []` que probablemente se usará para almacenar pares de valores (Esta lista se utilizará más adelante para guardar los datos en un archivo CSV y para generar la visualización gráfica de los datos).
```cpp
# Create empty lists to store data
time_data:float = []
distance_data:float = []
pointsArr = []
```
## 5. Procesamiento de datos desde el puerto serial del Arduino
Este bloque de código lee datos del puerto serial provenientes del dispositivo Arduino. Procesa estos datos dividiéndolos en tiempo y distancia, almacenando aquellos que cumplen con criterios específicos (tiempo entre 0 y 10 segundos, distancia entre 0 y 4000 unidades) en listas separadas (time_data y distance_data). Además, crea una lista pointsArr con pares de tiempo y distancia ajustada (dividida por 100) para su posterior almacenamiento.
```cpp
try:
    data = ser.readline().decode().strip()
    while data:
        # Read data from the Arduino
        print("Data read: " + data)

        # Split the data into time and distance values
        if ',' not in data:
            continue
        time, distance = data.split(',')
        if float(time) > 0 and float(time) < 10 and float(distance) > 0 and float(distance) < 4000:
            pointsArr.append((float(time), float(distance)/100))
            time_data.append(float(time))
            distance_data.append(float(distance))

        data = ser.readline().decode().strip()
```
## 6. Exportación de Datos y Visualización
Este bloque de código guarda los datos recolectados en un archivo CSV llamado "points.csv" utilizando la función save_points_to_csv(). Posteriormente, genera un gráfico de dispersión utilizando matplotlib, representando el tiempo en el eje X y la distancia en el eje Y. Finalmente, muestra el gráfico resultante para visualizar los datos recolectados desde el dispositivo Arduino.
```cpp
   # Export the data 
    output_file = "points.csv"
    
    save_points_to_csv(pointsArr, output_file)

    # Plot the data
    plt.scatter(time_data, distance_data)
    plt.xlabel('Time (s)')
    plt.ylabel('Distance (cm)')
    plt.show()
except KeyboardInterrupt:
    # Close the serial port when the script is interrupted
    ser.close()
```




