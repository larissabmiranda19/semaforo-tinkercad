#include <Servo.h>

Servo cancela;

int tempo = 0;
int botao = 0;
int distancia = 0;
long duracao = 0;
int luz = 0;
int frequencia = 0;

void setup()
{
  pinMode(11, OUTPUT);  // vermelho veículo
  pinMode(12, OUTPUT);  // amarelo veículo
  pinMode(13, OUTPUT);  // verde veículo

  pinMode(9, OUTPUT);   // vermelho pedestre
  pinMode(10, OUTPUT);  // verde pedestre

  pinMode(7, OUTPUT);   // buzzer
  pinMode(8, INPUT);    // botão

  pinMode(5, OUTPUT);   // TRIG
  pinMode(4, INPUT);    // ECHO

  cancela.attach(6);

  Serial.begin(9600);
}

void loop()
{
  luz = analogRead(A0);

  // DIA
  if(luz < 80)
  {
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);

    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    digitalWrite(12, HIGH);

    delay(500);

    digitalWrite(12, LOW);

    delay(500);

    // SENSOR ULTRASSÔNICO
    digitalWrite(5, LOW);
    delayMicroseconds(2);

    digitalWrite(5, HIGH);
    delayMicroseconds(10);

    digitalWrite(5, LOW);

    duracao = pulseIn(4, HIGH);

    distancia = duracao * 0.034 / 2;

    // CANCELA
    if(distancia <= 30)
    {
      cancela.write(90);

      delay(3000);

      cancela.write(0);
    }

    if(distancia > 30)
    {
      cancela.write(0);
    }
  }

  // NOITE
  if(luz >= 80)
  {
    // VERDE DO VEÍCULO

    if(tempo < 25)
    {
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);

      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);

      // BOTÃO DO PEDESTRE
      if(digitalRead(8) == HIGH)
      {
        tempo = 25;
      }
    }

    // AMARELO DO VEÍCULO
    if(tempo >= 25 && tempo < 30)
    {
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);

      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
    }

    // VERMELHO DO VEÍCULO
    if(tempo >= 30 && tempo < 45)
    {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);

      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);

      // BUZZER
      tone(7, 500);
      delay(500);

      tone(7, 1000);
      delay(500);
    }

    // FIM DO CICLO
    
    tempo++;

    delay(1000);

    if(tempo >= 45)
    {
      tempo = 0;
      noTone(7);
    }
  }
}
