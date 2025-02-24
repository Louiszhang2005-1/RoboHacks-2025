#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180


// Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;


// Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;


void setup()
{
    // Adjust PWM frequency for motor control
    TCCR0B = TCCR0B & B11111000 | B00000010;


    // Set up motor pins
    pinMode(enableRightMotor, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);


    pinMode(enableLeftMotor, OUTPUT);
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);


    // Set up IR sensor pins
    pinMode(IR_SENSOR_RIGHT, INPUT);
    pinMode(IR_SENSOR_LEFT, INPUT);


    // Start Serial Monitor for debugging
    Serial.begin(9600);
    Serial.println("begin");


    // Stop motors initially
    rotateMotor(0, 0);
}


void loop()
{
    int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
    int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);


    // Print sensor readings
    Serial.print("Right Sensor: ");
    Serial.print(rightIRSensorValue);
    Serial.print(" | Left Sensor: ");
    Serial.println(leftIRSensorValue);


    // If no sensors detect a black line, go straight
    if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
    {
        Serial.println(" Moving Forward");
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
    // If right sensor detects black line, turn right
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW)
    {
        Serial.println(" Turning Right (Right Sensor Detected Black)");
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    }
    // If left sensor detects black line, turn left
    else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH)
    {
        Serial.println(" Turning Left (Left Sensor Detected Black)");
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
    }
    // If both sensors detect black line, stop
    else
    {
        Serial.println(" Stopping (Both Sensors Detected Black)");
        rotateMotor(0, 0);
    }


    delay(500); // Small delay for stability
}


// Function to control motor speed and direction
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
    // Right motor control
    if (rightMotorSpeed < 0)
    {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
    }
    else if (rightMotorSpeed > 0)
    {
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
    }
    else
    {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, LOW);
    }


    // Left motor control
    if (leftMotorSpeed < 0)
    {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
    }
    else if (leftMotorSpeed > 0)
    {
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
    }
    else
    {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, LOW);
    }
}
