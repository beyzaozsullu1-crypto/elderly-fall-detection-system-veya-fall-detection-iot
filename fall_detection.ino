#include <Wire.h>
#include <MPU6050.h> // 6-axis Accelerometer & Gyroscope library

MPU6050 mpu;
const int buzzerPin = 8;
const float FALL_THRESHOLD = 2.5; // Trigger threshold for sudden impact (G-force)

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(buzzerPin, OUTPUT);
  
  if (mpu.testConnection()) {
    Serial.println("Sensor connection successful.");
  } else {
    Serial.println("Sensor connection failed!");
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate total acceleration magnitude (G-force)
  float gForce = sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2)) / 16384.0;

  // Check if the force exceeds the fall threshold
  if (gForce > FALL_THRESHOLD) {
    Serial.println("EMERGENCY ALERT: Fall Detected!");
    digitalWrite(buzzerPin, HIGH); // Trigger the alarm
    delay(5000); // Keep alarm on for 5 seconds
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  
  delay(100); // Read sensor data every 100ms
}
