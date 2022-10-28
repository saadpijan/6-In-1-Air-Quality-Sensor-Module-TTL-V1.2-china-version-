#include <SoftwareSerial.h>

SoftwareSerial Sensor(2,3); // Software serial pin conection RX,TX
char Data[20];

void setup() 
{
  Serial.begin(115200);
  Sensor.begin(9600);   // Sensor works on 9600 baud rate
}

void loop() 
{
sensorEvent();
 
} // void LOOP END


void sensorEvent() {

  
  if (Sensor.available()>=19)
  {
   
  int x= Sensor.readBytes(Data,19);
      Serial.println("Bytes received: ");
  Serial.println(x);
    
   if ( int (Data[0])==1 && int (Data[1])==3 && int (Data[2])==14)
   {


   Serial.print("Data: ");
   //Serial.println(Data[0],HEX);
   for(int i=0; i<=x-1; i++)
   {
  
  Serial.print(Data[i],HEX);
    Serial.print(",");

   }

   }// finding start of data stream
   else
    
    Serial.println(".");
  }
 delay(100);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
   // if (inChar == '\n') {
//    stringComplete = true;
   // }
  }
