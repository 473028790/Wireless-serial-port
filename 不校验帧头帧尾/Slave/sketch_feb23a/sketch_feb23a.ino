#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t esp_HAVE_address[] = {0xAC, 0x0B, 0xFB, 0xE5, 0xD3, 0x97};
uint8_t esp_NO_address[] = {0xE8, 0x68, 0xE7, 0xCA, 0xD3, 0xC2};

//接收信息时的回调函数，每次接收信息会自动调用该函数
uint8_t data_rc[50];
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) 
{
    memcpy(&data_rc, incomingData, sizeof(data_rc));  
     for(int i=0;i<len;i++)
     {
            Serial.write(data_rc[i]);
      }
}

void setup() {
  Serial.begin(115200);//初始化串口，设置其波特率为115200
  WiFi.mode(WIFI_STA);//设置WIFI模式为STA
  WiFi.disconnect();//断开WIFI连接
  
  // Init ESP-NOW
  esp_now_init();
  
  //双向通信时需要设定角色为 ESP_NOW_ROLE_COMBO
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  
  //与模块配对
  esp_now_add_peer(esp_NO_address, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  //执行完这个函数，每次接收数据就会自动调用回调函数了
  esp_now_register_recv_cb(OnDataRecv);
}

uint8_t data_to_send ;
uint8_t data[1];
void loop() 
{
    if (Serial.available() > 0) {
        data[0]= Serial.read();
        esp_now_send(esp_NO_address, data, 1);
        }

  }
  


