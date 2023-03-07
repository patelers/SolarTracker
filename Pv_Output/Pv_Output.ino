//
//void setup()
//{
//  Serial.begin(9600);
//  pinMode(A5, INPUT);
//}
//
//void loop()
//{
//  // analog values converted to digital values using AD converter
//  float val = analogRead(A5);
//  //Serial.print(val);
//  float divider_volt = analogRead(A5) * (5.0 / 1023);
//  //  float operating_voltage = 2 * divider_volt;
//  Serial.println(" Digital voltage from panel(V): ");
//  Serial.println(divider_volt);//  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt)
//
//  //float current = voltage/100;            //  I=voltage/(R1+R2)
//  float current = divider_volt / 100;
//  Serial.print(" Current from panel(A): ");
//  Serial.println(current);
//  // float current = operating_voltage / 200;          //  I=voltage/(R1+R2)
//  //  float power = operating_voltage * current;
//  float power = divider_volt * current;
//  Serial.print(" Power from panel(W): ");
//  Serial.println(power);
//  //   Serial.print("DATA,TIME,"); // PLX-DAQ command
//
//  //  Serial.print(" , divider_volt: ");
//  //  Serial.print(analogRead(A4));    //send the voltage to serial port
//  //  Serial.println(" aaa");
//
//  //  Serial.print(" , A0 ");
//  //  Serial.print(val);    //send the voltage to serial port
//  //  Serial.println(" V");
//  //  delay(500);
////
//  //  Serial.print(operating_voltage);    //send the voltage to serial port
//  //  Serial.println(" V");
//  //  delay(500)
//
//}

///////////////////////////////////////////////////////
// Working reading of V,P,I : use of one resitor as load, A5 pin and gnd// 2 for higher loads if not reading 

void setup()
{
  Serial.begin(9600);
  pinMode(A15, INPUT);

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time, Started Time, Date, Voltage, Current , Power,Voltage2, Current2 , Power2, ");
  Serial.println("RESETTIMER");
}

void loop()
{
  // analog values converted to digital values using AD converter
  float val = analogRead(A15);
  float val2 = analogRead(A14);
  //Serial.print(val);

/// V, I, P calculations 
  float divider_volt = analogRead(A15) * (5.0 / 1023);
  float divider_volt2 = analogRead(A14) * (5.0 / 1023);
  //  float operating_voltage = 2 * divider_volt; //  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt), comment if only one resistor used
  Serial.print("Digital voltage from panel (V): ");
  Serial.print("Digital voltage from panel2 (V): ");
  Serial.println(divider_volt);
  Serial.println(divider_volt2);
  //  Serial.print(operating_voltage);    //send the voltage to serial port
  //  Serial.println(" V");
  //  delay(500);

  float current = divider_volt / 100; // 100 = resistor value load
  float current2 = divider_volt2 / 100;
  Serial.print("Current from panel(A): ");
  Serial.println(current);
  Serial.print("Current from panel2 (A): ");
  Serial.println(current2);

  float power = divider_volt * current;
  Serial.print("Power from panel(W): ");
  Serial.println(power);
  float power2 = divider_volt2 * current2;
  Serial.print("Power from panel2 (W): ");
  Serial.println(power2);

////////////PLX-DAQ Display
  Serial.print("DATA, TIME, TIMER, DATE, ");
  Serial.print(divider_volt); //display first variable
  Serial.print(","); ; //move to next column
  Serial.print(current); //display second variable
  Serial.print(",");  //move to next column
  Serial.print(power); //display second variable
  Serial.print(","); //move to next column
  //Serial.println(); // move to next row
  //delay(100);

  Serial.print(divider_volt2); //display first variable
  Serial.print(","); //move to next column
  Serial.print(current2); //display second variable
  Serial.print(",");  //move to next column
  Serial.print(power2); //display second variable
  Serial.print(","); //move to next column
  Serial.println(); // move to next row
  //delay(100);
}

////////////////////////////////////////////////////////////
