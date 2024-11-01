#pragma once

#include <Bounce2.h>


//Inicia as entradas digitais
void inicializa_entradas();

//Atualiza o estado do botão
void atualiza_botoes();

/*
@brief Indica se o botão boot foi pressionado
@return Verdadeiro caso for pressionado
*/
bool botao_pressionado();


/*
@brief Indica se o botão boot foi solto
@return Verdadeiro caso for solto
*/
bool botao_solto();

/*
@brief Indica se o botão externo foi pressionado
@return Verdadeiro caso for pressionado
*/


#define BOTAO_PIN 23     // Pino onde o botão está conectado

extern bool botaoEstadoAnterior;



