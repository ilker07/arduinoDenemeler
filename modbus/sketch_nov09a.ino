#include <SoftwareSerial.h>


 
#define SSerialTxControl 2   //RS485 Direction control
 
#define RS485Transmit    HIGH
#define RS485Receive     LOW
 
 
SoftwareSerial RS485Serial(8, 9); // RX, TX

int yuksek,dusuk,toplam;



int byteReceived;
byte request [] = {
  0x01,
  0x03,
  0x00,
  0x03,
  0x00,
  0x01,
  0x74,
  0x0A
};
 

 
 
void setup()  
{
  Serial.begin(9600);
  delay(500);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver
  RS485Serial.begin(9600);  
 
}
 
 
void loop()  
{
 
  RS485Serial.listen();
  if (RS485Serial.available())  
  {
    Serial.print("Response: ");
    for (int i = 0; i <= 6; i++) {
      byteReceived = RS485Serial.read();
      Serial.print(byteReceived);
      if(i==3) 
      yuksek=byteReceived;
      if(i==4)  
      dusuk=byteReceived;
      
      Serial.print(" ");
    }
    
    Serial.println();
    toplam=256*yuksek+dusuk;
    Serial.println(toplam);
  }
  else{
   
    digitalWrite(SSerialTxControl, RS485Transmit);  // Init T ransceiver
    for (int i = 0; i < 8; i++) {
 
     // RS485Serial.write((byte)request[i]);
      RS485Serial.write(request[i]);
    }
    
    digitalWrite(SSerialTxControl, RS485Receive);  // Init Transmit
  }
  delay(1000);
 
}
 
