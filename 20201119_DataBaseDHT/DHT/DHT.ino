#include "DHT.h"
#include <WiFiMulti.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiMulti WiFiMulti;

int t = 0;  // TEMPERATURE VAR
int h = 0;  // HUMIDITY VAR
String data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("DHT11 sensor!");
  //call begin to start sensor
  dht.begin();

  delay(1000);

  //h = (int) dht.readHumidity(); 
 // t = (int) dht.readTemperature(); 
  data = "";

    // We start by connecting to a WiFi network
    //WiFiMulti.addAP("SSID", "SSID's password");
    //WiFiMulti.addAP("4F office", "078210171");
    WiFiMulti.addAP("616681", "616681616681");
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}

void loop() {
  
   //use the functions which are supplied by library.
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
   // h = (int) dht.readHumidity();
   // t = (int) dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    return;
    }

   String data = "temp1="+String(t)+"&hum1="+String(h);
  
  // print the result to Terminal
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C ");
    //we delay a little bit for next read
      delay(5000);

       const uint16_t port = 80;
       const char * host = "192.168.1.59"; // ip or dns
        Serial.print("connecting to ");
        Serial.println(host);

        // Use WiFiClient class to create TCP connections
        WiFiClient client;

        if (!client.connect(host, port)) {
          Serial.println("connection failed");
          Serial.println("wait 5 sec...");
          delay(5000);
          return;
         }
         
          client.println("POST /dht/add.php HTTP/1.1"); 
          client.println("Host:192.168.1.59"); // SERVER ADDRESS HERE TOO
          client.println("Content-Type: application/x-www-form-urlencoded"); 
          client.print("Content-Length: "); 
          client.println(data.length()); 
          client.println(); 
          client.print(data);

          if (client.connected()) { 
            Serial.println("連線關閉");
          client.stop();  // DISCONNECT FROM THE SERVER
          }
          
          delay(5000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
                    
}
