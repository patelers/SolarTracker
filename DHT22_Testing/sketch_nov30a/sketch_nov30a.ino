//#include <DHT_U.h>

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266HTTPClient.h>
//#include <Adafruit_Sensor.h>

//#include <DHT.h>
#include "DHT.h"

#include <SoftwareSerial.h> // library allows communication between mega board and other devices (esp8266)
#define RX 2  //digital pins defined for communication with ESP8266 2
#define TX 3  // corresponding RX and TX pins from ESP8266  3
#include <ESP8266.h>

//#define ESP8266_RST_PIN    2

#define DHTPIN 11  // Sensor data pin connected to digital ardunio pin 
#define DHTTYPE DHT22 // DHT 22 type (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

//#define dht_apin 11 // Analog Pin sensor is connected to
//int dht11 dhtObject;
//DHT dhtObject;

String AP = "OPPO Find X2";       // AP NAME
String PASS = "password"; // AP PASSWORD
String API = "0E2YTYU2J10KC87B";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;

SoftwareSerial esp8266(RX, TX); // digital (output) pin used to allow serial communication 

void setup() {
  Serial.begin(9600); //serial monitor
 // DHT.begin(); //start the sensor
  esp8266.begin(115200); //start the esp8266 module
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");
}

void loop() {

  String getData = "GET /update?api_key=" + API + "&field1=" + getTemperatureValue() + "&field2=" + getHumidityValue(); // can add more fields to server: + "field3=" + function()  
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");
  esp8266.println(getData); delay(1500); countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

// functions called 
String getTemperatureValue() {

  float temperature = dht.readTemperature();
  Serial.print(" Temperature(C)= ");
  Serial.println(temperature);
  delay(50);
  return String(temperature);

}

String getHumidityValue() {

  float humidity = dht.readHumidity();
  Serial.print(" Humidity in %= ");
  Serial.println(humidity);
  delay(50);
  return String(humidity);
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while (countTimeCommand < (maxTime * 1))
  {
    esp8266.println(command);//at+cipsend
    if (esp8266.find(readReplay)) //ok
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }
  
  if (found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}


//////////////////////////////////////////////////////////////

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266HTTPClient.h>
////#include <Adafruit_Sensor.h>
//#include <DHT.h>
////#include <DHT_U.h>
//
//#define DHTPIN 11           // DHT22 sensor pin
//#define DHTTYPE DHT22       // DHT22 sensor type
//#define WIFI_SSID "OPPO Find X2"
//#define WIFI_PASSWORD "password"
//#define API_KEY "0E2YTYU2J10KC87B"
//#define SERVER "api.thingspeak.com"
//#define RX 2  //digital pins defined for communication with ESP8266
//#define TX 3  // corresponding RX and TX pins from ESP8266
//DHT dht(DHTPIN, DHTTYPE);
//WiFiClient client;
//SoftwareSerial esp8266(RX, TX); // digital (output) pin used to allow serial communication
//
//void setup() {
//  Serial.begin(115200);
//  dht.begin();
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to WiFi...");
//  }
//  Serial.println("Connected to WiFi!");
//}
//
//void loop() {
//  float humidity = dht.readHumidity();
//  float temperature = dht.readTemperature();
//  
//  if (isnan(humidity) || isnan(temperature)) {
//    Serial.println("Failed to read DHT22 sensor!");
//    return;
//  }
//  
//  String url = "/update?api_key=" + String(API_KEY) +
//               "&field1=" + String(temperature) +
//               "&field2=" + String(humidity);
//               
//  if (client.connect(SERVER, 80)) {
//    Serial.println("Connected to ThingSpeak!");
//    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                 "Host: " + SERVER + "\r\n" +
//                 "Connection: close\r\n\r\n");
//    delay(500);
//    client.stop();
//    Serial.println("Data sent to ThingSpeak!");
//  } else {
//    Serial.println("Failed to connect to ThingSpeak!");
//  }
//  
//  delay(3000);   // Wait 3 seconds before sending next data
//}

/////////////////////////////////////////////////////////////////
