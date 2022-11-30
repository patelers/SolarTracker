//Libraries
#include <DHT.h>;

#define DHTPIN 11     // Sensor data pin connected to digital ardunio pin 
#define DHTTYPE DHT22   // DHT 22 type (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
float humid;  //Stores humidity value
float temp; //Stores temperature value
int led = 13 ;

void setup()
{
  pinMode (13, OUTPUT); // Led is connected to pin 13
  Serial.begin(9600); //serial monitor
  dht.begin(); //start the sensor

}

void loop()
{
  delay(2000);
  //Read data and store it to variables humid and temp
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(1000); // Delay 1 sec.

  if (temp > 28) {  // if temp is above 28 led turns high state or else its low state
    digitalWrite(13, HIGH);
    Serial.println("Temperature is too high");
  }
  else {
    digitalWrite(13, LOW);
    Serial.println("Temperature is normal");
  }

  delay(100);
}
