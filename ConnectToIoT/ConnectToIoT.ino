#include <CayenneArduinoDefines.h>
#include <CayenneArduinoMQTTClient.h>
#include <CayenneHandlers.h>
#include <CayenneMessage.h>
#include <CayenneMQTTESP32.h>
#include <CayenneMQTTESP8266.h>
#include <CayenneMQTTESP8266Shield.h>
#include <CayenneMQTTEthernet.h>
#include <CayenneMQTTEthernetClient.h>
#include <CayenneMQTTEthernetW5200.h>
#include <CayenneMQTTEthernetW5500.h>
#include <CayenneMQTTGSM.h>
#include <CayenneMQTTGSMClient.h>
#include <CayenneMQTTMKR1000.h>
#include <CayenneMQTTSerial.h>
#include <CayenneMQTTSerialClient.h>
#include <CayenneMQTTWiFi.h>
#include <CayenneMQTTWiFi101.h>
#include <CayenneMQTTWiFiClient.h>
#include <CayenneMQTTYun.h>
#include <CayenneMQTTYunClient.h>
#include <CayenneTemperature.h>
#include <CayenneTMP102.h>
#include <CayenneVCNL4000.h>
#include <DetectDevice.h>


//#include <SoftwareSerial.h>
//
//#include <ESP8266SerialLibrary.h>
//
///*
//This sketch connects to the Cayenne server using an ESP8266 WiFi module as a shield connected via a hardware serial to an Arduino.
//
//The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.
//
//Steps:
//1. Install the ESP8266SerialLibrary.zip library via the Arduino IDE (Sketch->Include Library->Add .ZIP Library) from the Cayenne extras/libraries
//   folder (e.g. My Documents\Arduino\libraries\CayenneMQTT\extras\libraries) to compile this example.
//2. Connect the ESP8266 as a shield to your Arduino. This example uses the Serial1 hardware serial pins available on the Mega. You can also try 
//   using a software serial, though it may be less stable.
//3. Set the Cayenne authentication info to match the authentication info from the Dashboard.
//4. Set the network name and password.
//5. Compile and upload the sketch.
//6. A temporary widget will be automatically generated in the Cayenne Dashboard. To make the widget permanent click the plus sign on the widget.
//
//NOTE: This code requires ESP8266 firmware version 1.0.0 (AT v0.22) or later.
//*/
//
////#define CAYENNE_DEBUG       // Uncomment to show debug messages
////#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
//#include <CayenneMQTTESP8266Shield.h>
//
//// WiFi network info.
//char ssid[] = "OPPO Find X2";
//char wifiPassword[] = "password";
//
//// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
//char username[] = "d2c956c0-539b-11ed-bf0a-bb4ba43bd3f6";
//char password[] = "991e77320786e82860a5f81172dd13ba73c39b33";
//char clientID[] = "d5cfa870-6911-11ed-8d53-d7cd1025126a";
//
//// Set ESP8266 Serial object. In this example we use the Serial1 hardware serial which is available on boards like the Arduino Mega.
//#define EspSerial Serial1
//
//ESP8266 wifi(&EspSerial);
//
//void setup()
//{
//  Serial.begin(9600);
//  delay(10);
//
//  // Set ESP8266 baud rate
//  EspSerial.begin(115200);
//  delay(10);
//
//  Cayenne.begin(username, password, clientID, wifi, ssid, wifiPassword);
//}
//
//void loop()
//{
//  Cayenne.loop();
//}
//
//// Default function for sending sensor data at intervals to Cayenne.
//// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
//CAYENNE_OUT_DEFAULT()
//{
//  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
//  Cayenne.virtualWrite(0, millis());
//  // Some examples of other functions you can use to send data.
//  //Cayenne.celsiusWrite(1, 22.0);
//  //Cayenne.luxWrite(2, 700);
//  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//}
//
//// Default function for processing actuator commands from the Cayenne Dashboard.
//// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
//  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}



