#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include "DHTesp.h"

#define DHTPIN 14 //D5

DHTesp dht;

const char* ssid = "ssid";
const char* password = "password";

float temperature = 0.0;
float humidity = 0.0;

//Nadpisanie metod klasy uMQTTBroker

class myMQTTBroker: public uMQTTBroker
{
public:
    virtual bool onConnect(IPAddress addr, uint16_t client_count) {
      Serial.println(addr.toString()+" connected");
      return true;
    }
    
    virtual bool onAuth(String username, String password) {
      Serial.println("Username/Password: "+username+"/"+password);
      return true;
    }
    
    virtual void onData(String topic, const char *data, uint32_t length) {
      char data_str[length+1];
      os_memcpy(data_str, data, length);
      data_str[length] = '\0';
      
      Serial.println("received topic '"+topic+"' with data '"+(String)data_str+"'");
    }
};

myMQTTBroker myBroker;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  Serial.println("Starting MQTT broker");
  myBroker.init();

  myBroker.subscribe("#");

  dht.setup(DHTPIN, DHTesp::DHT11);
  
}


void loop()
{

  delay(dht.getMinimumSamplingPeriod());
 
  float humi = dht.getHumidity();
  float temp = dht.getTemperature();

  if(!isnan(temp)){  
    temperature = temp;
    humidity = humi;

    myBroker.publish("broker/humidity", (String)humidity);
    myBroker.publish("broker/temperature", (String)temperature);

    Serial.println(humidity, 1);
    Serial.println(temperature, 1);
   }  
  
 }
