


int pushButton = 2;


void setup() {
  // 以每秒9600位的速度初始化串行通信：
  Serial.begin(9600);//使用Seria库内的begin函数
    
  // 将按钮的引脚作为输入：
  pinMode(pushButton, INPUT);
}

// 这个循环程序永远地一遍又一遍地运行：
void loop() {
  // 读取输入引脚：
  int buttonState = digitalRead(pushButton);
  // 打印出按钮的状态：
  Serial.println(buttonState);//使用Seria库内的println函数
  delay(1);        // 两次读取之间的延迟可确保稳定性
}