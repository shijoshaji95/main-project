void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(D5);
  sensorVoltage = sensorValue/1024*5.0;
 
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print("**sensor value = ");
  Serial.println(sensorValue);
  delay(1000);
}
