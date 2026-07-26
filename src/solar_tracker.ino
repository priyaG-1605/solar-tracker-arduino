#include <Servo.h>

Servo myServo;

// LDR pins
const int ldrLeft = A0;
const int ldrRight = A1;

const int servoPin = 9;
int pos = 90; // Start at center position (90°)
const int threshold = 50; // Sensitivity threshold

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(pos);
  delay(500);
}

void loop() {
  int leftValue = analogRead(ldrLeft);
  int rightValue = analogRead(ldrRight);

  int difference = leftValue - rightValue;

  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" | Right: ");
  Serial.print(rightValue);
  Serial.print(" | Diff: ");
  Serial.println(difference);

  // Adjust position based on light intensity difference
  if (difference > threshold) {
    if (pos < 180) pos++; // Move toward left LDR
  } 
  else if (difference < -threshold) {
    if (pos > 0) pos--;   // Move toward right LDR
  }

  pos = constrain(pos, 0, 180);
  myServo.write(pos);

  delay(50); // Reduced delay for smoother motor response
}
