import serial
import matplotlib.pyplot as plt
import csv

# Save data into csv
def save_points_to_csv(points, filename):
    with open(filename, 'w', newline='') as file:
        csv_writer = csv.writer(file)
        csv_writer.writerow(['time [s]', 'distance [m]'])  # Write header
        for point in points:
            csv_writer.writerow(point)

# Open a connection to the Arduino's serial port
arduino_port = 'COM4'  # Replace with the actual port of your Arduino
ser = serial.Serial(arduino_port, baudrate=9600, timeout=2)

# Create empty lists to store data
time_data:float = []
distance_data:float = []
pointsArr = []

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