void setup(){
  pinMode(D6, OUTPUT); // Set buzzer - pin 9 as an output//+=pin D6; -=Gnd
}

void loop(){
  tone(D6, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(D6);     // Stop sound...
  delay(1000);        // ...for 1sec
}