/*
This example shows how to connect to Cayenne using a Serial USB connection and send/receive sample data.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

This requires the use of the Serial USB connection so you cannot use the Serial device for
printing messages. If you need to print you can use SoftwareSerial and connect another device
to read messages via the SoftwareSerial pins.

In order for this to work you must run the connection script on the machine the Arduino is connected to.
The scripts are located under the extras\scripts folder in the main library folder. This redirects the traffic
from the Arduino to the Cayenne server.

Steps:
1. Set the Cayenne authentication info to match the authentication info from the Dashboard.
2. Compile and upload this sketch.
3. Launch the connection script as described below for Windows or Linux/OSX.

Windows:
  1. Open the Windows command line (cmd.exe)
  2. Navigate to the scripts folder by typing "cd [path]", e.g.  "cd C:\Users\[YourUserName]\Documents\Arduino\libraries\CayenneMQTT\extras\scripts"
  3. Run the script by typing "cayenne-ser.bat -c COM4" (where COM4 is the Arduino serial port) and hitting Enter

Linux and OSX:
    ./cayenne-ser.sh (may need to run with sudo)
    
You can specify port, baud rate, and server endpoint like this:
    ./cayenne-ser.sh -c <serial port> -b <baud rate> -s <server address> -p <server port>

    For instance :
      ./cayenne-ser.sh -c /dev/ttyACM0 -b 9600 -s mqtt.mydevices.com -p 1883

    Run cayenne-ser.sh -h for more information

    Be sure to select the right serial port (there may be multiple).

ATTENTION!
  Do not use Serial to display any output in this sketch. It will interfere with the Serial
  USB connection. When uploading sketches the Arduino IDE may complain with "programmer is
  not responding" or "Access is denied." You will need to terminate the connection script
  before uploading new sketches since it blocks access to the Serial port. Also make sure 
  the Serial Monitor is disabled in the IDE since that can prevent the Arduino from 
  connecting to the Windows/Linux/OSX machine. If you use Visual Micro for Visual Studio make
  sure Automatic Debugging is disabled. Otherwise the Serial Monitor can interfere with the
  Serial connection.
*/
//
//#include <CayenneMQTTSerial.h>
//
//// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
//char username[] = "d2c956c0-539b-11ed-bf0a-bb4ba43bd3f6";
//char password[] = "991e77320786e82860a5f81172dd13ba73c39b33";
//char clientID[] = "d5cfa870-6911-11ed-8d53-d7cd1025126a";
//
//void setup()
//{
//  //Baud rate can be specified by calling Cayenne.begin(username, password, clientID, 9600);
//  Cayenne.begin(username, password, clientID);
//}
//
//void loop() {
//  Cayenne.loop();
//}
//
//// Default function for sending sensor data at intervals to Cayenne.
//// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
//CAYENNE_OUT_DEFAULT()
//{
//  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
//  Cayenne.virtualWrite(0, millis());
//  // Some examples of other functions you can use to send data.
//  //Cayenne.celsiusWrite(1, 22.0);
//  //Cayenne.luxWrite(2, 700);
//  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//}
//
//// Default function for processing actuator commands from the Cayenne Dashboard.
//// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}


#define CAYENNE_DEBUG 
#define CAYENNE_PRINT Serial
// WiFi network info.
char ssid[] = "OPPO Find X2";
char wifiPassword[] = "password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "d2c956c0-539b-11ed-bf0a-bb4ba43bd3f6";
char password[] = "991e77320786e82860a5f81172dd13ba73c39b33";
char clientID[] = "d5cfa870-6911-11ed-8d53-d7cd1025126a";

void setup() {
  // put your setup code here, to run once:
Cayenne.begin(username, password, clientID, ssid, wifiPassword);
pinMode(4, OUTPUT);
digitalWrite(4, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
Cayenne.loop();//available from library
}

CAYENNE_IN(0) // COMmAND FROM WEBSITE TO TURN ON AND OFF, chanel 0 from webiste
{
  digitalWrite(4, !getValue.asInt());// digital value 1 or 0 basically, logic is interveted so need to invert command 
}
