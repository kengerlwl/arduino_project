#include <FastLED.h>

#define NUM_LEDS 53
#define LED_PIN 6
#define MIC_PIN A0
#define MIC_THRESHOLD 300
#define MAX_BRIGHTNESS 255
#define MOVING_AVERAGE_LENGTH 5

CRGB leds[NUM_LEDS];
int micReadings[MOVING_AVERAGE_LENGTH];
int micReadIndex = 0;
int last_micValue = -1;
int max_down_dis = 1; // 设置每次最大下降mic_value

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(0);
  FastLED.show();
  Serial.begin(9600);

  for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
    micReadings[i] = 0;
  }
}

// 设置每次下降不能超过20
int updateMicValue_by_distance(int mic_value){
  int tmp_vaule = mic_value;
  if(last_micValue - mic_value >= max_down_dis){
    mic_value = last_micValue - max_down_dis;
  }
  last_micValue = tmp_vaule;
  return mic_value;
}

void loop() {
  int micValue = analogRead(MIC_PIN);
  micReadings[micReadIndex] = micValue;
  micReadIndex = (micReadIndex + 1) % MOVING_AVERAGE_LENGTH;

  // 计算指数移动平均值
  int averageMicValue = calculateMovingAverage();

  averageMicValue = updateMicValue_by_distance(averageMicValue);
  if (averageMicValue > MIC_THRESHOLD) {
    visualize_music(averageMicValue);
  }
  //太短了容易出现瞬闪，太长了容易出现捕捉声音不到
  delay(20);
}

int calculateMovingAverage() {
  int sum = 0;

  for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
    sum += micReadings[i];
  }

  return sum / MOVING_AVERAGE_LENGTH;
}

void visualize_music(int micValue) {


  Serial.println(micValue);

  int min_mic = MIC_THRESHOLD + (1023 - MIC_THRESHOLD) * 0.05;
  if(micValue < min_mic){
    micValue = min_mic; // 设置为保底20%
  }


  // 不要设置为理论最大的声音强度，适当小一点。
  int numLedsToLight = map(micValue, MIC_THRESHOLD, 1023 - 300, 0, NUM_LEDS);
  int brightness = map(numLedsToLight, 0, NUM_LEDS, 0, MAX_BRIGHTNESS);
  brightness = MAX_BRIGHTNESS /2;
  FastLED.setBrightness(brightness);

  for (int i = 0; i < numLedsToLight; i++) {
    leds[i] = CRGB::White;
  }

  for (int i = numLedsToLight; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();
}
