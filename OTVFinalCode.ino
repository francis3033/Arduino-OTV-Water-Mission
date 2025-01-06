#include "Enes100.h"
#include <Servo.h>
#define S0 22
#define S1 24
#define S2 26
#define S3 28
#define OUT 30


// Motor Driver Servo
int servoENA = 8;
int servoPowerPin1 = 12;
int servoPowerPin2 = 13;


Servo servo1;
int servoPin = 9;


int R, G, B, depth, salinity, hit, counter, poolDepth, avgColor = 0;
float duration, distance, tdsValue, degree, y, x, theta;


const int waterTrigPinL = 46;
const int waterEchoPinL = 48;


const int navTrigPinL = 50;
const int navEchoPinL = 52;


const int TDS_PIN = A0;


int left_motors_pin1 = 4;
int left_motors_pin2 = 5;
int right_motors_pin1 = 6;
int right_motors_pin2 = 7;


long startTime;


void setup() {
 //Motor Setup
 pinMode(left_motors_pin1, OUTPUT);
 pinMode(left_motors_pin2, OUTPUT);
 pinMode(right_motors_pin1, OUTPUT);
 pinMode(right_motors_pin2, OUTPUT);
 //Motor speed control
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
  //Setting up pins for color sensor
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(OUT, INPUT);


 digitalWrite(S0, HIGH);
 digitalWrite(S1, LOW);
  // Initialize Pins for Servo Power
 pinMode(servoPowerPin1, OUTPUT);
 pinMode(servoPowerPin2, OUTPUT);
 pinMode(servoENA, OUTPUT);
 // Turn Servo On
 digitalWrite(servoPowerPin1, HIGH);
 digitalWrite(servoPowerPin2, LOW);
 // Reset Servo
 servo1.attach(9);
 servo1.write(175);
 delay(500);
 servo1.detach();
 // Turn Servo Off again
 digitalWrite(servoPowerPin1, LOW);
 digitalWrite(servoPowerPin2, LOW);
 // Initialize ultrasonic sensor
 pinMode(navTrigPinL, OUTPUT);
 pinMode(navEchoPinL, INPUT);
 Serial.begin(9600);


 // Initialize Enes100 Library
 // Team Name, Mission Type, Marker ID, Wifi Module TX Pin, Wifi Module RX Pin
 Enes100.begin("Keep It Clean", WATER, 600, 11, 10);
 delay(2000);
 //At this point we know we are connected.
 Enes100.println("Connected...");
}


float radianConvert(float radians) {
 if (radians >= 0) {
   degree = (radians * 180.0) / 3.1416;
   return degree;
 } else {
   degree = 360.0 + ((radians * 180.0) / 3.1416);
   return degree;
 }
}


void stop() {
 digitalWrite(left_motors_pin1, LOW);
 digitalWrite(left_motors_pin2, LOW);
 digitalWrite(right_motors_pin1, LOW);
 digitalWrite(right_motors_pin2, LOW);
}


void moveForward() {
 analogWrite(2, 255);
 analogWrite(3, 255);
 digitalWrite(left_motors_pin1, HIGH);
 digitalWrite(left_motors_pin2, LOW);
 digitalWrite(right_motors_pin1, LOW);
 digitalWrite(right_motors_pin2, HIGH);
}


void moveBackward() {
 analogWrite(2, 255);
 analogWrite(3, 255);
 digitalWrite(left_motors_pin1, LOW);
 digitalWrite(left_motors_pin2, HIGH);
 digitalWrite(right_motors_pin1, HIGH);
 digitalWrite(right_motors_pin2, LOW);
}


void turnRight() {
 analogWrite(2, 60);
 analogWrite(3, 60);
 digitalWrite(left_motors_pin1, LOW);
 digitalWrite(left_motors_pin2, HIGH);
 digitalWrite(right_motors_pin1, LOW);
 digitalWrite(right_motors_pin2, HIGH);
}


