#include <ESP32Servo.h>
#include "atuadores.h"


#define SERVO_PIN 5

Servo servoMotor; 

void inicializa_servos()
{
    servoMotor.attach(SERVO_PIN, 500, 2500);
}

void posiciona_servo(int angulo=0)
{
    servoMotor.write(angulo);
}