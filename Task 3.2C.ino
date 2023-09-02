#include <WiFiNINA.h>

#include <BH1750.h>
#include <Wire.h>


char yourhotspot[] = "Aryan";
char passkey[] = "123456789";

WiFiClient purchaser;
BH1750 photoread;

char   organizer[] = "maker.ifttt.com";
String route  = "/trigger/lightsensor/with/key/giaxwJZI9ala1sWuIBEs4kg0BueWF_NRMOCaOK1PTyw";
String queryString = "?value1=57&value2=25";

void setup() {

  Serial.begin(9600);
  Serial.print("START");
  while (!Serial);

  
     WiFi.begin(yourhotspot, passkey);
     Wire.begin();
while(true)
  {
  if (purchaser.connect(organizer, 80)) {
    
    Serial.println("Connected to server");
    break;
  }
  else {// if not connected:
    Serial.println("connection failed");
    
  }
  delay(500);
}
photoread.begin();
Serial.println("Connected to server");
}
void loop() {
  Serial.print("START");
  float lux = photoread.readLightLevel();

  queryString +="?value1=" ;
  queryString += lux;
  Serial.println(queryString);

  if (lux > 500) {

    // make a HTTP request:
    // send HTTP header
    purchaser.println("GET " + route + queryString + " HTTP/1.1");
    purchaser.println("Host: " + String(organizer));
    purchaser.println("Connection: close");
    purchaser.println(); 


    while (purchaser.connected()) {
      if (purchaser.available()) {
        
        char c = purchaser.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the purchaser:
    purchaser.stop();
    Serial.println();
    Serial.println("disconnected");
  }
  queryString = "";
  delay(3000);
}
