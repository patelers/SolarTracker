//#include <Servo.h> //import library
//
//int mode = 0;
//int axe = 0;
//
////Servo myservo;    // create servo object to control a servo
//int potPin = A0;  // analog pin used to connect potentiometer
//int potVal;       // variable to store the value read from the potentiometer
//int maxPos = 130; // set the max base rotation number (0 to 180)
//
//int  buttonState1 = 0;
//int buttonState2 = 0;
//int prevButtonState1 = 0;
//int prevButtonState2 = 0;
//
//int mode = 0;
//int axe = 0;
//Servo servo_updown;
//Servo servo_leftright;
//
//void setup() {
//
//  Serial.begin(9600);          //  setup serial
//  servo_leftright.attach(9);  // attaches the servo on pin 9 to the servo object
//
//  pinMode(3, INPUT); //Axis Switch
//  servo_updown.attach(8);
//  pinMode(4, INPUT);
//  // pinMode(A0, INPUT); //Axis Switch
//
//  void loop() {
//
//    char Mode;
//
//    potVal = analogRead(potPin);            // reads value from potentiometer at analog pin (value between 0 and 1023)
//    Serial.print("Potentiometer Value:"); // prints the value on serial monitor, the ADC value read by ardunio 0 to 1023
//    Serial.print(potVal);
//    Serial.print(" "); //print space between the value
//
//    //  potVal = map(potVal, 0, 1023, 0, maxPos);     // scale it to use it with the servo (value between 0 and 180) so 1023 value is max reotation of 180
//    //  myservo.write(potVal);                  // sets the servo position according to the scaled value
//    //  Serial.print("positon Value:");
//    //  Serial.print(potVal); // prints value of val
//    //  Serial.println(); //prints on a new line
//    //  delay(10);                           // waits for the servo to get there, waits for loop to execute again
//
//    buttonState1 = digitalRead(4);
//    if (buttonState1 != prevButtonState1) {
//      if (buttonState1 == HIGH) {
//        if (mode == 1) {
//          mode = 0;
//        } else {
//          mode = 1;
//        }
//      }
//    }
//
//    prevButtonState1 = buttonState1;
//    delay(50);
//
//    if (mode == 0) {
//      Mode = 'M';
//      Serial.println(Mode);
//      manualControl();
//
//    } else {
//      Mode = 'A';
//      Serial.println(Mode);
//    }
//
//    void manualControl() {
//      buttonstate2 = digitalRead(3);
//      if (buttonstate2 == HIGH) {
//        if (axe == 1) {
//          axe = 0;
//        }
//      }
//    }
//    prevButtonState2 = buttonState2 ;
//    delay(50);
//    if (axe == 0) {
//      servo_leftright.write(map(potVal, 0, 1023, 0, maxPos));
//    } else {
//      servo_updown.write(map(potVal, 0, 1023, 0, maxPos));
//    }
//  }
//
//}



//Servo motor library
#include <Servo.h>
//Initialize variables
int mode = 0;
int axe = 0;
int buttonState1 = 0;
int buttonState2   = 0;
int prevButtonState1 = 0;
int prevButtonState2 = 0;

//int ldrtopr=   0;                // top-right LDR
//int ldrtopl = 1;                // top-left LDR
//int ldrbotr = 2;               //   bottom-right LDR
//int ldrbotl = 3;               // bottom-left   LDR
//int topl = 0;
//int topr = 0;
//int botl = 0;
//int   botr = 0;

//Declare two servos
Servo servo_updown;
Servo servo_rightleft;

int   threshold_value = 10;         //measurement sensitivity

void setup()
{
  Serial.begin(9600);                                //serial connection setup  //opens   serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");                       //clear   all data that’s been place in already
  // Serial.println("LABEL,t,voltage,current,power,Mode");    //define the column headings (PLX-DAQ command)

  pinMode(4, INPUT);              //Mode switch Button between automatic and manual
  pinMode(5, INPUT);              //Axis switch between right-left or up-down
  pinMode(A0,   INPUT);              //Potentiometer for right-left movement and for up-down movement

  servo_updown.attach(8);             //Servo motor up-down movement
  servo_rightleft.attach(9);           //Servo motor right-left movement
}

