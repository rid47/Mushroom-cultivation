#include "DHTesp.h"
 
DHTesp dht;
 
void setup()
{
  Serial.begin(115200);
 
  dht.setup(26,DHTesp::DHT22);
}
 
void loop()
{
  float temperature = dht.getTemperature();
 
  Serial.print("Temperature: ");
  Serial.println(temperature);

  int humidity=dht.getHumidity();
  Serial.print("Humidity:");
  Serial.println(humidity);
  delay(10000);
 
}
