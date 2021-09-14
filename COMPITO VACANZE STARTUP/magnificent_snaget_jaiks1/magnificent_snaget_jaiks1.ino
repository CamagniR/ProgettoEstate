#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define echoIn 9
#define triggerIn 10

#define echoOut 6
#define triggerOut 7

#define VELOCITASUONO 343.1
#define VARIAZIONE 1

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Numero persone");
  lcd.setCursor(0,1);
  lcd.print("0");
  Serial.begin(9600);
  pinMode(echoIn,INPUT);
  pinMode(echoOut,INPUT);
  pinMode(triggerIn,OUTPUT);
  pinMode(triggerOut,OUTPUT);
  
}

double distInPrec = misuraDistanza(echoIn, triggerIn);//variabile che contiene il valore dell'ultima distanza misurata sul sensore posto all'ingresso
double distOutPrec = misuraDistanza(echoOut, triggerOut);//variabile che contiene il valore dell'ultima distanza misurata sul sensore posto all'uscita
int numeroPersonePresenti = 0;//numero persone presenti nel locale
bool sensoreAttivatoIn = false;
bool sensoreAttivatoOut = false;

void loop() {
  float misuraDistanzaIn = misuraDistanza(echoIn, triggerIn);
  if(sensoreAttivatoIn == false){
    if(misuraDistanzaIn < VARIAZIONE){
     sensoreAttivatoIn = true; 
     numeroPersonePresenti++;
     lcd.setCursor(0,1);
      lcd.print(numeroPersonePresenti);
      lcd.print("           ");
    }
  }
  else{
     if(misuraDistanzaIn > VARIAZIONE){
     sensoreAttivatoIn = false; 
    }
  }
  
  float misuraDistanzaOut = misuraDistanza(echoOut, triggerOut);
  if(sensoreAttivatoOut == false){
    if(misuraDistanzaOut < VARIAZIONE && numeroPersonePresenti > 0){
     sensoreAttivatoOut = true; 
     numeroPersonePresenti--;
     lcd.setCursor(0,1);
      lcd.print(numeroPersonePresenti);
      lcd.print("           ");
    }
  }
  else{
     if(misuraDistanzaOut > VARIAZIONE){
     sensoreAttivatoOut = false; 
    }
  }
}

double misuraDistanza(int _ECHO, int _TRIGGER){//funzione per misuarare la distanza passando come parametri 
  digitalWrite(_TRIGGER,LOW);
  digitalWrite(_TRIGGER,HIGH);
  delayMicroseconds(10);
  digitalWrite(_TRIGGER,LOW);
  
  double durata = pulseIn(_ECHO,HIGH);//quanto tempo passa da quando _ECHO diventa HIGH per ritornare a valore LOW
  double durataSecondi = durata/2.0/1000000.0;//si divide per 2 perchè altrimenti si conterebbe sia l'andata che il ritorno dell'onda
  double distanza = (durataSecondi*VELOCITASUONO); 
  return distanza;
}

