// TRACTORA.ino

//Librería del T1
#include "config/known_16bit_timers.h"
#include "TimerOne.h"

//Modo debug para mostrar por pantalla información de la velocidad
#define DEBUG

//definiciones pines driver paso a paso
#define PIN_STEP 46
#define PIN_DIR 48
#define PIN_EN A8
#define PIN_POT A10


//Definiciones para el cálculo de las velocidades
#define steps_vuelta 3200 //Número de pasos por vuelta = 360/(angulo_motor/microsteps_drivers)
#define us_irq 10  //microsegundos de ejecución de la interrupción.
#define velocidades 20  //Numero de velocidades a las que podemos ir
#define pi 3.14159265359  //PI
#define radio 19.45      //Diámetro de la polea para poder calcular la velocidad lineal de tracción.

long previus_millis;//variable con los millis() de la ejecución anterior.
long interval = 250; //intervalo de ejecución del programa en millis
int ticks=0; //Variable con el valor de ticks que debemos contabilizar.
int tick_count=0; //Variable donde vamos acumulano las interrupciones del timer.
//BUENA
float rpm_speed[]= {1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4};//array con las velocidades en RPM
//float rpm_speed[]= {1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.1, 4.3, 4.5, 4.7, 4.9, 5.1, 5.3};

//float rpm_speed[] ={  1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9};
int tick_speed[velocidades+1] = {-1,0,0,0,0,0,0,0,0,0,0};  //tabla con los ticks de retardo, velocidades en RPM
long actual_speed=0;  //variable con el valor de tick que tenemos que contar. de 0 a 7
int i=0;              //Numero de muestras tomadas 
void setup() {
        #ifdef DEBUG
        Serial.begin(9600);
        #endif
        //habilitamos los pines de salida y entrada
	pinMode(PIN_EN,OUTPUT);
	pinMode(PIN_DIR,OUTPUT);
	pinMode(PIN_STEP,OUTPUT);
        //Interrupción timer para contar los ticks del motor paso a paso.
	Timer1.initialize(us_irq);  //interupción del timer 1 cada 10uS
  	Timer1.attachInterrupt(timerISR); // Ejecutamos la rutina del timer
        //Cálculo de los ticks de cada velocidad.
        for (int i =0;i<=velocidades-1;i++){
           tick_speed[i+1]=((1/(rpm_speed[i]*(steps_vuelta/60)))/(us_irq*0.000001));
        }
}

void loop() {
        //Almacenamos el valor de la entrada analogica en una variable y contamos el núnero 
        //de muestras que tomamo en el tiempo de espera de ejecución del ciclo.
        actual_speed += map(analogRead(PIN_POT),10,1000,0,velocidades);
        i++;
           
        //Serial.println("fin FOR");
        unsigned long current_millis=millis();
        //Si el tiempo pasado es mayor que el intervalo realizamos la ejecución del programa.
        if (current_millis - previus_millis > interval){
            //Almacenamos el valor actual del timer
            previus_millis = current_millis;
            //Calculamos la media del valor del sensor medido.
            actual_speed = (actual_speed/i);
            Serial.println(actual_speed);
            //Almacenas los numeros de tick a contar para alcanzar la velocidad deseada.
            ticks=tick_speed[actual_speed];
            
            //Mostramos los RPM y velocidad lineal a la que giramos sólo si estamos en modo DEBUG
            #ifdef DEBUG 
              Serial.print("Girando a: ");
              if (actual_speed==0){
                Serial.print("0");
                Serial.print(" RPM");
                Serial.print("\t");
                Serial.println("0 mm/s");
              }
              else if (actual_speed!=0){
                Serial.print(rpm_speed[actual_speed]);
                Serial.print(" RPM");
                Serial.print("\t");
                Serial.print((rpm_speed[actual_speed]*pi*radio)/60);
                Serial.println(" mm/s");
              }
            #endif
            actual_speed=0;
            i=0;
         }
}


//IRS del timer
void timerISR(){
  //incrementamos los pulsos
  tick_count++;
  //Si llegamos al máximo, generamos un pulso
  if(tick_count == ticks) {  
    
    // Generamos un pulso
    digitalWrite(PIN_STEP, HIGH);
    digitalWrite(PIN_STEP, LOW);
    
    //reseteamos el contador
    tick_count = 0;
  }
}
