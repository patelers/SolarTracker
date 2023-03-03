// Servo motor library
#include <Servo.h>
//Initialize variables
int mode = 0; // either automatic or manual vairable intialised
int axe = 0; // either up-down or left-right vairable intialised
int buttonState1 = 0; // current state (A or M) control
int buttonState2   = 0; // current state (up-down or left-right) control
int prevButtonState1 = 0; // remember previous state (A or M)
int prevButtonState2 = 0; // remember previous axis state, detects when button state changes from not pressed to pressed (vice versa)

int ldrtopr = A1;   // top-right LDR Aduino pin
int ldrtopl = A2;   // top-left LDR Aduino pin
int ldrbotr = A3;   // bottom-right LDR Aduino pin
int ldrbotl = A4;   // bottom-left LDR Aduino pin

int topr, topl, botr, botl; //declare variables needed to find averages
//int topl = 0;
//int topr = 0;
//int botl = 0;
//int   botr = 0;

//Declare two servos
Servo servo_updown; //servo_z Variable declared used to control servo using PWM
int servo_updown_y = 0; //variable to store current position of servo
int servo_updown_y_limitHigh = 170; // set max position of servo 170
int servo_updown_y_limitLow = 10; // set minimum position of servo 10

Servo servo_rightleft; //servo_x
int servo_rightleft_x = 0; //variable to store current position of servo
int servo_rightleft_x_limitHigh = 170; // set max position of servo 170
int servo_rightleft_x_limitLow = 10; // set minimum position of servo 10

int   threshold_value = 15; //measurement sensitivity

void setup()
{
  Serial.begin(9600);   //serial connection setup  //opens   serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");  //clear all data that’s been place in already
  // Serial.println("LABEL,t,voltage,current,power,Mode");    //define the column headings (PLX-DAQ command)

  pinMode(4, INPUT);  //Mode switch Button between automatic and manual
  pinMode(5, INPUT);  //Axis switch between right-left or up-down
  pinMode(A0, INPUT); //Potentiometer for right-left movement and for up-down movement

  servo_updown.attach(8);  // pin 8 used to control angle and position of servo
  servo_rightleft.attach(9); // pin 9 used to control angle and position of servo

  servo_updown.write(5); //set the initial positions of vertical servo
  servo_rightleft.write(10); ////set the initial positions of horizontal servo

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
  if (buttonState1 != prevButtonState1)   { //if button state is different from previous button state value then button has changed state
    if (buttonState1 == HIGH) {   //if button state is 1 check mode value
      //Change mode
      if (mode == 1) {  //if mode equals to 1 then it sets mode to 0
        mode = 0;
      } else {    //if mode is still 0 then mode becomes 1
        mode = 1;
      }
    }
  }

  prevButtonState1 = buttonState1;
  delay(100); // Wait for 50 millisecond(s)

  if (mode == 0) {
    Mode = 'M';
    Serial.println(Mode);   //send Mode "M" to serial port
    manualsolartracker(); //execute manual tracking function
  } else { // mode automatic
    Mode = 'A';
    Serial.println(Mode); //send Mode "A" to serial port
    automaticsolartracker(); //send Mode "Automatic" to serial port
  }

}

