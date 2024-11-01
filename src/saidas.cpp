#include <Arduino.h>
#include <ESP32Servo.h>
#include "saidas.h"
#include "entradas.h"

// Definição dos pinos dos leds e do servo
#define LED_SINAL_PIN 34    // Pino para o LED

bool estadoLed = false; // Definição e inicialização

// Inicializa as saídas digitais
void inicializa_saidas()
{
  pinMode(LED_SINAL_PIN , OUTPUT);
}

// Atualiza as saídas digitais
void atualiza_saidas()
{
  // Atualiza o estado do umidificador
  if (botao_pressionado())
  {
    digitalWrite(LED_SINAL_PIN , HIGH);

      bool estadoLed = digitalRead(LED_SINAL_PIN);
      Serial.println(estadoLed);
  }
   
  
  else if (botao_solto())
  {
    digitalWrite(LED_SINAL_PIN , LOW);
  }
}
