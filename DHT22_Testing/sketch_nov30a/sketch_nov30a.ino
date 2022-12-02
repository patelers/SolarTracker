#include <SoftwareSerial.h>
//#include <DHT.h>;
#include "DHT.h"
#define RX 2
#define TX 3

#define DHTPIN 11
#define DHTTYPE DHT22
//#define dht_apin 11 // Analog Pin sensor is connected to
//int dht11 dhtObject;
String AP = "OPPO Find X2";       // AP NAME
String PASS = "password"; // AP PASSWORD
String API = "0E2YTYU2J10KC87B";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
  
SoftwareSerial esp8266(RX,TX); 
DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  Serial.begin(9600);
   dht.begin();
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {
  
 String getData = "GET /update?api_key="+ API +"&field1="+getTemperatureValue()+"&field2="+getHumidityValue();
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}


String getTemperatureValue(){

   float temperature = dht.readTemperature();
  Serial.print(" Temperature(C)= ");
  Serial.println(temperature);
  return String(temperature);
  
}


String getHumidityValue(){


   float humidity = dht.readHumidity();
  Serial.print(" Humidity in %= ");
  Serial.println(humidity);
  return String(humidity);
  
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
