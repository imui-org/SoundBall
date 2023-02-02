//OPEN TO DOS:
//Batterie Ladung checken und Feedback (LED?) einbauen, Spannung messen über Analog in? 
//Automatisches ausschalten und einschalten (bei Bewegung?) oder mit Schalter? Deep Sleep Funktion?
//Wifi connection Feedback (LED?) - automatisches Verbinden bei Abbruch etc. (visualisieren) 
//Bei richtigem Funktionieren Bewegung visualisieren (LED Farben und Intensität - Neopix?) - ggf. gefilterten und gemappten Wert aus Pure Data zurückschicken dafür?
//Die x,y,z Werte als 12bit Integer schicken und nicht als 1Byte ... 






//https://siytek.com/communication-between-two-esp8266/ WIFI

/************************************************************************************
 *   
 *  Name    : MMA8453_n0m1 Library Example: DataMode                       
 *  Author  : Noah Shibley, NoMi Design Ltd. http://n0m1.com                       
 *        : Michael Grant, Krazatchu Design Systems. http://krazatchu.ca/
 *  Date    : May 5th 2013                                    
 *  Version : 0.2                                              
 *  Notes   : Arduino Library for use with the Freescale MMA8453Q via Arduino native WIRE with repeated start (was i2c of DSS circuits). 
 *
 ***********************************************************************************/

#include <WiFi.h>
#include <WiFiUdp.h>
 #include <Wire.h>
 #include <MMA8453_n0m1.h>
// Set WiFi credentials
#define WIFI_SSID "TheOtherESP"
#define WIFI_PASS "imuiimui"


// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);
#define UDP_PORT 4210

MMA8453_n0m1 accel;

void setup() {

 
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);

accel.setI2CAddr(0x1C); //change your device address if necessary, default is 0x1C
accel.dataMode(true, 2); //enable highRes 10bit, 2g range [2g,4g,8g]

}

 
void loop() {
  accel.update();
 


 //Map the value from ACCEL_MIN to ACCEL_MAX to 0 to 255
  int mappedDataX = map(accel.x(), -2048, 2048, 0, 255);
  // Constrain the value to the range of 0 to 255
 mappedDataX = constrain(mappedDataX, 0, 255);
 //Map the value from ACCEL_MIN to ACCEL_MAX to 0 to 255
  int mappedDataY = map(accel.y(), -2048, 2048, 0, 255);
  // Constrain the value to the range of 0 to 255
 mappedDataY = constrain(mappedDataY, 0, 255);

 //Map the value from ACCEL_MIN to ACCEL_MAX to 0 to 255
  int mappedDataZ = map(accel.z(), -2048, 2048, 0, 255);
  // Constrain the value to the range of 0 to 255
 mappedDataZ = constrain(mappedDataZ, 0, 255);


   // Send Packet
UDP.beginPacket(remote_IP, UDP_PORT);
UDP.write(mappedDataX);
UDP.write(mappedDataY);
UDP.write(mappedDataZ);
UDP.endPacket();
  delay(5);

  
}
