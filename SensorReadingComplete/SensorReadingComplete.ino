#include <SoftwareSerial.h>

SoftwareSerial Sensor(2,3); // Software serial pin conection RX,TX
unsigned char Data[20]="";
 int FData[8]; // calculated data 
String Vale[]={"CO2 = ", "TVOC = ", "CH2O = ", "PM2.5 = ", "Hum = ", "Temp = ","PM10 = ",};
//char calData[8];
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
 
uint16_t crc16(unsigned char pushMsg[],int MsgLen);
char sensorReading();

/* CRC check table low bit */ unsigned char auchCRCLo [ ] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC ,0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55 ,0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};

/*CRC check table high order */
unsigned char auchCRCHi [ ] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41 ,0x40, 0x81, 0x40 ,0xC1 ,0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x40, 0x81, 0x40, 0xC1 ,0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x40, 0x81, 0x40, 0xC1 ,0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x40, 0x81, 0x40, 0xC1 ,0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 
0x40
};

void setup() 
{
  Serial.begin(115200);
  Sensor.begin(9600);   // Sensor works on 9600 baud rate
}

void loop() 
{

 sensorReading();

 
}// void Loop END




char sensorReading()
{

 if (Sensor.available()>=19)
  {
        Serial.println("Start");
  Serial.println(millis());
  int x= Sensor.readBytes(Data,19);
      Serial.println("Bytes received: ");
  Serial.println(x);
      Serial.print("Data: ");
     for(int i=0; i<=x-1; i++)
     { 
      Serial.print(Data[i],HEX);
      Serial.print(",");
     }

   if ( int(Data[0])==1 && int(Data[1])==3 && int(Data[2])==14)
   {
      // checking CRC
       uint16_t calculated_CRC,checkSum;
       checkSum=(Data[18] << 8 | Data[17]); // creating 16bit value
       calculated_CRC = crc16(Data, 14);
//         Serial.print(" Calculated CRC:  ");    
//         Serial.print( calculated_CRC, HEX );
//         Serial.print(" Recived CheckSum:  ");    
//         Serial.print(checkSum,HEX );
//         Serial.println( calculated_CRC == checkSum ? " -- passed." : " -- error.");
    
/// **************calculating and displaying calcuated data************//
        //"CO2":
           FData[0]=(Data[3]*256)+ Data[4];
       // "TVOC":
           FData[1] = ((Data[5]*256)+ Data[6])/10.0; 
       // "CH2O":
           FData[2] = ((Data[7]*256)+ Data[8])/10.0; 
      // "PM2.5":
          FData[3]=(Data[9]*256)+ Data[10];  
      // "Humidity":
            int Srh= (Data[11]*256)+ Data[12];
           FData[4]=(119*Srh)/pow(2,16);
      // "Temperature":
           int Stem= (Data[13]*256)+ Data[14];
           FData[5]=(128.87*Stem)/pow(2,16);
      //"PM10":
           FData[6]=(Data[15]*256)+ Data[16];

          for(int i=0; i<=7-1; i++)
           {
            Serial.print( Vale[i]);
            Serial.print(FData[i]);
            Serial.print(",");
           }
//         break;
      Serial.println("Stop");
  Serial.println(millis());
   }// finding start of data stream
   else
    Serial.print(" Did not Match Packet ");    
    Serial.println(".");
  }
//delay(100);
 
}// sensorReading END


uint16_t crc16(unsigned char pushMsg[], int MsgLen)
{
 unsigned int uIndex;
  uint8_t uchCRCLo= 0xff;
  uint8_t uchCRCHi= 0xff;
  unsigned int i = 0;;

while(MsgLen--)
{
  uIndex = (uchCRCLo ^ pushMsg[i]);
  uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
  uchCRCHi = auchCRCLo[uIndex];
  i++;
}
    return (uchCRCHi << 8 | uchCRCLo) ;
}//crc16 END
