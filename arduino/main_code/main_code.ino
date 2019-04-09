
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h> 
 
Servo myservo; 

// Set these to run example.
#define FIREBASE_HOST "home-automation-c6c30.firebaseio.com"
#define FIREBASE_AUTH "7TpxFfHBlUes1nSDNBsY41QrqUt9OzDCnPmBMMDI"
#define WIFI_SSID "Shijo"
#define WIFI_PASSWORD "12345679"

#define Relay1 D5 
#define Relay2 D6
 
int rel1,rel2;
float sensorValue;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//HIGH  ;;digitalWrite(D6,HIGH)

  myservo.attach(D2);  // attaches the servo on GIO2 to the servo object   
  
  pinMode(Relay1,OUTPUT);
  digitalWrite(Relay1,HIGH);
  pinMode(Relay2,OUTPUT);
  digitalWrite(Relay2,HIGH);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("FB1",0); 
  Firebase.setInt("FB2",0);  
}

void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
  
void loop() {

   
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }

   //***************************************
   rel1=Firebase.getString("FB1").toInt();    //Reading the value of the varialble Status from the firebase
   if(rel1==1)                                // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,LOW);
      Serial.println("Relay 1 ON");
    }
  if(rel1==0)                                  // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("Relay 1 OFF");
    }
     float sensorValue;
     //******************************************
   rel2=Firebase.getString("FB2").toInt();    //Reading the value of the varialble Status from the firebase
   if(rel2==1)                                // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("Door is lock");
      myservo.write(0);
    }
  if(rel2==0)                                  // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("Door is unlock");
      myservo.write(180);
    }
     
     //******************************************
 
  sensorValue = analogRead(D7);            //read sensor value from relay2 D7 pin--A0 pin
  Serial.print("**sensor value = ");
  Serial.println(sensorValue);
  if(sensorValue <= 1000)
     Firebase.setFloat("FB3", 2);           // upload value to firebase
  else
    Firebase.setFloat("FB3", 0);


  
}
