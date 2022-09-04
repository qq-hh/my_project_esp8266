#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  EEPROM.begin(4096);
  int  data=123;
  EEPROM.write(5,data);
  EEPROM.commit();

}

void loop() {
int  message =EEPROM.read(5);
 Serial.println(message);
 delay(3000);

}
