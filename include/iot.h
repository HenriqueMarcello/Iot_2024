#pragma once

//Inicia a conexão WiFi
void setup_wifi();

//Inicia a conexão MQTT
void inicializa_mqtt();
/*
@brief Publica uma mensagem no tópico MQTT
@param topico Tópico mqtt a ser publicado
@param msg Mensagem a ser publicada
*/
void publica_mqtt(String topico, String msg);

//Atualiza a conexão MQTT
void atualiza_mqtt();