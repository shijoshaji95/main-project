#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 

void setup() 
{ 
  myservo.attach(D2);  // attaches the servo on GIO2 to the servo object 
} 
 
void loop() 
{ 
  int pos;

                                   // in steps of 1 degree 
    myservo.write(180);              // tell servo to go to position in variable 'pos' 
                         // waits 15ms for the servo to reach the position 
  
} 