void turnLeft() {
 analogWrite(2, 60);
 analogWrite(3, 60);
 digitalWrite(left_motors_pin1, HIGH);
 digitalWrite(left_motors_pin2, LOW);
 digitalWrite(right_motors_pin1, HIGH);
 digitalWrite(right_motors_pin2, LOW);
}


void servoOn() {
 analogWrite(servoENA, 255);
 digitalWrite(servoPowerPin1, HIGH);
 digitalWrite(servoPowerPin2, LOW);
}


void servoOff() {
 digitalWrite(servoPowerPin1, LOW);
 digitalWrite(servoPowerPin2, LOW);
}


void posXForward(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.x < coord) {
     moveForward();
   Enes100.updateLocation();
 }
 stop();
}


void posYForward(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.y < coord) {
     moveForward();
   Enes100.updateLocation();
 }
 stop();
}


void negXForward(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.x > coord) {
     moveForward();
   Enes100.updateLocation();
 }
 stop();
}


void negYForward(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.y > coord) {
     moveForward();
   Enes100.updateLocation();
 }
 stop();
}


void negYBackwards(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.y > coord) {
     moveBackward();
   Enes100.updateLocation();
 }
 stop();
}


void posYBackwards(float coord) {
 Enes100.updateLocation();
 while (Enes100.location.y < coord) {
     moveBackward();
   Enes100.updateLocation();
 }
 stop();
}


void ninety() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) < (87)) || ((radianConvert(Enes100.location.theta)) > (91))) {
     turnLeft();
   Enes100.updateLocation();
 }
 stop();
}


void oneeighty() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) < (177))||((radianConvert(Enes100.location.theta)) > (181))) {
     turnLeft();
   Enes100.updateLocation();
 }
 stop();
}


void twoseventyRight() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) < (269))||((radianConvert(Enes100.location.theta)) > (273))) {
     turnRight();
   Enes100.updateLocation();
 }
 stop();
}


void twoseventy() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) < (269))||((radianConvert(Enes100.location.theta)) > (273))) {
     turnLeft();
   Enes100.updateLocation();
 }
 stop();
}


void zeroRight() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) > (6)) || ((radianConvert(Enes100.location.theta)) < (2))) {
     turnRight();
   Enes100.updateLocation();
 }
 stop();
}


void zero() {
 Enes100.updateLocation();
 while (((radianConvert(Enes100.location.theta)) > (6)) || ((radianConvert(Enes100.location.theta)) < (2))) {
     turnLeft();
   Enes100.updateLocation();
 }
 stop();
}


void readings(int color, float salinityLevel, int depth) {
 // If Polluted Water
 if (color > 35) {
   // If Salty Water --> Polluted
   if (salinityLevel > 750) {
     Enes100.mission(WATER_TYPE, SALT_POLLUTED);
     // If Fresh Water --> Polluted
   } else {
     Enes100.mission(WATER_TYPE, FRESH_POLLUTED);
   }
   // Not Polluted Water
 } else {
   // If Salty Water --> Not Polluted
   if (salinityLevel > 750) {
     Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
     // If Fresh Water --> Not Polluted
   } else {
     Enes100.mission(WATER_TYPE, FRESH_UNPOLLUTED);
   }
 }
 // Transmit the depth of the pool in mm (20, 30, or 40)
 if (depth < 25) {
   Enes100.mission(DEPTH, 20);
 } else if (depth < 35 && depth >= 25) {
   Enes100.mission(DEPTH, 30);
 } else {
   Enes100.mission(DEPTH, 40);
 }
}


//Change 0 to the value of no water
int waterLevelFunc() {
 int waterLevel = int(108.0 - ultrasonicWater(waterTrigPinL, waterEchoPinL));
 return waterLevel;
}


float ultrasonicWater(int trigPin, int echoPin) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = 10 * (((duration)*0.0343) / 2);
 return distance;
}