void loop()
{
  //  pv_power();
  char   Mode; // store a character
  //pv output
  //    float volt = analogRead(A5)*5.0/1023;
  //    float voltage = 2*volt;                 //  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt)
  //     float current = voltage/20;            //  I=voltage/(R1+R2)
  //    float power   = voltage*current;
  //   Serial.print("DATA,TIME,"); // PLX-DAQ command
  //    Serial.print(voltage);     //send the voltage to serial port
  //    Serial.print(",");
  //    Serial.print(current);     //send the current to serial port
  //    Serial.print(",");
  //    Serial.print(power);   //send the power to serial port
  //    Serial.print(",");

  //Serial.println(Mode);
  buttonState1 = digitalRead(4); // initially given 0 = read pin 4 to be 0 (off) and 1 (on)
  Serial.println(buttonState1); // print on serial monitor the value, once button pressed gives 1 and not pressed gives 0
  Serial.println("1 = on(Manual or Auto Mode), 0 = off(Reset) button state");
  if (buttonState1 != prevButtonState1)   { //if 0 doesnt equal 0 and if 1 doesnt equal 0
    if (buttonState1 == HIGH) {             //if button state is 1
      //Change mode and ligh up the correct   indicator
      if (mode == 1) {                      //if mode changes to 1 from 0 then mode is 0
        mode = 0;
      } else {                              //if mode is still 0 then mode becomes 1
        mode = 1;
      }
    }
  }
  prevButtonState1 = buttonState1;
  delay(50); // Wait for 50 millisecond(s)

  if (mode == 0) {
    Mode = 'M';
    Serial.println(Mode);   //send Mode "Manual" to serial port
    manualsolartracker();
  } else { // mode automatic
    Mode = 'A';
    Serial.println(Mode);
    //    automaticsolartracker(); //send Mode "Automatic" to serial port
  }
  //}
}

//void   automaticsolartracker() {
//
//  //capturing analog values of each LDR
//  topr = analogRead(ldrtopr);        //capturing analog value of top right LDR
//  topl = analogRead(ldrtopl);        //capturing analog value of top left LDR
//  botr = analogRead(ldrbotr);        //capturing analog value of bot right LDR
//  botl = analogRead(ldrbotl);        //capturing analog value of bot left LDR
//
//  // calculating average
//  int avgtop = (topr + topl) / 2;     //average   of top LDRs
//  int avgbot = (botr + botl) / 2;     //average of bottom LDRs
//  int avgleft = (topl + botl) / 2;    //average of left LDRs
//  int avgright   = (topr + botr) / 2;   //average of right LDRs
//
//  //Get the different
//  int diffelev = avgtop - avgbot;      //Get the different average betwen   LDRs top and LDRs bot
//  int diffazi = avgright - avgleft;    //Get the different   average betwen LDRs right and LDRs left
//
//  //left-right movement of   solar tracker
//
//  if (abs(diffazi) >= threshold_value) {       //Change   position only if light difference is bigger then the threshold_value
//    if   (diffazi > 0) {
//      if (servo_rightleft.read() < 180) {
//        servo_rightleft.write((servo_updown.read()   + 2));
//      }
//    }
//    if (diffazi <  0) {
//      if (servo_rightleft.read()   > 0) {
//        servo_rightleft.write((servo_updown.read() - 2));
//      }
//    }
//  }
//
//  //up-down movement of solar tracker
//  if (abs(diffelev) >= threshold_value) {   //Change position only if light   difference is bigger then thethreshold_value
//    if (diffelev > 0) {
//      if   (servo_updown.read() < 180) {
//        servo_updown.write((servo_rightleft.read()   - 2));
//      }
//    }
//    if (diffelev <  0) {
//      if (servo_updown.read()   > 0) {
//        servo_updown.write((servo_rightleft.read() + 2));
//      }
//    }
//  }
//}
/////////////////////////////////////////////////////
void manualsolartracker() {
  buttonState2 = digitalRead(5);
  Serial.println(buttonState2);
  Serial.print("buttonState2");

  if (buttonState2 != prevButtonState2) {
    if (buttonState2   == HIGH) {
      //Change mode and ligh up the correct indicator
      if   (axe == 1) {
        axe = 0;
      } else {
        axe = 1;
      }
    }
  }

  prevButtonState2 = buttonState2;
  delay(100); // Wait for 100   millisecond(s)
  if (axe == 0) {     //control right-left movement
    servo_rightleft.write(map(analogRead(A0),   0, 1023, 0, 130));
  } else { // //control up-down movement
    servo_updown.write(map(analogRead(A0),   0, 1023, 0, 130));
  }
}
