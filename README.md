# 6-In-1-Air-Quality-Sensor-Module-TTL-V1.2-china-version-
Air quality sensor china made module

# Function: 
Detect real-time data of CO2, formaldehyde, TVOC, PM2.5 and temperature and humidity in the environment

# 1. Product function description
Six-pass sense module is a collection of CO2s, laser dust, temperature and humidity, TVOC integrated air mass sensor and formaldehyde in one. Can be in the ring
Real-time detection in the environment, and output data through a certain protocol format, easy to use, with good stability.

# 2. Product application areas: 
Portable meters, vehicle-mounted systems, air quality monitoring equipment, air purifiers, fresh air ventilation systems, air conditioners, smart home equipment and other places.

![image](https://user-images.githubusercontent.com/19863113/198674782-dad6c4dc-0b1e-4f95-b114-8b3b10086a5b.png)

## The CO2 value and CH2O measured by the module are the equivalent value output of TVOC , please pay attention when using or purchasing .

1. Working voltage: DC5V±0.2V (The ripple must not exceed 200mv )
2. Working current : ≤125mA
3. Working environment: working temperature 0~50℃ working humidity: 15%RH-90 % RH (non-condensing)
4. Communica_on method: serial port output data 1S/ _me (data transmission cycle can be changed by instruc_ons )
5. Warm-up _me : ≤3 minutes
6. Service life: 5 years (in the air )

# Wiring definition

![63468-02](https://user-images.githubusercontent.com/19863113/198675459-0c71718a-9405-402b-a7fa-50a4fff8386c.jpg)

![image](https://user-images.githubusercontent.com/19863113/198675550-82489b0f-eff6-4c7f-846b-a1eb35f860c3.png)

# Product communication protocol
Serial TTL communica_on protocol ( 9600 , parity bit, none, stop bit, 1 bit ) data transmission cycle: default 1s (can be changed)

The length of the CRC check byte is: 17 (that is, the bytes of sequence number 1 to sequence number 17). Select A001 or 8005 in reverse order.

Data format (module -> user MCU) 
Message header (1 Byte) + func_on code (1Byte) + data length (1Byte) + data (n Byte) + CRC16 check (2Byte)

# data calculation method is as follows:
![image](https://user-images.githubusercontent.com/19863113/198676175-bccf3350-405d-4432-afb9-c7785d14e1be.png)

![image](https://user-images.githubusercontent.com/19863113/198676213-6f35546b-0c69-49a5-84bc-243009292e86.png)

## Modify the data transmission cycle format (the maximum can only be changed to 10 seconds)

# Code

I have made two different codes in arduino
File name SensorReading.ino provides you raw value coming directly from the sensor.

File name SensorReadingComplete.ino provides you filtered data from the raw value gives a real output.

# Ouput result

![WhatsApp Image 2020-11-16 at 11 07 06 AM](https://user-images.githubusercontent.com/19863113/198679331-205a60f3-7e46-467c-a578-22ca7cb6673c.jpeg)
