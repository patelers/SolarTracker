


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

//String myAPIkey = "0E2YTYU2J10KC87B";   // Write API KEY
//#include <SoftwareSerial.h>
//#include <DHT.h>
//#define RX 2
//#define TX 3
//SoftwareSerial ESP8266(RX, TX);
//
//#define DHTPIN 11 // pin on the Arduino data pin of the DHT sensor is connected.
//#define DHTTYPE DHT22 // type of DHT sensor being used
//
//DHT dht(DHTPIN, DHTTYPE, 11); //number of milliseconds to wait between sensor readings.
//float humidity;
//float temperature;
////variables used with timers
//long writingTimer = 3; //every 3 seconds upload
//long startTime = 0;
//long waitTime = 0;
//
//boolean relay1_st = false;
//boolean relay2_st = false;
//unsigned char check_connection = 0;
//unsigned char times_check = 0;
//boolean error;
//
//void setup() {
//
//  Serial.begin(9600);
//  ESP8266.begin(9600);
//  dht.begin();
//  startTime = millis(); //starting program clock
//  ESP8266.println("AT+RST");
//  delay(2000);
//  Serial.println("Connecting to wifi");
//  while (check_connection == 0)
//  {
//    Serial.print(".");
//    ESP8266.print("AT+CWJAP=\"OPPO Find X2\",\"password\"\r\n");
//    ESP8266.setTimeout(5000);
//    if (ESP8266.find("WIFI CONNECTED\r\n") == 1)
//    {
//      Serial.println("WIFI CONNECTED");
//      break;
//    }
//    times_check++;
//    if (times_check > 3)
//    {
//      times_check = 0;
//      Serial.print("Trying to Reconnect...");
//    }
//  }
//}

//void loop()
//{
//  waitTime = millis() - startTime;
//  if (waitTime > (writingTimer * 1000))
//  {
//    readSensors();
//    writeThingSpeak();
//    startTime = millis();
//  }
//}
//
////Read sensor value
//void readSensors(void)
//{
//  temperature = dht.readTemperature();
//  humidity = dht.readHumidity();
//}
//
//void writeThingSpeak(void);
//
//{
//  startThingSpeakCmd(); //follow these commands
//
//  String getStr = "GET /update?api_key=";
//  getStr += myAPIkey;
//  getStr += "&field1=";
//  getStr += String(temperature);
//  getStr += "&field2=";
//  getStr += String(humidity);
//  getStr += "\r\n\r\n";
//
//  GetThingspeakcmd(getStr);
//}
//
////start communication with Thinkspeak
//void startThingSpeakCmd(void)
//{
//  ESP8266.flush();
//  String cmd = "AT+CIPSTART=\"TCP\",\""; //TCP OR ICP
//  cmd += "184.106.153.149";
//  cmd += "\",80";
//  ESP8266.println(cmd);
//  Serial.print("Start Commands");
//  Serial.println(cmd);
//
//  if (ESP8266.find("Error"))
//  {
//    Serial.println("AT+CIPSTART error");
//    return;
//  }
//}
//
//String GetThingspeakcmd(String getStr)
//{
//  String cmd = "AT+CIPSEND=";
//  CMD += String(getStr.length());
//  ESP8266.println(cmd);
//  Serial.println(cmd);
//
//  if (ESP8266.find(">"))
//  {
//    ESP8266.print(getStr);
//    Serial.println(getStr);
//    delay(500);
//    String messageBody = "";
//    while (ESP8266.available())
//    {
//      String line = ESP8266.readStringUntil('\n');
//      if (line.length() == 1)
//      {
//        messageBody = ESP8266.readStringUntil('\n');
//      }
//    }
//    Serial.print("MessageBody received: ");
//    Serial.print(messageBody);
//    return messageBody;
//  }
//  else
//  {
//    ESP8266.println("AT+CIPCLOSE");
//    Serial.print("AT+CIPCLOSE");
//  }
//}


///////////////////////////////////////////////////
//chat gpt

//String myAPIkey = "0E2YTYU2J10KC87B"; // Write API KEY
//#include <SoftwareSerial.h>
//#include <DHT.h>
//#define RX 2
//#define TX 3
//SoftwareSerial ESP8266(RX, TX);
//
//#define DHTPIN 11 // pin on the Arduino data pin of the DHT sensor is connected.
//#define DHTTYPE DHT22 // type of DHT sensor being used
//
//DHT dht(DHTPIN, DHTTYPE); // remove the third parameter, it's not needed
//
//float humidity;
//float temperature;
////variables used with timers
//long writingTimer = 3; // every 3 seconds upload

/////////////////////////////////////////////////////////////////////////
//AT Checks
//void setup() {}
//void loop() {}
/////////////////////////////////////////////////////////////////////////

//#include <ESP8266WiFi.h>
// Thingspeak working code
String myAPIkey = "0E2YTYU2J10KC87B"; //found on thingspeak platform

#include <SoftwareSerial.h> //header file allows serial comms on digital pins for tx,rx 
#include <DHT.h>; // header file for DHT22 sensor, provides functions for reading values 
SoftwareSerial ESP8266(50, 51); // Rx,  Tx object created 2 white 3 green for UNO board, here white 50, green 51
// used to send and recieve data to and from ESP8266

#define DHTTYPE DHT22 // specifies DHT22 spec is used 
#define DHTPIN  11 //pin on the Arduino data pin of the DHT sensor is connected.

