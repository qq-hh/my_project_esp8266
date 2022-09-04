#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//udp包最大字节数
#define MAX_PACKETSIZE 1000
WiFiUDP udp;
const char* ssid = "";
const char* password = "";
//udp包缓冲区
char buffUDP[MAX_PACKETSIZE];

void startUDPServer(int port)
{
  Serial.print("StartUDPServer at port:");
  Serial.println(port);
  udp.begin(port);
}
void sendUDP(char *p)
{
  udp.beginPacket(udp.remoteIP(), udp.remotePort());
  udp.write(p);
  udp.endPacket();
}
void doUdpServerTick()
{
  int packetSize = udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = udp.remoteIP();
    for (int i = 0; i < 4; i++) {//允许做多4个UDP客户端连接
      Serial.print(remote[i], DEC);
      if (i < 3) Serial.print(".");
    }
    Serial.print(", port ");
    Serial.println(udp.remotePort());
    memset(buffUDP,0x00,sizeof(buffUDP));
    udp.read(buffUDP, MAX_PACKETSIZE-1);
    udp.flush();
    Serial.println("Recieve:");
    Serial.println(buffUDP);
    sendUDP(buffUDP);//send back
  }
}

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  startUDPServer(80);
}

void loop() {
  doUdpServerTick();
}
      
