#include <Wire.h>

// 0x27 is the I2C address. This address might be different.
const int IN_A0 = A0; // analog input
const int IN_D0 = 8; // digital input
void setup() {
  pinMode (IN_A0, INPUT);
  pinMode (IN_D0, INPUT);
  Serial.begin(9600);
}
int value_A0;
bool value_D0;
void loop() {
  value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
  value_D0 = digitalRead(IN_D0);// reads the digital input from the IR distance sensor
  
  Serial.println("\n now is :");
  Serial.println(value_A0);
  Serial.println(value_D0);
  delay(1000);
}