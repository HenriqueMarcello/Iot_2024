void setupUmidificador();

void loopUmidificador();
void desligaUmidificador();

int pulsoUmidificador();

extern bool umidificadorLigado; // Estado inicial do umidificador

extern bool estadoLed; // Declaração da variável


extern bool travaPulso;

#define UMIDIFICADOR_PIN 27 // Pino de controle do umidificador (comando)