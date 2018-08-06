#include "DHTesp.h" //library: https://github.com/beegee-tokyo/DHTesp
#define dht_dpin 26
#define DHTTYPE DHT22

DHTesp dht;
 
void setup()
{
  Serial.begin(115200);
 
  dht.setup(dht_dpin,DHTesp::DHTTYPE);
}
 
void loop()
{
  int  temperature = dht.getTemperature();
 
  Serial.print("Temperature: ");
  Serial.println(temperature);

  int humidity=dht.getHumidity();
  Serial.print("Humidity:");
  Serial.println(humidity);
  delay(1000);
 
}
