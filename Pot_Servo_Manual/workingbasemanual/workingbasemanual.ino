#include <Servo.h> //import library 

Servo myservo;   // create servo object to control a servo
int potPin = A0;  // analog pin used to connect potentiometer
int potVal;       // variable to store the value read from the potentiometer
int maxPos = 130; // set the max base rotation number (0 to 180)

void setup() {
  Serial.begin(9600);          //  setup serial
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  potVal = analogRead(potPin);            // reads value from potentiometer at analog pin (value between 0 and 1023)
  Serial.print("Potentiometer Value:"); // prints the value on serial monitor, the ADC value read by ardunio 0 to 1023
  Serial.println(potVal);
  Serial.print(" "); //print space between the value

  potVal = map(potVal, 0, 1023, 0, maxPos);     // scale it to use it with the servo (value between 0 and 180) so 1023 value is max reotation of 180
  myservo.write(potVal);                  // sets the servo position according to the scaled value
  Serial.print("positon Value:");
  Serial.print(potVal); // prints value of val
  Serial.println(); //prints on a new line
  delay(10);                           // waits for the servo to get there, waits for loop to execute again

}
