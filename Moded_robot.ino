//initialisation des pins des différents composants

//ultrason
#define echo A2    //Echo pin
#define trigger A3 //Trigger pin

//buzzer
#define buzzer 12 //buzzer pin 12


int distance,distance_F = 30;

int set = 10; //La distance limite qu'on doit fixer 




//Moteur_droite
const int motA_pin1=8;              
const int motA_pin2=9;
const int motA_EN=10; 


//Moteur_gauche
const int motD_pin1=7;             
const int motD_pin2=6;
const int motD_EN=5; 

//capteurs_infrarouges
bool etatCapteurGauche;
bool etatCapteurCentre;
bool etatCapteurDroit;

const int capteurGauche=4;
const int capteurCentre=7;
const int capteurDroit=11;

//vitesse de rotation de moteur 
char speed=250; 

//commande bluetooth
int command=0;



void setup() {
  //initialisation des types des pins
  //input=entrée;output=sortie
  Serial.begin(9600);

pinMode (motA_pin1,OUTPUT);      
pinMode (motA_pin2,OUTPUT);
pinMode (motA_EN,OUTPUT);



pinMode (motD_pin1,OUTPUT);
pinMode (motD_pin2,OUTPUT);
pinMode (motD_EN,OUTPUT);


pinMode(capteurGauche, INPUT);
pinMode(capteurCentre, INPUT);
pinMode(capteurDroit, INPUT);



pinMode(echo, INPUT );
pinMode(trigger, OUTPUT);   
pinMode(buzzer, OUTPUT); 
 
}

// fonction Calcul du distance de l'ultrason

long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echo, HIGH);
  return distance / 29 / 2;
}

// Avant 

void FWD() {
digitalWrite(motA_pin1,LOW);
digitalWrite(motA_pin2,HIGH);
 analogWrite(motA_EN,speed); 
 


 digitalWrite(motD_pin1,LOW);
digitalWrite(motD_pin2,HIGH);
 analogWrite(motD_EN,speed); 

}
// Gauche 

void LEFT() {

 analogWrite(motA_EN,speed);
digitalWrite(motA_pin1,LOW);
digitalWrite(motA_pin2,HIGH);


 digitalWrite(motD_pin1,HIGH);
digitalWrite(motD_pin2,LOW);
 analogWrite(motD_EN,speed); 

}
// Droite
void RIGHT() {
analogWrite(motA_EN,speed);
digitalWrite(motA_pin1,HIGH);
digitalWrite(motA_pin2,LOW);


 digitalWrite(motD_pin1,LOW);
digitalWrite(motD_pin2,HIGH);
 analogWrite(motD_EN,speed); 
 
}

//Arrière

void REV() {
digitalWrite(motA_pin1,HIGH);
digitalWrite(motA_pin2,LOW);
analogWrite(motA_EN,speed);



 digitalWrite(motD_pin1,HIGH);
digitalWrite(motD_pin2,LOW);
 analogWrite(motD_EN,speed); 

}

//Arret

void STOP(){
analogWrite(motA_EN,0);
digitalWrite(motA_pin1,LOW);
digitalWrite(motA_pin2,LOW);

 digitalWrite(motD_pin1,LOW);
digitalWrite(motD_pin2,LOW);
 analogWrite(motD_EN,0); 

}

// Mode Suiveur de ligne

void suiveur(){
  distance_F = Ultrasonic_read(); // Appel a la fonction Ultrasonic_read() 

  etatCapteurGauche = digitalRead(capteurGauche);//lecture des données du capteur gauche 

  etatCapteurDroit = digitalRead(capteurDroit);//lecture des données du capteur droite 

if (distance_F > set) {
    if ((etatCapteurGauche) && (!etatCapteurDroit)) {
      LEFT();
      }
    else if ((!etatCapteurGauche) && (etatCapteurDroit)) {
      RIGHT();
      }
    else if ((etatCapteurGauche) && (etatCapteurDroit))
      FWD();
     else STOP();}

else{digitalWrite(buzzer, HIGH); //activation du buzzer

      delay(500);
      digitalWrite(buzzer, LOW);//Desactivation du buzzer
      STOP();
}


}

void loop() {

  
//Déclaration des boutons de l'application bluetooth et leur liaison avec les fonctions définies ci-dessus

  if (Serial.available()>0){
    command=Serial.read();
while (command ==88) {
suiveur(); 


}


if ( command==70)  
FWD(); 
else if ( command==82)
RIGHT();
else if ( command==76)
LEFT();
else if ( command==66)
REV();

else 
STOP();
  }

}   