/////////////////////////////////////////////////////////////////////////////////
void automaticsolartracker() {

  ////// capturing analog values of each LDR
  topr = analogRead(ldrtopr);   //capturing analog value of top right LDR
  topl = analogRead(ldrtopl);   //capturing analog value of top left LDR
  botr = analogRead(ldrbotr);   //capturing analog value of bot right LDR
  botl = analogRead(ldrbotl);   //capturing analog value of bot left LDR

  // servoh = servo_x.read();
  servo_updown_y = servo_updown.read(); // read the current positions of vertical and horizontal servos
  Serial.print("servo_updown_y: ");
  Serial.println(servo_updown_y);
  
  // servov = servo_z.read();
  servo_rightleft_x = servo_rightleft.read(); // and store them as variables, allows to keep track of position 
  Serial.print("servo_rightleft_x: ");
  Serial.print(servo_rightleft_x);

  ///// calculating average
  int avgtop = (topr + topl) / 2;     //average   of top LDRs
  Serial.print("Average of top LDRs: ");
  Serial.println(avgtop);
  int avgbot = (botr + botl) / 2;     //average of bottom LDRs
  Serial.print("Average of bottom LDRs: ");
  Serial.println(avgbot);
  int avgleft = (topl + botl) / 2;    //average of left LDRs
  Serial.print("Average of left LDRs: ");
  Serial.println(avgleft);
  int avgright   = (topr + botr) / 2;   //average of right LDRs
  Serial.print("Average of right LDRs: ");
  Serial.println(avgright);

  ///// Get the difference
  int diffelev = avgtop - avgbot;      //Get the different average between LDRs top and LDRs bot
  Serial.print("diffelev: ");
  Serial.println(diffelev);
  int diffazi = avgleft - avgright;    //Get the different average betwen LDRs right and LDRs left
   Serial.print("diffazi: ");
  Serial.println(diffazi);


  ///////// horizontl axis tracking
  if (abs(diffelev) <= threshold_value) // check if the diffrence is less than the set required value
  {
    servo_updown.write(servo_updown_y); //stop the updown servo if above statement true
  } else  {
    if   (diffelev > threshold_value) // if the difference is more then rotate vertical servo
    { Serial.println(" x -   2 ");
      servo_updown.write(servo_updown_y  - 2); // clockwise rotation by 2 deg
      if ( servo_updown_y > servo_updown_y_limitHigh) // check if new position now exceeds a defined limit
      {
        servo_updown_y = servo_updown_y_limitHigh; // if true then set the servo at the max position no more rotation
      }
      delay(30); //10
    } else {
      servo_updown.write(servo_updown_y   + 2); // else increment position CCW rotation 2 deg
      if ( servo_updown_y < servo_updown_y_limitLow)
      {
        servo_updown_y = servo_updown_y_limitLow; // if true then set the servo at the min position no more rotation
      }
      delay(30);//10
    }
  }

  ///////tracking according to vertical axis
  if (abs(diffazi) <= threshold_value) // check if the diffrence is less than the set required value
  {
    servo_rightleft.write(servo_rightleft_x); //stop the horizontal servo if above statement true
  } else  {
    if   (diffazi > threshold_value) // if the difference is more then rotate horizontal servo
    {
      servo_rightleft.write(servo_rightleft_x  - 2); // clockwise rotation by 2 deg
      if ( servo_rightleft_x > servo_rightleft_x_limitHigh) // check if new position now exceeds a defined limit
      {
        servo_rightleft_x = servo_rightleft_x_limitHigh; // if true then set horizontal servo at the max position no more rotation
      }
      delay(10);
    } else {
      servo_rightleft.write(servo_rightleft_x   + 2); // increment position of servo by 2 deg, take current position + 2 (CW) then writes new position 
      if ( servo_updown_y < servo_updown_y_limitLow) 
      {
        servo_rightleft_x = servo_rightleft_x_limitLow; // if true then set the servo at the min position no more rotation
      }
      delay(10);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
void manualsolartracker() {
  buttonState2 = digitalRead(5); // initially given 0 = read pin 5 to be 0 (off) and 1 (on)
  Serial.print("buttonState2: ");
  Serial.println(buttonState2); 

  if (buttonState2 != prevButtonState2) { //if button state2 is different from previous button state2 value then button has changed state
    if (buttonState2   == HIGH) { //if button state is 1 check axis value
      if   (axe == 1) { //if axis equals to 1 then it sets axis to 0
        axe = 0; // indicates button clicked and change axis control 
      } else {
        axe = 1;
      }
    }
  }
  
  prevButtonState2 = buttonState2; // new button state updated 
  delay(100); // Wait for 100 milliseconds
  
  if (axe == 0) {     //control horizontal movement
    servo_rightleft.write(map(analogRead(A0),   0, 1023, 0, 130)); // potentiometer control 
  } else { // //control vertical movement
    servo_updown.write(map(analogRead(A0),   0, 1023, 0, 130)); // potentiometer control
  }
}
/////////////////////////////////////////////////////////////////////
