
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
// #if (SSD1306_LCDHEIGHT != 64)
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
// #endif
 
int nFrames = 36;
 
void setup()   {                
  Serial.begin(9600);
 
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 
  display.display();
  delay(1000);
 
  display.clearDisplay();
}
 
 
void loop() {
  for (int frame=0; frame < nFrames; frame++)
  {
    HariChord(frame);
  }
 
  for (int frame=(nFrames-1); frame >= 0; frame--)
  {
    HariChord(frame);
  }
}
 
void HariChord(int frame)
{
  display.clearDisplay();
  int n = 7;
  int r = frame * 64 / nFrames;
  float rot = frame * 2*PI / nFrames;
  for (int i=0; i<(n-1); i++)
  {
    float a = rot + i * 2*PI / n;
    int x1 = 64 + cos(a) * r;
    int y1 = 32 + sin(a) * r;
    for (int j=i+1; j<n; j++)
    {
      a = rot + j * 2*PI / n;
      int x2 = 64 + cos(a) * r;
      int y2 = 32 + sin(a) * r;
      display.drawLine(x1,y1, x2,y2, WHITE);
    }
  }
  display.display();
}