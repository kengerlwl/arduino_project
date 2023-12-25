const int buzzerPin=2;//定义D7引脚为蜂鸣器信号输出引脚
void setup() 
{
  pinMode(buzzerPin,OUTPUT);//端口定义
}

void loop() 
{
  for(int i=200;i<=800;i++)//频率不断上升
  {
    tone(buzzerPin,i);
    delay(5);
  }
  delay(4000);//保持频率最高的点延迟4秒
  for(int i=800;i>=200;i--)//频率在不断下降
  {
    tone(buzzerPin,i);
    delay(10);
  }
}