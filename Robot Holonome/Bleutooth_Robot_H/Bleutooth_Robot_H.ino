#include<SoftwareSerial.h>
SoftwareSerial bluetooth(12,13); //Rx, Tx




char val='0';
int vitesse=255; 
  bool  sens=true;







//const int codeur_pinA=5; //Fil Vert du moteur correspondant à la piste A du codeur relatif (C1)
//const int codeur_pinB=6;  //Fil jaune du moteur correspondant à la piste B du codeur relatif (C2)

//MOTEUR 3
const int retour_codeurs_M3 = 5;
const byte enable_m3=4;  //fil violet 
const byte pin1_MCC_m3=22; //fil blanc du moteur (M2)
const byte pin2_MCC_m3=3;  //fil rouge du moteur (M1)

//MOTEUR 1
const int retour_codeurs_M1 = 6;
const byte enable_m1=7;  //fil violet 
const byte pin1_MCC_m1=8; //fil blanc du moteur (M2)
const byte pin2_MCC_m1=9;  //fil rouge du moteur (M1)


//MOTEUR 0
const int retour_codeurs_M0 = 10;
const byte enable_m0=48;  //fil violet 
const byte pin1_MCC_m0=53; //fil blanc du moteur (M2)
const byte pin2_MCC_m0=52;  //fil rouge du moteur (M1)


//MOTEUR 2
const int retour_codeurs_M2 = 11;
const byte enable_m2=49;  //fil violet 
const byte pin1_MCC_m2=51; //fil blanc du moteur (M2)
const byte pin2_MCC_m2=50;  //fil rouge du moteur (M1)


void commande_moteur(byte enable, byte pin1_MCC, byte pin2_MCC,bool sens,byte vitesse)
{
      // la fonction commande_moteur prend en argument:
      //    - enable : le numéro de la pin du uc branchée à la pin ENA du driver moteur
      //    - pin1_MCC : le numéro de la pin du uc branchée à la pin in1 du driver moteur
      //    - pin2_MCC : le numéro de la pin du uc branchée à la pin in2 du driver moteur
      //    - sens : à mettre à false ou true pour choisir le sens de rotation du moteur
      //    (true :sens des aiguilles d'une montre et false l'inverse)
      //    - vitesse : à régler entre 0 et 255 selon la vitesse de rotation voulue (0 étant une vitesse nulle)
      // A partir de ces arguments la fonction commande le moteur en rotation grâce à une tension PWM
      
      byte pin_moteur_a_commander;
      if (sens)
      {
            pin_moteur_a_commander=pin1_MCC;
            digitalWrite(pin2_MCC,LOW);
      }
      else
      {
            pin_moteur_a_commander=pin2_MCC;
            digitalWrite(pin1_MCC,LOW);
      }
      if (vitesse==0)
      {
           digitalWrite(enable,LOW);
      }
      else
      {
           digitalWrite(enable,HIGH);
           analogWrite(pin_moteur_a_commander,vitesse);       
      }
}



void setup(void)
{
  bluetooth.begin(9600);
    Serial.begin(9600);  //démarrage de la communication série (pour utiliser la console)
    while (!Serial) 
    {
       ; // attend que le port serie soit connecté.
    }
    Serial.print("La communication serie est prete\n\n");  //Lorsque la communication serie est prete affichage d'un message
    delay(500);
    
    
    


}


void loop(void)
{

  if(bluetooth.available())
  { 
  val=bluetooth.read();
  Serial.write(val);

 switch(val)
 {

   case 'F' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,true,vitesse);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,true,vitesse);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,true,vitesse);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,true,vitesse);

  break;

  case 'G' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,false,vitesse);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,false,vitesse);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,false,vitesse);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,false,vitesse);

  break;

  case 'S' : 
  
      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,sens,0);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,sens,0);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,sens,0);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,sens,0);
  
  break;

  case 'R' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,true,vitesse);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,false,vitesse);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,false,vitesse);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,true,vitesse);

  break;

  case 'L' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,false,vitesse);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,true,vitesse);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,true,vitesse);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,false,vitesse);

  break;


  case 'E' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,true,0);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,true,0);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,true,vitesse);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,true,vitesse);

  break;

  case 'Q' : 

      commande_moteur(enable_m3,pin1_MCC_m3,pin2_MCC_m3,true,vitesse);
      commande_moteur(enable_m1,pin1_MCC_m1,pin2_MCC_m1,true,vitesse);
      commande_moteur(enable_m2,pin1_MCC_m2,pin2_MCC_m2,true,0);
      commande_moteur(enable_m0,pin1_MCC_m0,pin2_MCC_m0,true,0);

  break;

  case 'Y' : 
      
       vitesse += 25;

        if (vitesse > 255)
        {

          vitesse = 255;
        }else {

           
        }
      Serial.println(vitesse);
      

  break;

  case 'X' : 

       vitesse -= 25;

      if (vitesse < 105)
      {
        vitesse = 105;
      }
      else 
      {
          
        
        }

        Serial.println(vitesse);
      

  break;



  default : 


    break;
  
  
 }
  
}



  
}
