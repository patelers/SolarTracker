//#define CAYENNE_PRINT Serial
//#include <CayenneMQTTEthernet.h>    //CayenneMQTT library
#include <Servo.h>                  //Servo motor library 
//#include <DHT.h>                    //DHT library
//#define DHTTYPE DHT22
//#define DHTPIN 2
//DHT dht(DHTPIN,DHTTYPE);

//MQTT credentials
//char username[]="498d2d00-afe2-11ea-883c-638d8ce4c23d";
//char password[]="ab4a8f92d94033c01f6e18ce1d8a84d8c304c9c4";
//char clientID[]="17798a40-b968-11ea-93bf-d33a96695544";

Servo servo_x;                   //up-down servomotor
int servoh = 0;
int servohLimitHigh = 170;
int servohLimitLow = 10;

Servo servo_z;                   //left-right servomotor
int servov = 0;
int servovLimitHigh = 170;
int servovLimitLow = 10;

int topl, topr, botl, botr;
int threshold_value = 10;
float Vout;

void setup()
{ Serial.begin(9600);
  // Cayenne.begin(username, password, clientID);
  servo_x.attach(5);
  servo_z.attach(6);
  servo_z.write(90);  // set servo to mid-point
  //dht.begin();
  // pinMode(3,OUTPUT);
  // digitalWrite(3,LOW);
}

void loop()
{ topr = analogRead(A0);
  topl = analogRead(A1);
  botl = analogRead(A2);
  botr = analogRead(A3);
  //Vout = (analogRead(A4) * 5.0) / 1023;
  // Serial.println(" Manual-mode");
  // Cayenne.loop();

  //if (digitalRead(3) == HIGH) {

  servoh = servo_x.read();
  servov = servo_z.read(); // read the current angle of the servo (the value passed to the last call to Servo.write()
  int avgtop = (topr + topl) / 2;
  int avgbot = (botr + botl) / 2;
  int avgright = (topr + botr) / 2;
  int avgleft = (topl + botl) / 2;

  int diffhori = avgtop - avgbot;
  int diffverti = avgleft - avgright;

  /*tracking according to horizontal axis*/
  if (abs(diffhori) <= threshold_value)
  {
    servo_x.write(servoh);            //stop the servo up-down
  } else {
    if (diffhori > threshold_value)
    { Serial.println(" x - 2 ");
      servo_x.write(servoh - 2);   //Clockwise rotation CW
      if (servoh > servohLimitHigh)
      {
        servoh = servohLimitHigh;
      }
      delay(10);
    } else {
      servo_x.write(servoh + 2);  //CCW
      if (servoh < servohLimitLow)
      {
        servoh = servohLimitLow;
      }
      delay(10);
    }
  }
  /*tracking according to vertical axis*/
  if (abs(diffverti) <= threshold_value)
  {
    servo_z.write(servov);       //stop the servo left-right
  } else {
    if (diffverti > threshold_value)
    {
      servo_z.write(servov - 2); //CW
      if (servov > servovLimitHigh)
      {
        servov = servovLimitHigh;
      }
      delay(10);
    } else {
      servo_z.write(servov + 2); //CCW
      if (servov < servovLimitLow)
      {
        servov = servovLimitLow;
      }
      delay(10);
    }
  }
}

// Cayenne Functions
//CAYENNE_IN(8) {
//  int value = getValue.asInt();
//  CAYENNE_LOG("Channel %d, pin %d, value %d", 8, 3, value);
//  digitalWrite(3, value);
//}
//CAYENNE_IN(7) { //up-down servo motor
//  if (digitalRead(3) == HIGH) { //Automatic_mode
//  }
//  else { //Manual_mode
//    servo_x.write(getValue.asDouble() * 180);
// }
//}
//CAYENNE_IN(6) { //left-right servo motor
//  if (digitalRead(3) == HIGH) {
// }
// else {
//   servo_z.write(getValue.asDouble() * 180);
// }
//}

//CAYENNE_OUT(0) { //Current
//  float current = Vout / 10;
//  Cayenne.virtualWrite(0, current);
//  Serial.print("Current: ");
//  Serial.println(current);
//}
//CAYENNE_OUT(1) { //Voltage
//  float voltage = Vout * 2;
//  Cayenne.virtualWrite(1, voltage);
//  Serial.print("Voltage: ");
//  Serial.println(voltage);
//}
//CAYENNE_OUT(2) { //LDR Top-right
//  Cayenne.virtualWrite(2, topr);
//}
//CAYENNE_OUT(3) { //LDR Top-left
//  Cayenne.virtualWrite(3, topl);
//}
//CAYENNE_OUT(4) { //LDR Bot-left
//  Cayenne.virtualWrite(4, botl);
//}
//CAYENNE_OUT(5) { //LDR Bot-right
//  Cayenne.virtualWrite(5, botr);
//}
//CAYENNE_OUT(10) { //Power
//  float power = (Vout * 2 * Vout) / 10 ;
//  Cayenne.virtualWrite(10, power);
//  Serial.print("Power: ");
//  Serial.println(power);
//}
//CAYENNE_OUT(11) { //Temperature
//  float t = dht.readTemperature();
//  //int chk = dht.read(DHT11PIN);
//  Cayenne.virtualWrite(11, t, TYPE_TEMPERATURE, UNIT_CELSIUS);
//  Serial.print("temperature: ");
//  Serial.println(t);
//}
//CAYENNE_OUT(12) { //Huidity
//  float h = dht.readHumidity();
//  //int chk = dht.read(DHT11PIN);
//  Cayenne.virtualWrite(12, h);
//  Serial.print("  humidity: ");
//  Serial.println(h);
//}
