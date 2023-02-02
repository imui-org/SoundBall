#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "imuiimui"

// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210

// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

int accX, accY, accZ;

void setup() {

  // Setup LED pin
  pinMode(2, OUTPUT);
  
  // Setup serial port
  Serial.begin(115200);
//  Serial.println();
delay(1000);
  // Begin Access Point
  Serial.println("Starting access point...");

  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(1000);
  Serial.println(WiFi.localIP());
delay(1000);
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

}

void loop() {

  // Receive packet
  UDP.parsePacket();
  UDP.read((uint8_t*) packetBuffer, 3);
accX = (int) packetBuffer[0];
accY = (int) packetBuffer[1];
accZ = (int) packetBuffer[2];

 // Print the values to serial
    Serial.print("accX: ");
    Serial.println(accX);
    Serial.print("accY: ");
    Serial.println(accY);
    Serial.print("accZ: ");
    Serial.println(accZ);

} 
