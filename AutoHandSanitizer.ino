/*
Authors: Hazel Bains, Han Fang
Date of latest update: Dec 12, 2023

This program implements an automatic hand sanitizer.
Measurements are read from an ultrasonic sensor to determine distance from objects.
If objects (particularly a hand) is close, two Servo motors on either side of the sanitizing bottle 
repeatedly pull on and release the nozzle of a hand sanitizer until the object (hand) is withdrawn.
*/

//Import the Servo library
#include <Servo.h>

//Pins 1 and 2 are used for ultrasonic sensor input
#define trigPin 2
#define echoPin 1

//Pin 11 is used to output to the Servo motor on the left side of the sanitizing bottle
#define leftServoPin 11
//Pin 6 is used to output to the Servo motor on the right side of the sanitizing bottle
#define rightServoPin 6

//Initialize the Servo motors on the left and right side of the sanitizing bottle
Servo leftMotor;
Servo rightMotor;

void setup() {
  //Establish the pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Establish the pin modes for the Servo motors
  pinMode(leftServoPin, OUTPUT);
  pinMode(rightServoPin, OUTPUT);

  //Attaches the left servo pin to the left Servo motor, and sets the left motor's initial position to release the nozzle of the sanitizer
  leftMotor.attach(leftServoPin);
  leftMotor.write(0);
  //Attaches the right servo pin to the right Servo motor, and sets the right motor's initial position to release the nozzle of the sanitizer
  rightMotor.attach(rightServoPin);
  rightMotor.write(180);
}

//Loop continuously reads in and determines distance measurements, and the Servo motors alternate pulling and releasing the nozzle of the hand sanitizer when necessary
void loop() {

  //Initialize variables for distance measurements from the ultrasonic sensor
  long duration, distance;

  //Alternate the ultrasonic sensor between high and low to read in measurements
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin,  LOW);

  //Using the measurements, calculate the distance from the sensor to objects in cm
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  //If the distance from the ultrasonic sensor to an object is within 7 cm, the motors will alternate pulling on and releasing the nozzle of the hand sanitizer
  if(distance < 7){
    //Servo motors pull on the nozzle of the hand sanitizer
    leftMotor.write(180);
    rightMotor.write(0);
    delay(500); //Pull for half a second

    //Servo motors release the nozzle of the hand sanitizer
    leftMotor.write(0);
    rightMotor.write(180);
    delay(500); //Release for half a second

    delay(500); //Wait half a second to prevent overheating
  }
  //If the distance from the ultrasonic sensor to an object is not within 7 cm, the motors will stay in a position where the nozzle of the sanitizer is released
  else{
    leftMotor.write(0);
    rightMotor.write(180);
    delay(500); //Keep in the released position for half-second intervals
  }
  
}

