//Autor- Matěj Fr.
#include"IRremote.h" //nezapomenout správnou knihovnu z CD
#define pinIN 7

IRrecv dalkoveOvl(pinIN);
decode_results vysledek;

void go(int PL, int PR) {
  /*digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  analogWrite(3,PR);

  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  analogWrite(10,PL);*/

  if(PL < 0 && PR < 0){               //dozadu
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    analogWrite(3,abs(PL));

    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    analogWrite(10,abs(PR));
  }
  if(PL > 0 && PR > 0){               //dopredu
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    analogWrite(3,abs(PR));

    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    analogWrite(10,abs(PL));
  }
  if(PL > 0 && PR < 0){               //vpravo
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    analogWrite(3,abs(PR));

    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    analogWrite(10,abs(PL));
  }
  if(PL < 0 && PR > 0){               //vlevo
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    analogWrite(3,abs(PR));

    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    analogWrite(10,abs(PL));
  }
  if(PL == 0 && PR == 0){             //stop
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    analogWrite(3,0);

    digitalWrite(9,HIGH);
    digitalWrite(8,HIGH);
    analogWrite(10,0);
  }
}
/*void turnr(int PL, int PR) {
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  analogWrite(3,PR);

  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  analogWrite(10,PL);
}
void turnl(int PL, int PR) {
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  analogWrite(3,PR);

  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  analogWrite(10,PL);
}

void goback(int PLB, int PRB) {
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  analogWrite(3,PL);

  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  analogWrite(10,PR);
}
void stop() {
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  analogWrite(3,0);

  digitalWrite(9,HIGH);
  digitalWrite(8,HIGH);
  analogWrite(10,0);
}*/
void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);

  Serial.begin(9600);
  dalkoveOvl.enableIRIn();
}
void loop() {
  /*go(190, 255);
  delay(10000);
  stop();
  delay(1000);
  go(190, 255);
  delay(10000);  
  stop();
  delay(1000);
  bool cara = digitalRead(11);
  if(cara == 0){
    goback(90,90);
    delay(500);
    }
    else{
    go(90, 150);
    }
  Serial.println(cara);
  bool caral = !digitalRead(12);
  bool cara = !digitalRead(11);

  if(cara == 1){
    go(255,-75);
  } 
  else if(cara == 0){
    go(-75,255);
  }*/
  if (dalkoveOvl.decode(&vysledek)) {
    detekceKlaves();
    dalkoveOvl.resume();
  } 
  if (vysledek.value == 0xFF629D){
    go(255,255);}
  else if (vysledek.value == 0xFFA857){
    go(-255,-255);}
  else if (vysledek.value == 0xFFA857){
    go(-255,255);}
  else if (vysledek.value == 0xFFA857){
    go(255,-255);}
  else{
    go(0,0);
  } 
  switch(vysledek.value) {
    case 0xFF629D:  
      go(255,255);
      break;
    case 0xFFA857:  
      go(-255,-255);
      break;
    case 0xFF22DD:  
      go(-255,255);
      break;
    case 0x2FFC23D:  
      go(255,-255);
      break;
    default: 
      go(0,0);
  }
}

void detekceKlaves() {
  switch(vysledek.value) {
    case 0xFF629D:  
      Serial.println("Stisknuto dopredu");
      break;
    case 0xFFA857:  
      Serial.println("Stisknuto dozadu");
      break;
    case 0xFF22DD:  
      Serial.println("Stisknuto doleva");
      break;
    case 0x2FFC23D:  
      Serial.println("Stisknuto doprava");
      break;
    default: 
      Serial.println("Stisknuta jina klavesa");
  }
  delay(500);
}
