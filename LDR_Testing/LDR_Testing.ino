 int light, analogLight;
  void setup() {
  // put your setup code here, to run once:
  pinMode (13, OUTPUT); // Led is connected to pin 13
  Serial.begin(9600);
  }

  void loop() {
  // put your main code here, to run repeatedly:
  light = analogRead(A0); //will gain an ADC value from this function: between 0 and 1023
  Serial.print("Digital value (ADC): ");
  Serial.print(light);
  delay(100);
  analogLight = light * 4.887 ; // ADC * Step size * 10^-3
  Serial.print(" , Analog Input voltage: ");
  Serial.print(analogLight);
  Serial.println(" mV");

  if (light < 40) {  //if value of LDR is less than 40 then LED turns on
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  Serial.println(light);
  delay(100);
  }



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
