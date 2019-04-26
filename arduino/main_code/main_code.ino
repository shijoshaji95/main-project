//d0-door sensor
//d1-gas sensor
//d2-door
//d3-d4-display ac
//d5-light
//D6-buzzer

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

 
Servo myservo; 

// Set these to run example.
#define FIREBASE_HOST "home-automation-c6c30.firebaseio.com"
#define FIREBASE_AUTH "7TpxFfHBlUes1nSDNBsY41QrqUt9OzDCnPmBMMDI"
#define WIFI_SSID "ProjectNetwork"
#define WIFI_PASSWORD "ihopethisnetworkstays"

#define Relay1 D5 //light


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int REED_PIN = D0; // Pin connected to reed switch
int rel0,rel1,rel2,rel3,rel4,rel6,rel7;
float sensorValue;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//HIGH  ;;digitalWrite(D6,HIGH)

 Wire.begin(D3,D4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  pinMode(REED_PIN, OUTPUT);
  myservo.attach(D2);  // attaches the servo on GIO2 to the servo object [Door]  
  pinMode(D6, OUTPUT); // Set buzzer - pin 9 as an output//+=pin D6; -=Gnd
  pinMode(Relay1,OUTPUT);
  digitalWrite(Relay1,LOW);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
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
  
  Firebase.setString("FB0","0");
  Firebase.setString("FB1","0"); 
  Firebase.setString("FB2","0"); 
  Firebase.setString("FB3","0");
  Firebase.setString("FB6","1"); 
  Firebase.setString("FB7","0"); 
   
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
    //**************************************

   
  rel0=Firebase.getString("FB0").toInt();    //Reading the value of the varialble Status from the firebase
  display.display();
  delay(100);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  
  if(rel0==0)                                // If, the Status is 1, turn on the Relay1
    {

    display.setTextSize(3); // Draw 2X-scale text
    display.println(F("AC OFF "));
          
    }
  else                                  // If, the Status is 0, turn Off the Relay1
     {                                      

     display.setTextSize(1.5); // Draw 2X-scale text
     display.println(F("       AC ON "));
     display.println(F(" "));
     display.print(F("      Temp : "));
     display.println(rel0);
       
     }

  display.display();      // Show initial text
  delay(100);
  // Scroll in various directions, pausing in-between:
 


   //***************************************
   rel1=Firebase.getString("FB1").toInt();    //Reading the value of the varialble Status from the firebase
   Serial.println(rel1);
   if(rel1==1)                                // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,HIGH);
      Serial.println("Relay 1 ON");
     }
   if(rel1==0)                                  // If, the Status is 0, turn Off the Relay1
     {                                      
      digitalWrite(Relay1,LOW);
      Serial.println("Relay 1 OFF");
     }
        //******************************************
   rel2=Firebase.getString("FB2").toInt();    //Reading the value of the varialble Status from the firebase
   if(rel2==1)                                // If, the Status is 1, turn on the Relay2
     {
     
      Serial.println("Door is lock");
      myservo.write(0);
     }
   if(rel2==0)                                  // If, the Status is 0, turn Off the Relay2
     {                                      
      
      Serial.println("Door is unlock");
      myservo.write(100);
     }
     //******************************************
   rel3=Firebase.getString("FB3").toInt();     //gas sensor  
   Serial.println(rel3);
  if(rel3==2)                                // If, the Status is 1, turn on the Relay2
        {
           Serial.println("notification on");
           Firebase.setString("FB6","0");
           tone(D6, 1000); // Send 1KHz sound signal...
        }
    if(rel3==0)                                    // If, the Status is 0, turn Off the Relay2
    {                                      
      Serial.println("notification off");
      noTone(D6);
    }
     //******************************************
   rel4=Firebase.getString("FB4").toInt();     //door sensor  
   Serial.println(rel4);
   if(rel2==1)                                // If, the Status is 1, turn on the Relay2
     {
   if(rel4==2)                                // If, the Status is 1, turn on the Relay2
     {
      Serial.println("notification on");
      tone(D6, 1000); // Send 1KHz sound signal...
     }
     }
   if(rel4==0)                                    // If, the Status is 0, turn Off the Relay2
    {                                      
      Serial.println("notification off");
      noTone(D6);
    }
     //******************************************
    rel7=Firebase.getString("FB7").toInt();
    if(rel7==2)                                // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(D8,HIGH);
      Serial.println("d8 is ON");
     }
   if(rel7==0)                                  // If, the Status is 0, turn Off the Relay1
     {                                      
      digitalWrite(D8,LOW);
      Serial.println("D8 1 OFF");
     }
      //***************************************
   rel6=Firebase.getString("FB6").toInt();    //Reading the value of the varialble Status from the firebase
   if(rel6==1)                                // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(D7,HIGH);
      Serial.println("d7 1 ON");
     }
   if(rel6==0)                                  // If, the Status is 0, turn Off the Relay1
     {                                      
      digitalWrite(D7,LOW);
      Serial.println("D7 1 OFF");
     }
        //******************************************
 
   sensorValue = analogRead(D1);            //read sensor value from relay2 D7 pin--A0 pin
   Serial.print("**sensor value = ");
   Serial.println(sensorValue);
   if(sensorValue <= 1000)
      Firebase.setString("FB3","2");           // upload value to firebase
      
   if(sensorValue >= 1000)
      Firebase.setString("FB3","0");
    //******************************************
   int sensorValue1 = analogRead(A0);          //read sensor value from relay2 D7 pin--A0 pin
   Serial.print("**sensor value1 = ");
   Serial.println(sensorValue1);
   if(sensorValue1 <= 30)
      Firebase.setString("FB7","0");           // upload value to firebase
   if(sensorValue1 >=30 )
      Firebase.setString("FB7","2");

    
    //******************************************
   int proximity = digitalRead(REED_PIN); // Read the state of the switch
   if(rel2==1)                                // If, the Status is 1, turn on the Relay2
   {
      if (proximity == LOW) // If the pin reads low, the switch is closed.
      {
        Serial.println("Door open");
        Firebase.setString("FB4","2");
   
      }
      else
      {
        Serial.println("Door close");
        Firebase.setString("FB4","0");
      }
   }
   else
   {
        Serial.println("Door close");
        Firebase.setString("FB4","0");
   }
    //******************************************
 
     

}
  
