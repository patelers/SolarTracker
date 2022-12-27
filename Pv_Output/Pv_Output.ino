
void setup()
{
  Serial.begin(9600);
  pinMode(A7, INPUT);
}

void loop()
{
  // analog values converted to digital values using AD converter
  float val = analogRead(A7);
  float divider_volt = analogRead(A0) * (5.0 / 1023);
  float operating_voltage = 2 * divider_volt;              //  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt)
 
  //float current = voltage/20;            //  I=voltage/(R1+R2)
//  float current = operating_voltage / 200;          //  I=voltage/(R1+R2)
//  float power = operating_voltage * current;
  //   Serial.print("DATA,TIME,"); // PLX-DAQ command

//  Serial.print(" , divider_volt: ");
//  Serial.print(analogRead(A4));    //send the voltage to serial port
//  Serial.println(" aaa");

  Serial.print(" , A0 ");
  Serial.print(val);    //send the voltage to serial port
  Serial.println(" V");
  delay(500);

  Serial.print(" , Digital voltage from panel: ");
  Serial.print(operating_voltage);    //send the voltage to serial port
  Serial.println(" V");
  delay(500);

//  Serial.print(" , Current: ");
//  Serial.print(current);    //send the current to serial port
//  Serial.println(" A");
//
//  Serial.print(" , Power: ");
//  Serial.print(power);  //send the power to serial port
//  Serial.println(" W");

}

//
// #include <Wire.h>
//
// void setup()  
// {  
//  Serial.begin(9600); // sensor buart rate  
//
// }  
// void loop()  
// {  
//  int sensorValue = analogRead(A4); // Solar Panel Positive PIN connect to A0  
//  float voltage = sensorValue * (5.0 / 1023.0);  
//   Serial.print("voltage  ");  
//   Serial.println(voltage);  
//     
//   delay(500);   
// } 
