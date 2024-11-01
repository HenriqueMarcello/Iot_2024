#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>
#include "motorDC.h"

// Prototipar (declarar) as funções antes do setup e loop
void motorForward(int speed);
void motorStop();

// Definir pinos de controle do motor e o botão
int in1 = 25;      // IN1 do L298N
int in2 = 26;      // IN2 do L298N
int buttonPin = 0; // Botão BOOT (GPIO 0 no ESP32)

// Variáveis para o canal PWM no ESP32
const int pwmChannel1 = 0;
const int pwmFreq = 1000;    // Frequência PWM (1 kHz)

const int pwmResolution = 8; // Resolução PWM (8 bits, valores de 0 a 255)

// Variável para armazenar o estado do motor
bool motorLigado = false;

void MotorSetup()
{
    // Configurar os pinos como saída
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    // Configurar o pino do botão como entrada com pullup interno
    pinMode(buttonPin, INPUT_PULLUP);

    // Configurar canal PWM no ESP32
    ledcSetup(pwmChannel1, pwmFreq, pwmResolution);

    // Associar o pino IN1 ao canal PWM
    ledcAttachPin(in1, pwmChannel1);

    // Iniciar o motor parado
    motorStop();
}

void Motorloop()
{
    // Verificar se o botão foi pressionado
    if (digitalRead(buttonPin) == LOW)
    {

        // Alternar o estado do motor
        if (motorLigado)
        {
            motorStop(); // Desliga o motor
            motorLigado = false;
        }
        else
        {
            motorForward(150); // Liga o motor a velocidade 100
            motorLigado = true;
        }
    }
}

// Função para rodar o motor para frente
void motorForward(int speed)
{
    ledcWrite(pwmChannel1, speed); // PWM no IN1 com velocidade 100
    digitalWrite(in2, LOW);        // IN2 LOW para mover para frente
}

// Função para parar o motor
void motorStop()
{
    ledcWrite(pwmChannel1, 0); // IN1 em LOW (desligado)
    digitalWrite(in2, LOW);    // IN2 também LOW para garantir parada completa
}