# Wireless-serial-port
Based on esp8266_ Now's wireless serial port
需要制作的时候，需要去代码里面修改esp8266模块的MAC地址

连接MCU的ESP8266，需要依照协议发送。
帧头：0X81
帧尾：0X7E
中间数据最多为100位。

更新时间：2023.3.3