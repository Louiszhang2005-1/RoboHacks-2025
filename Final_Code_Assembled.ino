#include <Servo.h>

// --- Servo Motor Variables ---
Servo seedDispenser;
int count = 0;

// --- DC Motor Variables ---
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;
int enable1 = 6;
int enable2 = 7;

// --- Color Detector Variables ---
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// --- Black Line Detection Variables ---
#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180
int enableRightMotor = 6;
int rightMotorPin1 = 2;
int rightMotorPin2 = 3;
int enableLeftMotor = 7;
int leftMotorPin1 = 4;
int leftMotorPin2 = 5;

// --- Setup for Servo, DC Motors, and Color Detection ---
void setup() {
  // Setup Servo Motor
  seedDispenser.attach(12);

  // Setup DC Motors
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  // Setup Color Detection Pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setup IR Sensors
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);  // Set pulse width scaling to 20%
}

void loop()
{
    int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
    int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

    // Read color sensor values (red, green, blue)
    redPW = getRedPW();
    delay(200);
    greenPW = getGreenPW();
    delay(200);
    bluePW = getBluePW();
    delay(200);

    // Print color readings for debugging
    Serial.print("Red PW = ");
    Serial.print(redPW);
    Serial.print(" - Green PW = ");
    Serial.print(greenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(bluePW);

    // Set up initial motor speed
    int motorSpeedLeft = MOTOR_SPEED;
    int motorSpeedRight = MOTOR_SPEED;

    // Add offsets based on certain conditions or sensors
    int offset = 20;  // Adjust this value to change the offset

    // Color-based decision-making
    if (redPW < greenPW && redPW < bluePW) {
        // If Red is the dominant color
        Serial.println("Dominant Color: Red");
        // Continue forward without any special action
    } 
    else if (greenPW < redPW && greenPW < bluePW) {
        // If Green is the dominant color
        Serial.println("Dominant Color: Green");
        // Stop the motors and activate the seed dispenser (servo motor)
        stopMotors();
        // Add code to run Servo_Motor code here, i.e. activate seed dispenser
        operateSeedDispenser(); // Example of triggering the servo
        
  
    } 
    else if (bluePW < redPW && bluePW < greenPW) {
        // If Blue is the dominant color
        Serial.println("Dominant Color: Blue");
        // Stop the motors and activate the seed dispenser (servo motor)
        stopMotors();
        // Add code to run Servo_Motor code here, i.e. activate seed dispenser
        operateSeedDispenser();
        
    }

    // If both IR sensors do not detect a black line, go straight
    if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
        Serial.println("Moving Forward");
        motorSpeedLeft += offset;  // Speed up the left motor
        motorSpeedRight -= offset; // Slow down the right motor
    } 
    // If the right sensor detects a black line, turn right
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
        Serial.println("Turning Right (Right Sensor Detected Black)");
        motorSpeedLeft -= offset;  // Slow down the left motor
        motorSpeedRight += offset; // Speed up the right motor
    }
    // If the left sensor detects a black line, turn left
    else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
        Serial.println("Turning Left (Left Sensor Detected Black)");
        motorSpeedLeft += offset;  // Speed up the left motor
        motorSpeedRight -= offset; // Slow down the right motor
    } 
    // If both sensors detect a black line, stop
    else {
        Serial.println("Stopping (Both Sensors Detected Black)");
        motorSpeedLeft = 0;
        motorSpeedRight = 0;
    }

    // Call the rotateMotor function with adjusted speeds
    rotateMotor(motorSpeedRight, motorSpeedLeft);

    delay(500); // Small delay for stability
}

// Function to stop both motors
void stopMotors() {
    rotateMotor(0, 0);  // Set both motor speeds to 0, effectively stopping them
}


// Function to operate the seed dispenser (servo motor)
void operateSeedDispenser() {
  int count = 0;
  while (count < 2) {
    int pos;
    for (pos = 0; pos <= 120; pos++) {
      seedDispenser.write(pos);
      delay(10);
    }

    for (pos = 120; pos >= 0; pos--) {
      seedDispenser.write(pos);
      delay(10);
    }

    count++;
  }
}

// Function to read the Red Pulse Width
int getRedPW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  return pulseIn(sensorOut, LOW);
}

// Function to read the Green Pulse Width
int getGreenPW() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}

// Function to read the Blue Pulse Width
int getBluePW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW);
}

// Function to control motor speed and direction
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
    // Add an offset to the right and left motor speeds
    int rightSpeedWithOffset = rightMotorSpeed;
    int leftSpeedWithOffset = leftMotorSpeed;

    // Example of adding a fixed offset (you can change this value to control the amount of offset)
    int offset = 20; // Change this value to adjust the speed difference between the motors
    rightSpeedWithOffset += offset;  // Right motor faster
    // leftSpeedWithOffset -= offset;  // Uncomment to make left motor slower

    // Right motor control
    if (rightSpeedWithOffset < 0) {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
    } else if (rightSpeedWithOffset > 0) {
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
    } else {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, LOW);
    }

    // Left motor control
    if (leftSpeedWithOffset < 0) {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
    } else if (leftSpeedWithOffset > 0) {
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
    } else {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, LOW);
    } 
}