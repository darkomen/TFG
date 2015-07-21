#define hall_pin 7
#define rele_pin 6 

int last_state=1,state=0;
long previus_millis;
long interval = 1000;
void setup(){
   pinMode(hall_pin,INPUT_PULLUP);
   pinMode(rele_pin,OUTPUT);
   Serial.begin(9600); 
}

void loop(){
    /*Realizamos el retardo sin usar la funcion delay()*/
   unsigned long current_millis=millis();
   if (current_millis - previus_millis > interval){
     //Almacenamos el valor actual del timer
     previus_millis = current_millis;
     /*apagamos la salida del rele, aprovechamos el muestreo del
     programa para hacer un pulso en la salida y solo si detectamos
     el pulso del encoder activamos el rele*/
     digitalWrite(rele_pin,LOW);
     //Comprobamos el cambio de estado del sensor HALL.
     state=digitalRead(hall_pin);
     if ((state!=last_state) && state==0){
       //Si hay un cambio de estado activamos el rele
       digitalWrite(rele_pin,HIGH);
     }
     last_state=state;
   }
   
}
