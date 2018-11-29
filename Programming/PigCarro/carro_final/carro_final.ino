/**********************************************************
* UNIVERSIDADE FEDERAL DE PERNAMBUCO - UFPE
* CENTRO DE INFORMARICA - CIN
* INTRODUCAO A COMPUTACAO - IF668 EC
* CODIGO PARA TESTE DO SENSOR OPTICO
* GRUPO: Gloria a Deuxx
* INTEGRANTES:  Elisson Rodrigo da Silva Araujo(ersa); Natalia Souza Soares(nss2); Arthur Henrique Anibal da Costa(ahac); 
*               Pedro Henrique Sarmento de Paula(pshp); Matheus Viana Coelho Albuquerque(mvca); Lucas Grisi Oliveira de Queiroz(lgoq); 
*               Eliasjam Luiz de Oliveira(elo).
*
********************************************************/

/* ------------------- SENSOR ULTRASSÔNICO ------------------- */
#include "Ultrasonic.h"         // Inclui a biblioteca do sensor ultrasonico
#define ECHO_PIN 10             // Pino 10 recebe o pulso do echo
#define TRIG_PIN 9              // Pino 9 envia o pulso para gerar o echo
int distancia;                  // Variavel que recebe a distancia lida pelo sensor
Ultrasonic ultrasonic(9, 10);   // Iniciando a função e passando os pinos
/* ------------------------------------------------------------ */


/* --------------------- PONTE H MOTORES ---------------------- */
#define MOTOR_E1 8
#define MOTOR_E2 7
#define MOTOR_EV 6
#define MOTOR_DV 5
#define MOTOR_D2 4
#define MOTOR_D1 3
#define VELOCIDADE_MIN 40         // Define a velocidade maxima do carrinho
#define VELOCIDADE_MAX 70         // Define a velocidade minima do carrinho
#define VELOCIDADE_MIN_OBST 40    // Define a velocidade minima do carrinho durante o desvio do obstaculo
#define VELOCIDADE_MAX_OBST 70    // Define a velocidade maxima do carrinho durante o desvio do obstaculo
/* ------------------------------------------------------------ */


/* ----------------------- SENSOR OPTICO ---------------------- */
#define IN_PIN 2      // Pino de entrada
int cor = 0;          // Inteiro que armazena o cor lido (BRANCO -> HIGH; PRETO -> LOW)
/* ------------------------------------------------------------ */


/* ---------------------------- LEDS -------------------------- */
#define LED_DIREITA 11    // Led do lado direito do carrinho
#define LED_ESQUERDA 12   // Led do lado esquerdo do carrinho
#define LED_OBSTACULO 13  // Led central
/* ------------------------------------------------------------ */

//DECLARAÇÕES DAS VARIÁVEIS
int estado = 0;           // Variavel que recebe o valor lido pelo sensor optico
int flagObstaculo = 1;    // Variavel que indica se o obstaculo ja desviado

//DECLARAÇÕES DAS FUNÇÕES
void para();              // Função que para os motores
void andaEsquerda();      // Função que move o carrinho para esquerda ate que encontre a linha preta
void andaDireita();       // Função que move o carrinho para direita ate que encontre a linha preta
void desvia();            // Função que move o carrinho para desviar o obstaculo
int lerDistancia();       // Função que ler a distancia entre carrinho e o obstaculo
/* ------------------------------------------------------------ */


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

  andaEsquerda();                             // Move o carrinho para o lado esquerdo até que encontre a linha preta

  if (flagObstaculo) {                        // Verifica se o obstaculo ja foi desviado    
    distancia = lerDistancia();               // Chama a função 'lerDistancia' que verifica a distancia entre o carrinho e o obstaculo
  }
  if (distancia <= 19 && flagObstaculo) {     // Verifica se a distancia lida é menor ou igual a 19cm e se o obstaculo ja foi desviado
    desvia();                                 // Chama a função para desviar o obstaculo
  }
  andaDireita();                              // Move o carrinho para o lado direito até que encontre a linha preta
}


/* ------------------------------- FUNÇÕES ----------------------------- */

//Função que ler a distancia do carrinho ao obstaculo
int lerDistancia(){
  digitalWrite(TRIG_PIN, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);             // Emite um pulso sonoro (indica o incio da transmissao de dados)
  delayMicroseconds(10);                
  digitalWrite(TRIG_PIN, LOW);              // Para a emissão
  distancia = (ultrasonic.Ranging(CM));     // A variavel distancia recebe o valor lido pelo sensor (distancia = (tempo echo em nivel alto*velocidade do som)/2)
  return distancia;                         // Retorna a distancia lida em centímetros
}

//Função que move o carrinho para o lado esquerdo
void andaEsquerda() {
  digitalWrite(LED_DIREITA, LOW);     // Apaga o led direito
  digitalWrite(LED_ESQUERDA, HIGH);   // Acende o led esquerdo(indicando o lado do movimento)
  // Loop enquanto o sensor optico estiver lendo branco(HIGH)
  do {
    // Movimentação dos motores, motor direito no sentido horario na velocidade maxima e o motor esquerdo no sentido anti-horario na velocidade minima
    analogWrite(MOTOR_EV, VELOCIDADE_MIN);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX);
    digitalWrite(MOTOR_E1, HIGH);
    digitalWrite(MOTOR_E2, LOW);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (digitalRead(IN_PIN) == HIGH);
  // Loop enquanto o sensor optico estiver lendo preto(passando por cima da linha)
  do {
    estado = digitalRead(IN_PIN);
  } while (estado == LOW);
}

