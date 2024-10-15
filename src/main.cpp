/*************************************************************
 * Projeto: Automação IoT com ESP32
 * Escola: SENAI de Informática
 * Curso: Aprendizagem Industrial - Integrador de Soluções em Nuvem
 * Data: 01/08/2024
 *
 * Autor: Marcello Henrique
 * Versão: 0.9
 *
 * Descrição:
 * Este projeto utiliza o ESP32 para implementar uma solução
 * de automação com conectividade WiFi e integração via MQTT.
 * O código controla entradas e saídas digitais, monitorando
 * estados e publicando informações para um broker MQTT.
 *************************************************************/

#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "atuadores.h"
#include "funcoes.h"

// Definição dos tópicos de publicação
#define mqtt_pub_topic1 "projeto_integrado/SENAI134/Cienciadedados/Grupoprime"

// Variáveis globais
unsigned long tempoAnteriorIntervaloPublicacao = 0;
const unsigned long intervaloPublicao = 1000;

// Prototipo das funcoes

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  //inicializa_mqtt();
  randomSeed(esp_random());
}

void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();
  randomiza_senha();

  JsonDocument doc;
  String json;
  bool mensagemPendente = false;

  if (millis() - tempoAnteriorIntervaloPublicacao >= intervaloPublicao)
  {
    tempoAnteriorIntervaloPublicacao = millis();
    doc["timeStamp"] = timeStamp();
    mensagemPendente = true;
  }

  if (botao_boot_pressionado())
  {
    LedBuiltInState = !LedBuiltInState;
    doc["LedState"] = LedBuiltInState;
    doc["BotaoState"] = true;
    doc["timeStamp"] = timeStamp();
    mensagemPendente = true;
  }

  else if (botao_boot_solto())
  {
    doc["BotaoState"] = false;
    doc["timeStamp"] = timeStamp();
    mensagemPendente = true;
  }

  if (mensagemPendente)
  {
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
    mensagemPendente = false;
  }
}

// Variáveis e funções relacionadas à senha
int senha;
const unsigned long intervaloNormal = 30000;
const unsigned long intervaloEstendido = 90000;
unsigned long tempoInicialResetSenha = 0;
unsigned long intervaloResetSenha = 0;

int randomiza_senha()
{
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoInicialResetSenha >= intervaloResetSenha)
  {
    resetaUsuario();
    if (intervaloResetSenha != intervaloNormal)
      intervaloResetSenha = intervaloNormal;
    tempoInicialResetSenha = tempoAtual;
    senha = random(1000, 9999);
    Serial.printf("Nova Senha: %d\n", senha);
  }
  return senha;
}

void tempoSenhaEstendido()
{
  if (intervaloResetSenha != intervaloEstendido)
  {
    unsigned long tempoAtual = millis();
    tempoInicialResetSenha = tempoAtual;
    intervaloResetSenha = intervaloEstendido;
    Serial.println("Senha estendida por 90 segundos");
  }
}