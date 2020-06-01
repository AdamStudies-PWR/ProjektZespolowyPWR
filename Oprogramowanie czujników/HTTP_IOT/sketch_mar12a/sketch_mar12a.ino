
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include "DHTesp.h"

#define DHTPIN 14 //D5

DHTesp dht;

// Set your access point network credentials
const char* ssid = "ssid";
const char* password = "password";

float temperature = 0.0;
float humidity = 0.0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  
    //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());


  server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "temperature:C humidity:%");
  });


  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(temperature).c_str());
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(humidity).c_str());
  });


  dht.setup(DHTPIN, DHTesp::DHT11);
  
  // Start server
  server.begin();
}
 
void loop(){

  delay(dht.getMinimumSamplingPeriod());
 
  float humi = dht.getHumidity();
  float temp = dht.getTemperature();

  if(!isnan(temp)){  
    temperature = temp;
    humidity = humi;
  
    Serial.println(humidity, 1);
    Serial.println(temperature, 1);
   }  
  
 }
  
