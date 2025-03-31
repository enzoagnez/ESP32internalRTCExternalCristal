#include "Arduino.h"
#include "rtc.h"


void setup() {
  Serial.begin(115200);

  rtcBegin(); //inicia RTC preferencialmente no modo cristal externo

}

void loop() {
  rtcUpdate();  //atualiza a struct timeval
  Serial.printf("Tempo atual do RTC: %ld segundos desde 1º Jan 1970\n", tv.tv_sec);
  delay(1000);
}
