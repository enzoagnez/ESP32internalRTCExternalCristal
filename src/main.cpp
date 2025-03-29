#include"Arduino.h"
#include <Wire.h>
#include "time.h"

// Prototipação das funções
void setManualTime(int year, int month, int day, int hour, int minute, int second);
void printLocalTime();

int year = 2024;
int month = 9;
int day = 10;
int hour = 12;
int minute = 30;
int second = 0;

void setup() {
  Serial.begin(115200);
  
  // Configura a hora manualmente
  setManualTime(year, month, day, hour, minute, second);
  
  // Exibe a hora atual
  printLocalTime();
}

void loop() {
  // Exibe a hora atual a cada 10 segundos
  delay(10000);
  printLocalTime();
}

// Função para configurar a hora manualmente
void setManualTime(int year, int month, int day, int hour, int minute, int second) {
  struct tm t;
  
  // Configura o horário manualmente com os valores fornecidos
  t.tm_year = year - 1900;  // tm_year conta a partir de 1900
  t.tm_mon = month - 1;     // tm_mon é de 0 a 11, então subtrai 1
  t.tm_mday = day;
  t.tm_hour = hour;
  t.tm_min = minute;
  t.tm_sec = second;

  // Converte a estrutura tm para o formato de tempo do sistema (epoch time)
  time_t t_of_day = mktime(&t);

  // Define o tempo do sistema
  struct timeval now = { .tv_sec = t_of_day };
  settimeofday(&now, NULL);
}

// Função para exibir a hora local no formato legível
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter a hora");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
