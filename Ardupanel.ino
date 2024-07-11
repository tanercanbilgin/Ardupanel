#define ldr_up A0
#define ldr_down A1
#define panel_servo 11
#include <Servo.h>

Servo Panel;
int min_angle = 0;
int max_angle = 180;

void setup() {
  Serial.begin(9600);
  Panel.attach(panel_servo);
  Panel.write(90); // Start at 90 degrees (middle position)
}

void loop() {
  int level_up = analogRead(ldr_up);
  int level_down = analogRead(ldr_down);

  // Calculate the difference between LDR readings
  int difference = level_up - level_down;

  // Map the difference to an angle around the center (90 degrees)
  int angle = map(difference, -512, 512, min_angle, max_angle);

  // Constrain the calculated angle within the defined range
  angle = constrain(angle, min_angle, max_angle);

  Serial.print("Level Up: ");
  Serial.print(level_up);
  Serial.print(" Level Down: ");
  Serial.print(level_down);
  Serial.print(" Difference: ");
  Serial.print(difference);
  Serial.print(" Mapped Angle: ");
  Serial.println(angle);

  // Set the servo position based on the constrained angle
  Panel.write(angle);

  delay(100); // Adjust delay as needed for your application
}
