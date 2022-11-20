#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
// WiFi network info.
char ssid[] = "OPPO Find X2";
char wifiPassword[] = "password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "d2c956c0-539b-11ed-bf0a-bb4ba43bd3f6";
char password[] = "991e77320786e82860a5f81172dd13ba73c39b33";
char clientID[] = "f3d80050-6921-11ed-8d53-d7cd1025126a";

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
