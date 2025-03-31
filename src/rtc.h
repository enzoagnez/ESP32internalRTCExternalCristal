#include "Arduino.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "soc/rtc.h"

struct timeval tv;

int rtcBegin(){
  
  // Configura o RTC para usar o cristal externo de 32.768 kHz
  rtc_clk_slow_freq_set(RTC_SLOW_FREQ_32K_XTAL);
  delay(1000); 
  
  Serial.println("RTC Configurado com cristal externo de 32.768 kHz.");
  
  // Obtém e imprime a frequência do RTC Slow Clock
  rtc_slow_freq_t freq = rtc_clk_slow_freq_get();
  
  switch (freq) {
      case RTC_SLOW_FREQ_RTC: Serial.println("Usando o clock interno RC"); break;
      case RTC_SLOW_FREQ_32K_XTAL: Serial.println("Usando o cristal de 32.768 kHz"); break;
      case RTC_SLOW_FREQ_8MD256: Serial.println("Usando o clock derivado de 8 MHz"); break;
      default: Serial.println("Clock desconhecido"); break;
  }
  
  // Se for a primeira vez rodando (não vindo de deep sleep), inicializa o tempo
  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("Configurando o tempo inicial...");
    tv.tv_sec = 1711868400;  // Defina um timestamp inicial (epoch time)
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);
  }

  return 0;

}

void rtcUpdate(){
  gettimeofday(&tv, NULL);

}