#include <ESP8266WiFi.h>
 
void setup()
{
  Serial.begin(115200);//设置串口波特率为115200
  WiFi.mode(WIFI_STA);//设置WiFi模式为STA，这里要与之后使用的模式相对应
}
 
void loop()
{
  //每隔一秒钟打印一次MAC地址
  Serial.println(WiFi.macAddress());
  delay(100);
}

