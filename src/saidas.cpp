#include <Arduino.h>
#include <ArduinoJson.h>
#include <time.h>
#include "saidas.h"

#define LedBuiltInPin 15  // Pino do LED integrado
#define BOOTPIN 0        // Pino do botão BOOT do ESP32

#define SCREEN_WIDTH 128  // Largura do display OLED
#define SCREEN_HEIGHT 64  // Altura do display OLED
#define OLED_RESET -1     

bool LedBuiltInState = LOW;

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 1000;

void inicializa_saidas()
{
    pinMode(LedBuiltInPin, OUTPUT);
    pinMode(BOOTPIN, INPUT_PULLUP);   // Define o pino do botão BOOT como entrada
}

void atualiza_saidas()
{
    digitalWrite(LedBuiltInPin, LedBuiltInState);
    

    // Verificação do botão BOOT
    if (digitalRead(BOOTPIN) == LOW) {
        // Criação do JSON para informar que o botão foi pressionado
        JsonDocument doc;
        doc["message"] = "Botão BOOT pressionado";
        
        String output;
        serializeJson(doc, output);
        Serial.println(output);

        // Acende o LED e exibe a mensagem de que o LED foi ligado
        LedBuiltInState = HIGH;
        digitalWrite(LedBuiltInPin, LedBuiltInState);


        // Criação do JSON para informar que o LED foi ligado
        doc.clear();
        doc["message"] = "LED aceso";
        serializeJson(doc, output);
        Serial.println(output);
         // Apaga o LED após 500ms
        delay(500);
        LedBuiltInState = LOW;
        digitalWrite(LedBuiltInPin, LedBuiltInState);

        doc.clear();
        doc["message"] = "LED apagado";
        serializeJson(doc, output);
        Serial.println(output);
    }
}