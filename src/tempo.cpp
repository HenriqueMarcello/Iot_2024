#include <WiFiUdp.h>
#include <NTPClient.h> // Consultar a hora no servidor
#include <TimeLib.h>   // Formatar a hora
#include "tempo.h"

// Fuso horário de Brasília GMT-3
const int fusoHorario = -10800;

// Atualiza o servidor NTP a cada 60 segundos
const unsigned long atualizaNTP = 60000; // em milissegundos

// Configuração do servidor NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", fusoHorario, atualizaNTP);

// Retorna a hora atual no formato dd/mm/aaaa hh:mm:ss
void hora_certa()
{
  unsigned long epochTime = timeClient.getEpochTime();
  setTime(epochTime);
  Serial.printf("%02d/%02d/%04d", day(), month(), year());
  Serial.printf(" %02d:%02d:%02d \n", hour(), minute(), second());
}

// Retorna tempo no formato POSIX
unsigned long timeStamp()
{
  return timeClient.getEpochTime();
}

// Configura o servidor NTP
void setup_time()
{
  timeClient.begin();
}

// Atualiza o servidor NTP
void atualiza_time()
{
  timeClient.update();
}