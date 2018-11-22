#include "Ultrasonic.h"
/* -----SENSOR ULTRASSÔNICO------ */
#define echoPin 10 //Pino 10 recebe o pulso do echo
#define trigPin 9 //Pino 9 envia o pulso para gerar o echo
int distancia;
int ultimaDirecao = 1;

/* -----PONTE H MOTORES------ */
#define Motor_E1 8
#define Motor_E2 7
#define Motor_EV 6
#define Motor_DV 5
#define Motor_D2 4
#define Motor_D1 3

// velocidades
#define vMenor 25
#define vMaior 60

#define branco 0
#define preto 1

int inicio = 1;
/* -----SENSOR OPTICO------ */
#define inPin 2 //pino de entrada
int valor = 0; //Inteiro que armazena o valor lido
int estado = 0;
int cor = 1;
boolean sentido = false;
int viuPreto = 0;

//iniciando a função e passando os pinos
Ultrasonic ultrasonic(9, 10);

void travaRoda();
void boost();
void para();
void andaEsquerda();
void andaDireita();
void desvia();

void setup() {
  //Define os pinos como saida do motor
  pinMode(Motor_E1, OUTPUT);
  pinMode(Motor_E2, OUTPUT);
  pinMode(Motor_EV, OUTPUT);
  pinMode(Motor_DV, OUTPUT);
  pinMode(Motor_D2, OUTPUT);
  pinMode(Motor_D1, OUTPUT);

  //sensor óptico
  Serial.begin(9600);
  pinMode(inPin, INPUT);

  //ultrassonico
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

}

void loop() {
  static int tempoBranco = millis();
  static int tempo = millis();
  andaEsquerda();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distancia = (ultrasonic.Ranging(CM));
//  if (distancia <= 20) {
//    tempo = millis();
//    do {
//      analogWrite(Motor_EV, vMenor);
//      analogWrite(Motor_DV, vMaior);
//      digitalWrite(Motor_E1, LOW);
//      digitalWrite(Motor_E2, HIGH);
//      digitalWrite(Motor_D1, LOW);
//      digitalWrite(Motor_D2, HIGH);
//    } while (millis() - tempo < 400);
//    if (millis() - tempo >= 400) {
//      para();
//      tempo = millis();
//      delay(3000);
//    }
//  }
  andaDireita();
}

void andaEsquerda() {
  do {
    analogWrite(Motor_EV, vMenor);
    analogWrite(Motor_DV, vMaior);
    digitalWrite(Motor_E1, HIGH);
    digitalWrite(Motor_E2, LOW);
    digitalWrite(Motor_D1, LOW);
    digitalWrite(Motor_D2, HIGH);
  } while (digitalRead(inPin) == HIGH); // BRANCO -> HIGH

  do {
    estado = digitalRead(inPin);
  } while (estado == LOW);
}


void andaDireita() {
  do {
    analogWrite(Motor_EV, vMaior);
    analogWrite(Motor_DV, vMenor);
    digitalWrite(Motor_E1, LOW);
    digitalWrite(Motor_E2, HIGH);
    digitalWrite(Motor_D1, HIGH);
    digitalWrite(Motor_D2, LOW);
  } while (digitalRead(inPin) == HIGH);

  do {
    estado = digitalRead(inPin);
  } while (estado == LOW);
}

void para() {
  analogWrite(Motor_EV, 0);
  analogWrite(Motor_DV, 0);
  digitalWrite(Motor_E1, HIGH);
  digitalWrite(Motor_E2, HIGH);
  digitalWrite(Motor_D1, HIGH);
  digitalWrite(Motor_D2, HIGH);
}

void desvia() {
  //  static int tempo = millis();
  //  do{
  //    analogWrite(Motor_EV, vMaior);
  //    analogWrite(Motor_DV, vMaior);
  //    digitalWrite(Motor_E1, HIGH);
  //    digitalWrite(Motor_E2, LOW);
  //    digitalWrite(Motor_D1, HIGH);
  //    digitalWrite(Motor_D2, LOW);
  //  }while(millis() - tempo < 2000);
  //  if(millis() - tempo >= 2000){
  //    para();
  //    tempo = millis();
  //    delay(5000);
  //  }
}

