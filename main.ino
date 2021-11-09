#include <AFMotor.h>

  //declare order from hc into variable
int state =0;

  //define the motors
AF_DCMotor topMotor(1);
AF_DCMotor rightMotor(2);
AF_DCMotor leftMotor(3);



///////////////////////////////////////////////////////////////////////////
int sensor = 26;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rps=0;
/////////////////////////////////////////////////////////////////////////////

#include <NewPing.h>

#define TRIGGER_PIN  22  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     24  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() 
{
  Serial.begin(9600);
  pinMode(sensor,INPUT_PULLUP);
  Serial.println(" STEPS - 0");
  Serial.println(" RPS   - 0.00");

///////////////////////////////////////////////////////////////////////////////
  topMotor.setSpeed(150); // 250 rpm 
  topMotor.run(RELEASE);
  rightMotor.setSpeed(150);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(150);
  leftMotor.run(RELEASE);
}
 
void loop()
{
  if(Serial.available()>0)
{
  state=Serial.read();
    Serial.println(state);

}
 if(state == 48) {
  topMotor.run(RELEASE) ;
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);
}

  //Forward state
 
if (state == 51){
  topMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

  //Backward state
if(state == 52){
  topMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
}

  //Right state
if(state == 50) {
  topMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  leftMotor.run(FORWARD);
}

  //Left state 
  if(state == 49) {
  topMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  leftMotor.run(BACKWARD);
}
///////////////////////////////////////////////////////////////////////////////
 start_time=millis();
 end_time=start_time+1000;
 while(millis()<end_time)
 {
   if(digitalRead(sensor))
   {
    steps=steps+1; 
    while(digitalRead(sensor));
   }if (sonar.ping_cm() <= 10){ 
    Serial.print (" i found smth after " );
    Serial.println(steps);
   Serial.println("   ");
    break;

 } }
 }