//Função que move o carrinho para o lado direito
void andaDireita() {
  digitalWrite(LED_ESQUERDA, LOW);    // Apaga o led esquerdo
  digitalWrite(LED_DIREITA, HIGH);    // Acende o led direito(indicando o lado do movimento)
  // Loop enquanto o sensor optico estiver lendo branco(HIGH)
  do {
    // Movimentação dos motores, motor direito no sentido anti-horario na velocidade minima e o motor esquerdo no sentido horario na velocidade maxima
    analogWrite(MOTOR_EV, VELOCIDADE_MAX);
    analogWrite(MOTOR_DV, VELOCIDADE_MIN);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, HIGH);
    digitalWrite(MOTOR_D2, LOW);
  } while (digitalRead(IN_PIN) == HIGH);
  // Loop enquanto o sensor optico estiver lendo preto(passando por cima da linha)
  do {
    estado = digitalRead(IN_PIN);
  } while (estado == LOW);
}

//Função que trava a movimentação dos motores
void para() {
  analogWrite(MOTOR_EV, 0);
  analogWrite(MOTOR_DV, 0);
  digitalWrite(MOTOR_E1, HIGH);
  digitalWrite(MOTOR_E2, HIGH);
  digitalWrite(MOTOR_D1, HIGH);
  digitalWrite(MOTOR_D2, HIGH);
}

//Função que movimenta o carrinho para executar o desvio do obstaculo
void desvia() {
  int tempo = millis();     // Variavel que recebe o tempo de execução da função em millisegundos

  // Giro para Direita enquanto o tempo for menor que 200ms
  do {
    digitalWrite(LED_OBSTACULO, HIGH);
    analogWrite(MOTOR_EV, VELOCIDADE_MIN_OBST - 20);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST - 20);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (millis() - tempo < 200);

  // Para o carrinho durante 300ms
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo > 200 && millis() - tempo < 500);

  // Movimento para frente durente 200ms
  do {
    digitalWrite(LED_OBSTACULO, HIGH);
    analogWrite(MOTOR_EV, VELOCIDADE_MAX_OBST);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST + 5);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (millis() - tempo > 500 && millis() - tempo < 700);

  // Para o carrinho durante 150ms
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo > 700 && millis() - tempo < 850);

  // Giro para Esquerda durante 200ms
  do {
    digitalWrite(LED_OBSTACULO, HIGH);
    analogWrite(MOTOR_EV, VELOCIDADE_MAX_OBST);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, HIGH);
    digitalWrite(MOTOR_D2, LOW);
  } while (millis() - tempo > 850 && millis() - tempo < 1050);

  // Para o carrinho durante 150ms
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo > 1050 && millis() - tempo < 1200);

  // Movimento para frente durante 700ms
  do {
    analogWrite(MOTOR_EV, VELOCIDADE_MAX_OBST);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (millis() - tempo > 1200 && millis() - tempo < 1900);

  // Para o carrinho durante 150ms
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo > 1900 && millis() - tempo < 2050);

  // Giro para Esquerda durante 150ms
  do {
    digitalWrite(LED_OBSTACULO, HIGH);
    analogWrite(MOTOR_EV, VELOCIDADE_MAX_OBST);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, HIGH);
    digitalWrite(MOTOR_D2, LOW);
  } while (millis() - tempo > 2050 && millis() - tempo < 2200);

  // Para o carrinho durante 150ms
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo > 2200 && millis() - tempo < 2350);

  // Movimenta para frente até o sensor optico encontre o linha preta
  do {
    analogWrite(MOTOR_EV, 60);
    analogWrite(MOTOR_DV, 65);
    digitalWrite(MOTOR_E1, LOW);
    digitalWrite(MOTOR_E2, HIGH);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (digitalRead(IN_PIN) == HIGH);

  // Para o carrinho durante 150ms
  tempo = millis();   //Reinicia o tempo
  do {
    para();
    digitalWrite(LED_OBSTACULO, LOW);
  } while (millis() - tempo < 150);

  // Giro para Direita ate que o sensor optico encontre a linha preta
  do {
    analogWrite(MOTOR_EV, VELOCIDADE_MIN_OBST);
    analogWrite(MOTOR_DV, VELOCIDADE_MAX_OBST);
    digitalWrite(MOTOR_E1, HIGH);
    digitalWrite(MOTOR_E2, LOW);
    digitalWrite(MOTOR_D1, LOW);
    digitalWrite(MOTOR_D2, HIGH);
  } while (digitalRead(IN_PIN) == HIGH);
   
  para();                             // Para o carrinho 
  digitalWrite(LED_OBSTACULO, LOW);   //Desliga o led(indicando o fim do desvio)
  tempo = millis();                   // Reinicia o tempo
  delay(50);                          // Espera 50ms
  flagObstaculo = 0;                  // Zera a variavel 'flagObstaculo', indicando que o carrinho já realizou o desvio de obstaculo e não permitindo que o faça novamente, evitando desvios acidentais durante o resto do percuso
}
/* ------------------------------------------------------------------ */
