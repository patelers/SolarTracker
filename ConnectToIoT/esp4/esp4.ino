//#include <SoftwareSerial.h>
//#define RX 2
//#define TX 3
//String AP = "OPPO Find X2";       // AP NAME
//String PASS = "password"; // AP PASSWORD
//String API = "0E2YTYU2J10KC87B";   // Write API KEY
//String HOST = "api.thingspeak.com";
//String PORT = "80";
//String field = "Field 1";
//int countTrueCommand;
//int countTimeCommand;
//boolean found = false;
//int valSensor = 1;
//SoftwareSerial esp8266(RX,TX);
//
//
//void setup() {
//  Serial.begin(9600);
//  esp8266.begin(115200);
//  sendCommand("AT",5,"OK");
//  sendCommand("AT+CWMODE=1",5,"OK");
//  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
//}
//
//void loop() {
// valSensor = getSensorData();
// String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
//sendCommand("AT+CIPMUX=1",5,"OK");
// sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
// sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
// esp8266.println(getData);delay(1500);countTrueCommand++;
// sendCommand("AT+CIPCLOSE=0",5,"OK");
//}
//
//int getSensorData(){
//  return random(1000); // Replace with your own sensor code
//}
//
//void sendCommand(String command, int maxTime, char readReplay[]) {
//  Serial.print(countTrueCommand);
//  Serial.print(". at command => ");
//  Serial.print(command);
//  Serial.print(" ");
//  while(countTimeCommand < (maxTime*1))
//  {
//    esp8266.println(command);//at+cipsend
//    if(esp8266.find(readReplay))//ok
//    {
//      found = true;
//      break;
//    }
//
//    countTimeCommand++;
//  }
//
//  if(found == true)
//  {
//    Serial.println("OYI");
//    countTrueCommand++;
//    countTimeCommand = 0;
//  }
//
//  if(found == false)
//  {
//    Serial.println("Fail");
//    countTrueCommand = 0;
//    countTimeCommand = 0;
//  }
//
//  found = false;
// }

////////////////////////////////////////////////////////////////////////////

String myAPIkey = "0E2YTYU2J10KC87B";   // Write API KEY
#include <SoftwareSerial.h>
#include <DHT.h>
#define RX 2
#define TX 3
SoftwareSerial ESP8266(RX, TX);

#define DHTPIN 11
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float humidity;
float temperature;
long writingTimer = 17;
long startTime = 0;
long waitTime = 0;

boolean relay1_st = false;
boolean relay2_st = false;
unsigned char check_connection = 0;
unsigned char times_check = 0;
boolean error;

void setup() {

  Serial.begin(9600);
  ESP8266.begin(9600);
  dht.begin();
  startTime = millis(); //starting program clock
  ESP8266.println("AT+RST");
  delay(2000);
  Serial.println("Connecting to wifi");
  while (check_connection == 0)
  {
    Serial.print(".");
    ESP8266.print("AT+CWJAP=\"OPPO Find X2\",\"password\"\r\n");
    ESP8266.setTimeout(5000);
    if (ESP8266.find("WIFI CONNECTED\r\n")==1)
    {
      Serial.println("WIFI CONNECTED");
      break;
    }
    times_check++;
    if (times_check > 3)
    {
      times_check = 0;
      Serial.print("Trying to Reconnect...");
    }
  }
}

void loop()
{
  waitTime = millis() - startTime;
  if (waitTime > (writingTimer * 1000))
  {
    readSensors();
    writeThingSpeak();
    startTime = millis();
  }
}

//Read sensor value
void readSensors(void)
{
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

void writeThingSpeak(void);

{
  startThingSpeakCmd(); //follow these commands

  String getStr = "GET /update?api_key=";
  getStr += myAPIkey;
  getStr += "&field1=";
  getStr += String(temperature);
  getStr += "&field2=";
  getStr += String(humidity);
  getStr += "\r\n\r\n";

  GetThingSpeakcmd(getStr);
}

//start communication with Thinkspeak
void startThingSpeakCmd(void)
{
  ESP8266.flush();
  String cmd = "AT+CIPSTART=\"TCP\",\""; //TCP OR ICP
  cmd += "184.106.153.149";
  cmd += "\",80";
  ESP8266.println(cmd);
  Serial.print("Start Commands");
  Serial.println(cmd);

  if (ESP8266.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
}

String GetThingSpeakcmd(String getStr)
{
  String cmd = "AT+CIPSEND=";
  CMD += String(getStr.length());
  ESP8266.println(cmd);
  Serial.println(cmd);

  if (ESP8266.find(">"))
  {
    ESP8266.print(getStr);
    Serial.println(getStr);
    delay(500);
    String messageBody = "";
    while (ESP8266.available())
    {
      String line = ESP8266.readStringUntil('\n');
      if (line.length() == 1)
      {
        messageBody = ESP8266.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody received: ");
    Serial.print(messageBody);
    return messageBody;
  }
  else
  {
    ESP8266.println("AT+CIPCLOSE");
    Serial.print("AT+CIPCLOSE");
  }
}
////////////////////////


//void setup() {}
//void loop() {}
////////////////////////////
