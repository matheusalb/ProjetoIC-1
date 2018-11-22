/* ------------------- SENSOR ULTRASSÔNICO ------------------- */
#include "Ultrasonic.h"
#define ECHO_PIN 10 //Pino 10 recebe o pulso do echo
#define TRIG_PIN 9 //Pino 9 envia o pulso para gerar o echo
int distancia;
int ultimaDirecao = 1;
/* ------------------------------------------------------------ */


/* --------------------- PONTE H MOTORES ---------------------- */
#define MOTOR_E1 8
#define MOTOR_E2 7
#define MOTOR_EV 6
#define MOTOR_DV 5
#define MOTOR_D2 4
#define MOTOR_D1 3
#define VELOCIDADE_MIN 40
#define VELOCIDADE_MAX 70
/* ------------------------------------------------------------ */


/* ----------------------- SENSOR OPTICO ---------------------- */
#define IN_PIN 2 //pino de entrada
int cor = 0; //Inteiro que armazena o cor lido
/* ------------------------------------------------------------ */


/* ---------------------------- LEDS -------------------------- */
#define LED_DIREITA 11
#define LED_ESQUERDA 12
#define LED_OBSTACULO 13
/* ------------------------------------------------------------ */

// VARIÁVEIS
int estado = 0;


// FUNÇÕES
void para();
void andaEsquerda();
void andaDireita();
void desvia();


// Iniciando a função e passando os pinos
Ultrasonic ultrasonic(9, 10);

void setup() {
  // Define os pinos como saida do motor
  pinMode(MOTOR_E1, OUTPUT);
  pinMode(MOTOR_E2, OUTPUT);
  pinMode(MOTOR_EV, OUTPUT);
  pinMode(MOTOR_DV, OUTPUT);
  pinMode(MOTOR_D2, OUTPUT);
  pinMode(MOTOR_D1, OUTPUT);

  // Sensor óptico
  pinMode(IN_PIN, INPUT);

  // Sensor Ultrassonico
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

  // Leds
  pinMode(LED_DIREITA, OUTPUT);
  pinMode(LED_ESQUERDA, OUTPUT);
  pinMode(LED_OBSTACULO, OUTPUT);
}

void loop() {
  static int tempoBranco = millis();
  static int tempo = millis();
  andaEsquerda();
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  distancia = (ultrasonic.Ranging(CM));
    if (distancia <= 20) {
    //digitalWrite(LED_OBSTACULO, HIGH);
      tempo = millis();
      do {
        // Giro para Direita
        digitalWrite(LED_OBSTACULO, HIGH);
        analogWrite(MOTOR_EV, VELOCIDADE_MIN - 20);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX - 20);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo < 200);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 200 && millis() - tempo < 500);
      do {
        // Frente
        digitalWrite(LED_OBSTACULO, HIGH);
        analogWrite(MOTOR_EV, VELOCIDADE_MAX);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo > 500 && millis() - tempo < 800);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 800 && millis() - tempo < 1100);
      do {
        // Giro para Esquerda
        digitalWrite(LED_OBSTACULO, HIGH);
        analogWrite(MOTOR_EV, VELOCIDADE_MAX);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, HIGH);
        digitalWrite(MOTOR_D2, LOW);
      } while (millis() - tempo > 1100 && millis() - tempo < 1350);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 1350 && millis() - tempo < 1550);
      do {
        // Frente
        analogWrite(MOTOR_EV, VELOCIDADE_MAX);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo > 1550 && millis() - tempo < 2050);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 2050 && millis() - tempo < 2300);
      do {
        // Giro para Esquerda
        analogWrite(MOTOR_EV, VELOCIDADE_MAX);
        analogWrite(MOTOR_DV, VELOCIDADE_MIN);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo > 2300 && millis() - tempo < 2600);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 2600 && millis() - tempo < 2900);
      do {
        // Frente
        analogWrite(MOTOR_EV, VELOCIDADE_MAX - 0);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX - 0);
        digitalWrite(MOTOR_E1, LOW);
        digitalWrite(MOTOR_E2, HIGH);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo > 2900 && millis() - tempo < 3100);
      do{
        para();
        digitalWrite(LED_OBSTACULO, LOW);
      }while(millis() - tempo > 3100 && millis() - tempo < 3200);
      do {
        // Giro para Direita
        analogWrite(MOTOR_EV, VELOCIDADE_MIN);
        analogWrite(MOTOR_DV, VELOCIDADE_MAX);
        digitalWrite(MOTOR_E1, HIGH);
        digitalWrite(MOTOR_E2, LOW);
        digitalWrite(MOTOR_D1, LOW);
        digitalWrite(MOTOR_D2, HIGH);
      } while (millis() - tempo > 3200 && millis() - tempo < 3500);
      if (millis() - tempo >= 3500) {
        para();
        digitalWrite(LED_OBSTACULO, LOW);
        tempo = millis();
        delay(3000);
      }
    }
  andaDireita();
}

void andaEsquerda() {
  digitalWrite(LED_DIREITA, LOW);
  digitalWrite(LED_ESQUERDA, HIGH);
  do {
    analogWrite(MOTOR_EV, VELOCIDADE_MIN);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX);
    digitalWrite(MOTOR_E1, HIGH);
    digitalWrite(MOTOR_E2, LOW);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (digitalRead(IN_PIN) == HIGH); // BRANCO -> HIGH

  do {
    estado = digitalRead(IN_PIN);
  } while (estado == LOW);
}


void andaDireita() {
  digitalWrite(LED_ESQUERDA, LOW);
  digitalWrite(LED_DIREITA, HIGH);
  do {
    analogWrite(MOTOR_EV, VELOCIDADE_MAX);
    analogWrite(MOTOR_DV, VELOCIDADE_MIN);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, HIGH);
    digitalWrite(MOTOR_D2, LOW);
  } while (digitalRead(IN_PIN) == HIGH);

  do {
    estado = digitalRead(IN_PIN);
  } while (estado == LOW);
}

void para() {
  analogWrite(MOTOR_EV, 0);
  analogWrite(MOTOR_DV, 0);
  digitalWrite(MOTOR_E1, HIGH);
  digitalWrite(MOTOR_E2, HIGH);
  digitalWrite(MOTOR_D1, HIGH);
  digitalWrite(MOTOR_D2, HIGH);
}

void desvia() {
  //  static int tempo = millis();
  //  do{
  //    analogWrite(MOTOR_EV, VELOCIDADE_MAX);
  //    analogWrite(MOTOR_DV, VELOCIDADE_MAX);
  //    digitalWrite(MOTOR_E1, HIGH);
  //    digitalWrite(MOTOR_E2, LOW);
  //    digitalWrite(MOTOR_D1, HIGH);
  //    digitalWrite(MOTOR_D2, LOW);
  //  }while(millis() - tempo < 2000);
  //  if(millis() - tempo >= 2000){
  //    para();
  //    tempo = millis();
  //    delay(5000);
  //  }
}

