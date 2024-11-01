#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <funcoes.h>
#include <saidas.h>
#define debug 0
// Cria um objeto do sensor
Adafruit_VL53L0X sensorTinta = Adafruit_VL53L0X();

// Definir as dimensões do reservatório (em centímetros)
const float alturaTotalReservatorio = 200.0; // Altura total do reservatório

void inicializaSensorTinta()
{
  // Inicializa o sensor VL53L0X
  if (!sensorTinta.begin())
  {
    Serial.println("Falha ao inicializar o VL53L0X. Verifique a conexão.");
    while (1)
      ; // Fica travado aqui em caso de falha
  }
  if(debug) Serial.println("Sensor VL53L0X iniciado com sucesso!");
}

void medirNivelTinta()
{
  // Obtenha a leitura de distância
  VL53L0X_RangingMeasurementData_t medida;
  sensorTinta.rangingTest(&medida, false); // false = não use o modo contínuo

  // Exibe a distância medida em centímetros
  if (medida.RangeStatus != 4) // Se o sensor estiver funcionando corretamente
  {
    distanciaMedida = medida.RangeMilliMeter / 10.0; // Converte mm para cm
   if(debug) Serial.print("Distância medida (cm): ");
   if(debug) Serial.println(distanciaMedida, 1); // Exibe a distância com 1 casa decimal

    // Calcula o nível de tinta
    float nivelTinta = alturaTotalReservatorio - distanciaMedida;
    if (nivelTinta < 0)
      nivelTinta = 0; // Se a distância for maior que a altura, o nível é 0
    
   if(debug) Serial.print("Nível de tinta (cm): ");
   if(debug) Serial.println(nivelTinta, 1); // Exibe o nível de tinta com 1 casa decimal
  }
  else
  {
   if(debug) Serial.println("Fora de alcance"); // Se a medição estiver fora do alcance
  }

  // Aguarde um pouco antes da próxima medição
  //delay(1000); // Aguarda 1 segundo para a próxima leitura
}
