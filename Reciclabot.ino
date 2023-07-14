#include <Servo.h>

Servo myservo[2];
int servoPin[] = { 1,2,3,4,5,6,7,8,9,10,11,12};
float periodo[] = {4,4,4,4,2,2,2,2,1,1,1,1};
float anguloFase[] = {0,0,180,180,0,0,180,180,0,0,180,180};
int angulo[12];

#define TRIGGER_PIN 2  // Pino de trigger do sensor ultrassônico
#define ECHO_PIN 3     // Pino de echo do sensor ultrassônico
#define TEMPOREACAO 4      // duraçao do movimento loucos

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  for ( int i=0;i<12; i++)
    myservo[i].attach(servoPin[i]);
}

void loop() 
{

  float distancia = medeDistancia();
  if (distancia < 100) 
     movimentoSenoidal(TEMPOREACAO);  // Exemplo: período de 2 segundos, ângulo de fase de 45 graus, duração de 3 períodos
}

float medeDistancia()
{
   // Aciona o pulso de trigger no sensor ultrassônico
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // Lê o tempo de retorno do sinal de echo
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula a distância com base no tempo de retorno
  float distancia = duration * 0.034 / 2;
  return distancia;
 
}

void movimentoSenoidal(float tempo) 
{
    for (float t = 0; t <= tempo ; t += 0.05) {  // Intervalo de tempo de 20ms (ajuste conforme necessário)
      for ( int j=0;j<12; j++){
        int angulo = servopos(periodo[j], anguloFase[j], t);
        myservo[j].write(angulo);  // Define a posição d e cada servomotor
      }
      delay(50);  // Aguarda um curto período de tempo para atualizar a posição dos servomotor
    }
}

int servopos(float periodo, int anguloFase, float t)
{
    float frequencia = 1 / periodo;
    int angulo = sin(2 * PI * frequencia * t + radians(anguloFase)) * 90 + 90;  // Fórmula para calcular o ângulo da posição atual
    return angulo;
  
}