DHT dht(DHTPIN, DHTTYPE, 11); // number of milliseconds,
//wait before attempting to communicate with the DHT sensor again.
//prevent multiple requests from overwhelming and causing errors.

float humidity, temp_f;

//need to include variables needed to be seen on iot

long writingTimer = 17; // delay for a certain function
long startTime = 0; // store the starting time of a function
long waitTime = 0; // time to wait before performing operation


boolean relay1_st = false; //store the current status of a relay
boolean relay2_st = false; // store the current status of a second relay.
unsigned char check_connection = 0; //indicating whether a connection to network has been established.
unsigned char times_check = 0;// can hold integer values between 0 and 255, cannot hold -ve values, check for error
boolean error; // indicate error has occurred

void setup()
{
  Serial.begin(9600);
  ESP8266.begin(9600); //allow communication of ardunio and esp8266 wifi module at same baud rate, wifi module has been configured to work under 9600
  dht.begin(); // initialse DHT sensor
  startTime = millis(); //return number of milliseconds since the board begins running
  ESP8266.println("AT+RST"); // sends the command to ESP8266 which resets it.
  delay(2000); // 2-second delay to givetime to reset.
  Serial.println("Connecting to Wifi"); // sends string "Connecting to Wifi" over the serial connection

  // waiting for the connection to be established before moving on with the rest of the program.
  while (check_connection == 0) // continue running as long as the variable check_connection is equal to 0, keep track of the Wi-Fi connection status
  {
    Serial.print("."); // indicate on serial monitor that code is attempting to connect to wifi network
    ESP8266.print("AT+CWJAP=\"OPPO Find X2\",\"password\"\r\n");// sends AT command telling to connect to wifi network
    ESP8266.setTimeout(5000);// take 5 sec to respond to command
    if (ESP8266.find("WIFI CONNECTED\r\n") == 1) // checks if module has connected successfully
    {
      Serial.println("WIFI CONNECTED");
      break; // if wifi connected printed on serial monitor break out of while loop
    }
    times_check++; // increment counter if not connected first time round
    if (times_check > 3)
    {
      times_check = 0; //repeat checks until connection made
      Serial.println("Trying to Reconnect..");
    }
  }
}

void loop()
{
  waitTime = millis() - startTime; //checks time elapsed since previous data transmission to ThingSpeak
  if (waitTime > (writingTimer * 1000))
  {
    readSensors(); // function to read the temperature and humidity from sensor

    //write a function for voltage, current, power of panel.
    //readpanel1();
    //readpanel2();

    writeThingSpeak(); //  function to send the data to ThingSpeak.
    startTime = millis();
  }
}

void readSensors(void)
{
  temp_f = dht.readTemperature(); // finds temperature
  humidity = dht.readHumidity(); // finds humidity
}

//void readpanel1(void)

//void readpanel2(void)

void writeThingSpeak(void)
{
  startThingSpeakCmd(); // function to initiate communication with server
  String getStr = "GET /update?api_key="; //from thinkspeak
  getStr += myAPIkey; // Specific key provided by thinkspeak, allows data transmission
  getStr += "&field1="; // graph 1 display
  getStr += String(temp_f);
  getStr += "&field2="; // graph 2 display
  getStr += String(humidity);

  //panel1
  //getStr += "&field3="; // graph 1 display
  // getStr += String(voltage1);
  //getStr += "&field4="; // graph 1 display
  // getStr += String(current1);
  //getStr += "&field5="; // graph 1 display
  // getStr += String(power1);

  //panel2
  //getStr += "&field5="; // graph 1 display
  // getStr += String(voltage2);
  //getStr += "&field6="; // graph 1 display
  // getStr += String(current2);
  //getStr += "&field7="; // graph 1 display
  // getStr += String(power2);

  getStr += "\r\n\r\n"; //may need to change as needed
  GetThingspeakcmd(getStr); // execute function
}

void startThingSpeakCmd(void)
{
  ESP8266.flush(); // gets rid of any incoming and outgoinng data on module
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com IP address
  cmd += "\",80"; // port number
  ESP8266.println(cmd); // sends the AT command to the ESP8266 module for execution.
  Serial.print("Start Commands: ");
  Serial.println(cmd);

  if (ESP8266.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return; // print error message and return without established
  }
}

String GetThingspeakcmd(String getStr) // get request string for sending sensor data to thinkspeak
{
  String cmd = "AT+CIPSEND="; // AT command,
  cmd += String(getStr.length());
  ESP8266.println(cmd);
  Serial.println(cmd);

  if (ESP8266.find(">")) // If module does not respond with ">" , means that the TCP connection was not successfully established
  {
    ESP8266.print(getStr); // string is then sent to the module
    Serial.println(getStr);
    delay(500);
    String messageBody = ""; // for debugging purposes and returns it as the output of the function.
    while (ESP8266.available())
    {
      String line = ESP8266.readStringUntil('\n');// read until no more data available
      if (line.length() == 1)
      {
        messageBody = ESP8266.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody received: "); // successsfuly transferred data to platform
    Serial.println(messageBody);
    return messageBody;
  }
  else
  {
    ESP8266.println("AT+CIPCLOSE"); // command to the ESP8266 module,closes the TCP connection with the server.
    // module does not receive the '>' character from the server
    Serial.println("AT+CIPCLOSE");
  }
}

////////////////////////////////////////////////////////////////////////
