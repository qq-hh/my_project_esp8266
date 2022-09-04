#include <ESP8266WiFi.h>
#include <espnow.h>

int r = 4;
int g = 5;
int y = 2;
typedef struct struct_message {
  int a;
  String d;
} struct_message;

//创建结构体变量
struct_message myData;

//创建一个回调函数作为接收数据后的串口显示
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.println(myData.a);
  //接收数据亮灯关灯
      if(myData.a ==0){
        Serial.println("122");
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(2, 0);
    }
    if(myData.a != NULL){
       digitalWrite(myData.a, 1);
       delay(2000);
    }

}
void setup() {
  //初始化窗口
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  //设置ESP8266模式
  WiFi.mode(WIFI_STA);
  //初始化 ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //设置ESP8266角色：
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //先前创建的功能 测试ESP-NOW通信
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {


}
