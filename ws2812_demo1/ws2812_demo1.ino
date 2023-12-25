
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    130
uint8_t max_bright = 128;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高


CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
}
void loop() {
  // Red
  for (int i = 0; i <= (NUM_LEDS -1); i++) {
    leds[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(40);
  }

  // Green
  for (int i = 0; i <= (NUM_LEDS -1); i++) {
    leds[i] = CRGB ( 0, 255, 0);
    FastLED.show();
    delay(40);
  }

  //  Blue
  for (int i = 0; i <= (NUM_LEDS -1); i++) {
    leds[i] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(40);
  }

}