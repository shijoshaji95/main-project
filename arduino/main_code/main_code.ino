
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "home-automation-c6c30.firebaseio.com"
#define FIREBASE_AUTH "7TpxFfHBlUes1nSDNBsY41QrqUt9OzDCnPmBMMDI"
#define WIFI_SSID "Shijo_Shaji"
#define WIFI_PASSWORD "12345679"

#define Relay1 D6 
int rel1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//HIGH  ;;digitalWrite(D6,HIGH)
  pinMode(Relay1,OUTPUT);
  digitalWrite(Relay1,LOW);
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
}

void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
  
void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
   rel1=Firebase.getString("FB1").toInt();    //Reading the value of the varialble Status from the firebase
    if(rel1==1)                               // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,HIGH);
      Serial.println("Relay 1 ON");
    }
 if(rel1==0)                                  // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,LOW);
      Serial.println("Relay 1 OFF");
    }


  
}
