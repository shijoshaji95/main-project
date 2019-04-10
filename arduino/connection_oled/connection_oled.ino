#include <ESP8266WiFi.h>                                   //
#include <FirebaseArduino.h>                              //

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define FIREBASE_HOST "home-automation-c6c30.firebaseio.com"      //
#define FIREBASE_AUTH "7TpxFfHBlUes1nSDNBsY41QrqUt9OzDCnPmBMMDI"   // 
#define WIFI_SSID "Shijo"                                           //    
#define WIFI_PASSWORD "12345679"                                     // 



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  Wire.begin(D3,D4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

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
   int rel1;
   rel1=Firebase.getString("FB0").toInt();    //Reading the value of the varialble Status from the firebase
   Serial.println(rel1);
   


  
  
  display.display();
  delay(1000);

   if(rel1==0)                                // If, the Status is 1, turn on the Relay1
     {

   display.clearDisplay();
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.println(F("AC OFF "));
   display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(500);
      
     }
   else                                  // If, the Status is 0, turn Off the Relay1
     {                                      

    display.clearDisplay();
  display.setTextSize(1.5); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.println(F("AC ON "));
  display.println(F(" "));
  display.print(F("Temp : "));
  display.println(rel1);
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(500);
  
      
     }


 

  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);

 
}
