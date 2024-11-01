#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"
#include "umidificador.h"
//Definição dos pinos dos botões

#define BOTAO_PIN 23

// Inicializa o objeto Bounce com o pino do botão e o tempo de debounce
Bounce bounce = Bounce();
//Inicializa as entradas digitais
void inicializa_entradas()
{
    bounce.attach(BOTAO_PIN, INPUT_PULLUP);
}

//Atualiza o estado dos botões
void atualiza_botoes()
{
    //atualiza do estado do botao_boot
    bounce.update();
   
}

bool botao_pressionado()
{
    if (bounce.fell())
    {
        pulsoUmidificador();
        return true;  // Retorna true se o botão foi pressionado
    }
    return false;  // Retorna false se o botão não foi pressionado
}

//Retorna se o botão boot foi solto
bool botao_solto()
{
    return bounce.rose();
}
