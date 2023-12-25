int out_pin = 11;

void setup() {
  pinMode(out_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sound_value = analogRead(A0); // 从模拟引脚A0读取声音传感器的值
  Serial.println(sound_value);

  if (sound_value > 100) { // 根据传感器输出的值来调整阈值
    digitalWrite(out_pin, LOW);
  } else {
    digitalWrite(out_pin, HIGH);
    delay(200);
  }
}
