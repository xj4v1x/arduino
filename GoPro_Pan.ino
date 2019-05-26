#include <Servo.h>
 //500-2500
 //myservo.writeMicroseconds(500-2500);
Servo myservo;  // crea el objeto servo
 
int pos = 0;    // posicion del servo
int BotonA = 5;
int BotonB = 6;
bool Derecha = false;
int opt = 0;
int minutos = 0;
int segundos = 0;
long tiempo = 120; //minutos
int servo = 7;
int buzz = 8;

void setup() {
  Serial.begin(9600);
  pinMode (BotonA, INPUT);
  pinMode (BotonB, INPUT);
  pinMode(servo, OUTPUT);
  pinMode(buzz, OUTPUT);
  myservo.attach(servo);  // vincula el servo al pin digital 7
  myservo.writeMicroseconds(1500);             
  delay (500);
  myservo.detach();
  Sentido();
  Tiempo();
  Gira();
  Fin();
}
 
void loop() {
}

void Sentido(){
  opt = 0;
  while (opt==0) {
    if (digitalRead(BotonA)==HIGH){     
      delay(300);
      beep(277,200);
      opt = 1;
      Derecha = true;
      myservo.attach(servo);
      myservo.writeMicroseconds(500);             
      delay(500);
      myservo.detach();
    }
    if (digitalRead(BotonB)==HIGH){
      delay(300);
      beep(277,200);
      opt = 2;
      Derecha = false;
      myservo.attach(servo);
      myservo.writeMicroseconds(2500);
      delay(500);
      myservo.detach();
    }
  }
}


void Tiempo(){
  opt = 0;
  while (opt==0) {
    if (digitalRead(BotonA)==HIGH){     
      delay(300);
      beep(277,200);
      tiempo = tiempo/2;
      if (tiempo<1) {
        tiempo=60;
        beep(440 ,400);
      }
      Serial.println(tiempo);
    }
    if (digitalRead(BotonB)==HIGH){
      delay(300);
      beep(440 ,400);
      opt = 1;
    }
  }
}


void Gira(){
  tiempo = (tiempo*60000)/2000;
  myservo.attach(servo);
  Serial.print(Derecha);
  if (Derecha == true) {
    myservo.writeMicroseconds(500);             
    delay(500);
    for (int i=500; i <= 2500; i++) {
      myservo.writeMicroseconds(i);             
      delay (tiempo);       
      Serial.println(i);
    } 
  } else {
    myservo.writeMicroseconds(2500);             
    delay(500);
    for (int i=2500; i >= 500; i--) {
      myservo.writeMicroseconds(i);
      delay (tiempo);
      Serial.println(i);
    } 
  }
   myservo.detach();
}


void Fin() {
  beep(261,500);
  beep(277,500);
  beep(294,500);
  
  

  
}
void beep(int tono, int espera) {
  tone(8, tono);
  delay(espera);                 // Espera
  noTone(8);
}
