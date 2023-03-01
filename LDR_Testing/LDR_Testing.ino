float light, analogLight, light2, analogLight2, light3, analogLight3, light4, analogLight4;
void setup() {
  // put your setup code here, to run once:
 // pinMode (13, OUTPUT); // Led is connected to pin 13
  Serial.begin(9600);
}

void loop() {

// top left LDR
  light = analogRead(A2); //will gain an ADC value from this function: between 0 and 1023
  Serial.print("Analog value2 (ADC): ");
  Serial.print(light);
  delay(500);
  analogLight = light * (5.0 / 1023) ; // ADC
  Serial.print(" ,Digital Output voltage2: ");
  Serial.print(analogLight);
  Serial.println(" V");

//top right LDR
  light2 = analogRead(A1); //will gain an ADC value from this function: between 0 and 1023
  Serial.print("Analog value (ADC): ");
  Serial.print(light2);
  delay(500);
  analogLight2 = light2 * (5.0 / 1023) ; // ADC 
  Serial.print(" , Digital Output voltage: ");
  Serial.print(analogLight2);
  Serial.println(" V");

//bottom right LDR
  light3 = analogRead(A3); //will gain an ADC value from this function: between 0 and 1023
  Serial.print("Analog value3 (ADC): ");
  Serial.print(light3);
  delay(500);
  analogLight3 = light3 * (5.0 / 1023) ; // ADC 
  Serial.print(" , Digital Output voltage3: ");
  Serial.print(analogLight3);
  Serial.println(" V");

//bottom left LDR
 light4 = analogRead(A4); //will gain an ADC value from this function: between 0 and 1023
  Serial.print("Analog value4 (ADC): ");
  Serial.print(light4);
  delay(500);
  analogLight4 = light4 * (5.0 / 1023) ; // ADC 
  Serial.print(" ,   Digital Output voltage4: ");
  Serial.print(analogLight4);
  Serial.println(" V");




}


//  if (light < 40) {  //if value of LDR is less than 40 then LED turns on
//    digitalWrite(13, HIGH);
//  }
//  else {
//    digitalWrite(13, LOW);
//  }
//  Serial.println(light);
//  delay(100);
//  }



//int light;
//
//void setup() {
//  Serial.begin(9600);
//}
//
//void loop () {
//  light = analogRead(A0); //LDR connection
//  Serial.println(light); //light value printed on serial monitor
//  delay(100); // every 100ms

//}


/* for trial file sketch 
////// horizontl axis tracking 
  if (abs(diffazi) >= threshold_value) {       //Change   position only if light difference is bigger then the threshold_value
    if   (diffazi > 0) {
      if (servo_rightleft.read() < 180) {
        servo_rightleft.write((servo_updown.read()   + 2));
      }
    }
    if (diffazi <  0) {
      if (servo_rightleft.read()   > 0) {
        servo_rightleft.write((servo_updown.read() - 2));
      }
    }
  }

  /////// up-down movement of solar tracker
if (abs(diffelev) >= threshold_value) {   //Change position only if light   difference is bigger then thethreshold_value
  if (diffelev > 0) {
    if   (servo_updown.read() < 180) {
      servo_updown.write((servo_rightleft.read()   - 2));
    }
  }
  if (diffelev <  0) {
    if (servo_updown.read()   > 0) {
      servo_updown.write((servo_rightleft.read() + 2));
    }
  }
}
}



  // servoh = servo_x.read();
  servo_updown_y = servo_updown.read();
  // servov = servo_z.read();
  servo_rightleft_x = servo_rightleft.read();

*\
