#pragma once

//Inicia a conexão WiFi
void setup_wifi();
void inicializa_mqtt();
void publica_mqtt(String topico, String msg);

void atualiza_mqtt();

void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();
void tratar_msg(char *topic, String msg);

void verifica_boot();