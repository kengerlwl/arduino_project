#define BLINKER_BLE
#include <FastLED.h>
#include <BlinkerSimpleSerialBLE.h>
#include <SoftwareSerial.h>
#include <Blinker.h>

#define NUM_LEDS 53
#define LED_PIN 6
#define MIC_PIN A0
#define MIC_THRESHOLD 300
#define MAX_BRIGHTNESS 100
#define MOVING_AVERAGE_LENGTH 5

CRGB leds[NUM_LEDS];
CRGB LEDColor = CRGB::White; // LED颜色全局变量
uint8_t Bright = MAX_BRIGHTNESS;

int micReadings[MOVING_AVERAGE_LENGTH];
int micReadIndex = 0;
int last_micValue = -1;
int max_down_dis = 1;

BlinkerRGB RGB1("RGBKey");
BlinkerText Text1("Min_Mic");

/*
目前音乐调节还不灵敏
一个调节音乐灵敏度的办法，将灯条的理论最大值设置多一点。实际并没有这么多灯。就可以变得看上去更加灵敏

*/


void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(0);
  FastLED.show();
  Serial.begin(9600);

  Blinker.begin(4, 5);
    // Blinker.attachData(dataRead);

  RGB1.attach(rgb1_callback);  // 回调函数 
 


  for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
    micReadings[i] = 0;
  }
}

void loop() {
  Blinker.run();
  //设置减去的值
  int micValue = analogRead(MIC_PIN) - 100;
  // Serial.println(micValue);
  micReadings[micReadIndex] = micValue;
  micReadIndex = (micReadIndex + 1) % MOVING_AVERAGE_LENGTH;

  int averageMicValue = calculateMovingAverage();
  averageMicValue = updateMicValueByDistance(averageMicValue);

  if (averageMicValue > MIC_THRESHOLD) {
    visualize_music(averageMicValue);
  }

  delay(10);
}









int calculateMovingAverage() {
  int sum = 0;
  for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
    sum += micReadings[i];
  }
  return sum / MOVING_AVERAGE_LENGTH;
}

void visualize_music(int micValue) {
  int min_mic = MIC_THRESHOLD + (1023 - MIC_THRESHOLD) * 0.05;
  micValue = max(micValue, min_mic);

  //乘以一个系数，让这个对声音更加敏感
  int numLedsToLight = map(micValue, MIC_THRESHOLD, 1023 - 300, 0, int(NUM_LEDS*1.5));
  
  if(numLedsToLight >= NUM_LEDS){
    numLedsToLight = NUM_LEDS-1;
  }
  Serial.print("the numLedsToLight is ");
  Serial.println(numLedsToLight);
  int brightness = map(numLedsToLight, 0, NUM_LEDS, 0, Bright);
  // Serial.print("the bright is ");
  // Serial.println(Bright);

  FastLED.setBrightness(brightness);


  for (int i = 0; i < numLedsToLight; i++) {
    leds[i] = LEDColor;
  }
  for (int i = numLedsToLight; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();
}

int updateMicValueByDistance(int mic_value) {
  if (last_micValue - mic_value > max_down_dis) {
    mic_value = last_micValue - max_down_dis;
  }
  last_micValue = mic_value;
  return mic_value;
}

void rgb1_callback(uint8_t r_value, uint8_t g_value, uint8_t b_value, uint8_t bright_value) {
  Serial.print("CALLBACK");
  Serial.println(bright_value);
  LEDColor = CRGB(r_value, g_value, b_value);
  Bright = bright_value;
  fill_solid(leds, NUM_LEDS, LEDColor);

  FastLED.show();
}
