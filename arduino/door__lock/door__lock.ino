
 void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, INPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D0, HIGH);
  Serial.begin(9600);
}
 
void loop() {
  
   if (digitalRead(D1)==HIGH){
    Serial.println("Your Door is Closed");
    
  }
  else {
      Serial.println("Your Door is Open");
  }
  delay(500);
  /*digitalWrite(D1, LOW);
  digitalWrite(D0, HIGH);*/
  
}
