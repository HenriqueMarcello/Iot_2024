#include <WiFiUdp.h>
#include <NTPClient.h> // Consultar a hora no servidor
#include <TimeLib.h>   // Formatar a hora
#include "tempo.h"

const int fusoHorario = -10800;
const unsigned long atualizaNTP = 60000; // em milissegundos

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", fusoHorario, atualizaNTP);


void hora_certa()
{
  unsigned long epochTime = timeClient.getEpochTime();
  setTime(epochTime);
  Serial.printf("%02d/%02d/%04d", day(), month(), year());
  Serial.printf(" %02d:%02d:%02d \n", hour(), minute(), second());
}

unsigned long timeStamp()
{
  return timeClient.getEpochTime();
}

void setup_time()
{
  timeClient.begin();
}

void atualiza_time()
{
  timeClient.update();
}
