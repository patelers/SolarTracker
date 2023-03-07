//#include <ThingSpeak.h>
#include <SoftwareSerial.h>
#include <ESP8266.h>
#include <DHT.h>;
#include "DHT.h"

#define RX 2
#define TX 3
//#define dht_apin 11 // Analog Pin sensor is connected to
//#define DHT dhtObject;
#define DHTPIN 11
#define DHTTYPE DHT22

//dht11 dhtObject;
String AP = "OPPO Find X2";       // AP NAME
String PASS = "password"; // AP PASSWORD

//unsigned long myChannelNumber = 1945743;
String API = "0E2YTYU2J10KC87B";   // Write API KEY from thinkspeak
String HOST = "api.thingspeak.com";
String PORT = "80";

DHT dht(DHTPIN, DHTTYPE);

//String field = "field1";//
int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;

SoftwareSerial esp8266(RX, TX);

void setup() {

  Serial.begin(9600);
  dht.begin();
  esp8266.begin(9600);//115000
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

  /////////////
  //  String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
  //switch(countTrueCommand) {
  //
  //case 0: sendCommand("AT",5,"OK");break;
  //case 1: sendCommand("AT+RST",10,"invalid");break;
  //case 2: sendCommand("AT+CIPMUX=1",5,"OK"); break;
  //case 3: sendCommand("AT+CIPSTART=0,"TCP","+ HOST +","+ PORT,15,"OK"); break;
  //case 4: sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">"); break;
  //case 5: esp8266.println(getData);delay(1500);countTrueCommand++; break;
  //case 6: sendCommand("AT+CIPCLOSE=0",5,"OK"); break;
  //case 7:
  //
  //Serial.println(valSensor);
  //Serial.print(getData);
  //Serial.print(",");
  //Serial.println(getData.length());
  //valSensor = random(100000); // random value, change with sensor value if using sensor
  //countTrueCommand = 0;
  //delay(10000);
  //break;
  //}
  /////////////

// functions 
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
