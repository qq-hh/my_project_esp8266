#include <ESP8266WiFi.h>
#include <espnow.h>
//对方MAC地址
uint8_t broadcastAddress[] = {0x30, 0x83, 0x98, 0xB1, 0xD1, 0x93};

typedef struct struct_message {
  int a;
  String d;
} struct_message;

//创建一个新的类型变量
struct_message myData;
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");//将消息是否发送成功打印出来
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

void setup() {
  //初始化串行监视器以进行调试
  Serial.begin(115200);

  //将设备设置为Wi-Fi站点
  WiFi.mode(WIFI_STA);

  //立即初始化ESP
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  //先前创建的功能。
  esp_now_register_send_cb(OnDataSent);

  //与另一个ESP-NOW设备配对以发送数据
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  //配置要发送的值
  myData.a = 4;
  //发送消息
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //延时两秒
  delay(3000);
   myData.a = 5;
  //发送消息
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //延时两秒
  delay(3000);
   myData.a = 2;
  //发送消息
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //延时两秒
  delay(3000);
  myData.a = 0;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
}
