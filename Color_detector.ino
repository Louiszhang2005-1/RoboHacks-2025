/*
  Color Sensor Calibration with Color Indication
  color-sensor-calib.ino
  Calibrate RGB Color Sensor output Pulse Widths
  and indicate the dominant color based on sensor readings

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read the pulse widths for each color with delays to stabilize the sensor
  redPW = getRedPW();
  delay(200);
  
  greenPW = getGreenPW();
  delay(200);
  
  bluePW = getBluePW();
  delay(200);
  
  // Print the raw pulse widths
  Serial.print("Red PW = ");
  Serial.print(redPW);
  Serial.print(" - Green PW = ");
  Serial.print(greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(bluePW);
  
  // Determine and print the dominant color.
  // Lower pulse width means higher intensity (more of that color is present)
  if (redPW < greenPW && redPW < bluePW) {
    Serial.println("Dominant Color: Red");
  }
  else if (greenPW < redPW && greenPW < bluePW) {
    Serial.println("Dominant Color: Green");
  }
  else if (bluePW < redPW && bluePW < greenPW) {
    Serial.println("Dominant Color: Blue");
  }
  else {
    Serial.println("Dominant Color: Unknown");
  }
  
  Serial.println(); // extra spacing for clarity
  delay(500);
}

// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Measure and return the pulse width for red
  return pulseIn(sensorOut, LOW);
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Measure and return the pulse width for green
  return pulseIn(sensorOut, LOW);
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Measure and return the pulse width for blue
  return pulseIn(sensorOut, LOW);
}
