//#include <ESP8266.h>
//
//#include "Arduino.h"
//
//
//#include "SoftwareSerial.h"
//SoftwareSerial  ConsoleOut(8, 9);
//
//#define SSID  "MySSID"
//#define PWD   "MyPassword"
//
//void setup() {
//  char  *ipAddress, ap[31];
//
//  WiFi.reset(WIFI_RESET_HARD);
//  WiFi.begin(9600);
//  if (WiFi.join(SSID, PWD) == WIFI_ERR_OK) {
//    ipAddress = WiFi.ip(WIFI_MODE_STA);
//    ConsoleOut.print(F("\n\rIP address:"));
//    ConsoleOut.print(ipAddress);
//    ConsoleOut.print(':');
//    if (WiFi.isConnect(ap))
//      ConsoleOut.println(ap);
//    else
//      ConsoleOut.println(F("not found"));
//  } else
//    while (1);
//}
//
//void loop() {
//  if (WiFi.connect((char *)"www.google.co.jp", 80) == WIFI_ERR_CONNECT) {
//
//    if (WiFi.send((const uint8_t *)"GET / HTTP/1.1\r\n\r\n") == WIFI_ERR_OK) {
//      int16_t c;
//      uint16_t len = WiFi.listen(10000UL);
//      while (len)
//        if ((c = WiFi.read()) > 0) {
//          ConsoleOut.write((char)c);
//          len--;
//        }
//    } else
//      ConsoleOut.println(F("Send fail"));
//
//    WiFi.close();
//
//  } else
//    ConsoleOut.println(F("TCP connect fail"));
//
//  WiFi.disconnect();
//
//  while (1);
//}

//#include <SoftwareSerial.h>
//#define RX 2
//#define TX 3
//String AP = "OPPO Find X2";       // AP NAME
//String PASS = "password"; // AP PASSWORD
//String API = "0E2YTYU2J10KC87B";   // Write API KEY
//String HOST = "api.thingspeak.com";
//String PORT = "80";
//String field = "field 1";
//
//int countTrueCommand;
//int countTimeCommand;
//boolean found = false;
//int valSensor = 1;
//
//SoftwareSerial esp8266(RX, TX);
//
//void setup() {
//
//  Serial.begin(9600);
//  esp8266.begin(115200);
//
//  sendCommand("AT", 5, "OK");
//  sendCommand("AT+CWMODE=1", 5, "OK");
//  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");
//
//}
//
//void loop() {
//
//  valSensor = getSensorData();
//  String getData = "GET /update?api_key=" + API + "&" + field + "=" + String(valSensor);
//  sendCommand("AT+CIPMUX=1", 5, "OK");
//  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
//  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");
//  esp8266.println(getData); delay(1500); countTrueCommand++;
//  sendCommand("AT+CIPCLOSE=0", 5, "OK");
//
//}
//
//
//
//int getSensorData() {
//  return random(10); // Replace with your own sensor code
//}
//
//void sendCommand(String command, int maxTime, char readReplay[]) {
//  Serial.print(countTrueCommand);
//  Serial.print(". at command => ");
//  Serial.print(command);
//  Serial.print(" ");
//  
//  while (countTimeCommand < (maxTime * 1))
//
//  {
//    esp8266.println(command);//at+cipsend
//    if (esp8266.find(readReplay)) //ok
//    
//    {
//
//      found = true;
//      break;
//
//    }
//
//    countTimeCommand++;
//
//  }
//
//  if (found == true)
//
//  {
//
//    Serial.println("OYI");
//    countTrueCommand++;
//    countTimeCommand = 0;
//
//  }
//
//  if (found == false)
//
//  {
//
//    Serial.println("Fail");
//    countTrueCommand = 0;
//    countTimeCommand = 0;
//
//  }
//
//  found = false;
//
//}
////////////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>                        
SoftwareSerial esp8266(2,3);                   
#define serialCommunicationSpeed 9600               
#define DEBUG true                                 

void setup()

{
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed);     
  InitWifiModule();                              
}

void loop()                                                         
{

  if(esp8266.available())                                           
 {    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48;                                                
     String webpage = "<h1>Hello World!</h1>";
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";    
     sendData(closeCommand,3000,DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";                                             
    esp8266.print(command);                                          
    long int time = millis();                                      
    while( (time+timeout) > millis())                                 
    {      
      while(esp8266.available())                                      
      {
        char c = esp8266.read();                                     
        response+=c;                                                  
      }  
    }    
    if(debug)                                                        
    {
      Serial.print(response);
    }    
    return response;                                                  
}

void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);                                                  
  sendData("AT+CWJAP=\"OPPO Find X2\",\"password\"\r\n", 2000, DEBUG);        
  delay (3000);
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);                                     

}