float ultrasonic(int trigPin, int echoPin) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = ((duration)*0.0343) / 2;
 return distance;
}


int testColor() {
 digitalWrite(S2, LOW);
 digitalWrite(S3, LOW);
 R = pulseIn(OUT, LOW);
 delay(10);


 digitalWrite(S2, HIGH);
 digitalWrite(S3, HIGH);
 G = pulseIn(OUT, LOW);
 delay(10);


 digitalWrite(S2, LOW);
 digitalWrite(S3, HIGH);
 B = pulseIn(OUT, LOW);
 delay(10);


 avgColor = (R + G + B) / 3;
 return avgColor;
}


float testSalinity() {
 tdsValue = analogRead(TDS_PIN);
 float voltage = tdsValue * (5.0 / 1023.0);
 tdsValue = (voltage - 0.5) * 1000;
 if (tdsValue > 750) {  // This threshold for "salty" is just an example, adjust based on your needs
   Enes100.println("SALTY");
 } else {
   Enes100.println("FRESHWATER");
 }
 return tdsValue;
}


void startingNav() {
 Enes100.updateLocation();
 // We start at location B
 if (Enes100.location.y < 1) {
   ninety();
   posYForward(1.25);
   // We start at location A
 } else {
   twoseventy();
   negYForward(0.75);
 }
}


void lowerServo() {
 servo1.write(52);
 delay(2200);
}


void raiseServo() {
 servo1.write(175);
 delay(1800);
}


void loop() {
 // START MISSION
 if (counter < 1) {
   // Starting at A or B and go to the mission site
   startingNav();
   // After getting to the mission, delay for 4 sec for water level
   stop();
   delay(8000);
   poolDepth = waterLevelFunc();
   delay(4000);


   // After getting to the mission site lower the pump in the water
   servoOn();
   servo1.attach(9);
   lowerServo();
   int G = testColor();
   float salinity = testSalinity();
   raiseServo();
   // Detach servo after raising it back up
   servo1.detach();
   servoOff();


   //Activate color sensor and record value
   readings(G, salinity, poolDepth);
   delay(3000);


   // Course navigation after water mission
   // Move Backwards after mission
   Enes100.updateLocation();
   if (Enes100.location.y > 1) {
   negYBackwards(1);
   zeroRight();
   } else {
   posYBackwards(1.05);
   zero();
   }


   // Turn to move forwards
   posXForward(0.75);
   stop();
   delay(2000);
   distance = ultrasonic(navTrigPinL, navEchoPinL);
   // First Obstacle
   // If there's an obstacle
   if (distance < 40) {
     ninety();
     posYForward(1.5);
     zeroRight();
     posXForward(1.7);
     stop();
     delay(2000);
     distance = ultrasonic(navTrigPinL, navEchoPinL);
     // Checking Second Obstacle if there's a first obstacle
     if (distance < 40) {
       stop();
       delay(2000);
       twoseventyRight();
       negYForward(1.2);
       zero();
       posXForward(2.7);
       twoseventyRight();
       negYForward(0.5);
       zero();
       // IF No second obstacle
     } else {       
       posXForward(2.7);
       twoseventyRight();
       negYForward(0.5);
       zero();
       }       
       // IF NO First Obstacle
   } else {
     posXForward(1.7);
     stop();
     delay(2000);
     distance = ultrasonic(navTrigPinL, navEchoPinL);
     // Checking for second obstacle after no first
     // IF There's a secodn obstacle after no first
     if (distance < 40) {
       stop();
       delay(2000);
       twoseventyRight();
       negYForward(0.5);
       zero();
       posXForward(2.7);
       // No first and no second obstacle
     } else {
       posXForward(2.7);
       twoseventyRight();
       negYForward(0.5);
       zero();
     }
   }
   posXForward(3.75);
   stop();
   delay(5000);
 }
 counter += 1;
}

