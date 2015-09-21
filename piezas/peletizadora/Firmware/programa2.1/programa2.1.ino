// Programa de control de Peletizadora.


#include <AccelStepper.h>
#include <Servo.h>
#define PIN_STEP 46
#define PIN_DIR 48
#define PIN_EN A8
#define PIN_ASP 10
#define PIN_POT1 A5 //Potenciometro para controlar la velocidad de la tractora
#define PIN_POT2 A9  //Potenciometro para controlar la velocidad de las aspas
#define PIN_SERV 4  //Pin del servo oscilador
//AccelStepper stepper(1,STEP,DIR); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

AccelStepper stepper(1,PIN_STEP,PIN_DIR); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
Servo oscilador;
int pot1,pot2,pos=120;
int subida = 1; //Variable para controlar el giro del oscilador;
int ciclo=0;
int nciclo=150; //Numero de ciclos a incrementar el valor;
void setup()
{  
    pinMode(PIN_POT1,INPUT);
    pinMode(PIN_POT2,INPUT);
    pinMode(PIN_ASP,OUTPUT);
    pinMode(PIN_EN,OUTPUT);
    digitalWrite(PIN_EN,LOW);
    oscilador.attach(PIN_SERV);
    //2500
    stepper.setMaxSpeed(2500);
    stepper.setSpeed(150);
    //stepper.setAcceleration(2500);
    //stepper.setCurrentPosition(0);
    Serial.begin(9600);	

}

void loop()
{ 
  pot2=analogRead(PIN_POT2);
  pot2=map(pot2,0,1024,0,255);
  analogWrite(PIN_ASP,pot2);
  delay(2000);
  while(1){
      //Control de velocidad para tractora
      pot1=analogRead(PIN_POT1);
      pot1=map(pot1,0,1024,10,900);  //300-900
      digitalWrite(PIN_EN,LOW);
      stepper.setSpeed(pot1);
      stepper.runSpeed();

      //Control de velocidad para aspas
      pot2=analogRead(PIN_POT2);
      pot2=map(pot2,0,1024,0,255);
      analogWrite(PIN_ASP,pot2);

      //Control de velocidad para servo

      if (ciclo>=nciclo){
        if (subida){
          pos+=5;
          ciclo=0;
        }
        else if (!subida){
          pos-=5;;
          ciclo=0;
        }
      }
      if ((pos>=135)){
        subida=0;
      }
      else if (pos<=105){
        subida=1;
      }

      oscilador.write(pos);
      ciclo++;
  }
}
