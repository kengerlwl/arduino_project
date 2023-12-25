int led_pin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
}


// 注意：LED的阳极（长线）与高电压相连。


// 实现闪烁灯光的功能
void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i<=10000; i++){
    if(i %2 ==0){
      digitalWrite(led_pin, HIGH);
    }
    else{
      digitalWrite(led_pin, LOW);
    }
    
    delay(300);
  }

}
