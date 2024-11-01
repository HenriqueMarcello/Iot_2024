#include <Arduino.h>
#include <Bounce2.h>
#include <entradas.h>
#include <saidas.h>
#include <umidificador.h>
#include <ArduinoJson.h>

#define UMIDIFICADOR_PIN 27 // Pino de controle do umidificador (comando)

bool umidificadorLigado = 0; // Estado inicial do umidificador

bool travaPulso = 0;

unsigned long tempoAnteriorUmidificador = 0;
int nivelUmidificador = 0;

void setupUmidificador()
{
  Serial.begin(9600);
  pinMode(UMIDIFICADOR_PIN, OUTPUT);
  // Inicialmente, desliga o umidificador e o LED
  digitalWrite(UMIDIFICADOR_PIN, LOW);
}

void loopUmidificador()
{
  int valor = analogRead(LED_SINAL_PIN);
  valor > 3000 ? umidificadorLigado = 1 : umidificadorLigado = 0;

  if (travaPulso) // Se o pino do umidificador estiver em nivel logido baixo
  {
    if (millis() - tempoAnteriorUmidificador > 50) // se está a mais de ms em nivel lógico baixo
    {
      travaPulso = 0;
      digitalWrite(UMIDIFICADOR_PIN, HIGH); // deixar o umidificador em nivel lógico alto
    }
  }
}

int pulsoUmidificador()
{
  if (!travaPulso)
  {
    travaPulso = 1;
    digitalWrite(UMIDIFICADOR_PIN, LOW);  // Desliga o umidificador
    tempoAnteriorUmidificador = millis(); // Salva o tempo atual
    if (nivelUmidificador < 3)
      nivelUmidificador++;
    else
    {
      nivelUmidificador = 0;
      if (umidificadorLigado)
        desligaUmidificador();
    }
  }
  return nivelUmidificador;
}

void desligaUmidificador()
{
  nivelUmidificador = 0;
  for (int x = 0; x < 3; x++)
  {
    if (analogRead(LED_SINAL_PIN) > 3000)
    {
      digitalWrite(UMIDIFICADOR_PIN, LOW);
      delay(50);
      digitalWrite(UMIDIFICADOR_PIN, HIGH);
      delay(50);
    }
  }
}

