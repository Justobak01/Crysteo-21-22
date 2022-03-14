int bouton = 22; 
int led = 2;
int etat_bouton = 0;



void setup() { 

  

  pinMode(led, OUTPUT); 

  pinMode(bouton, INPUT_PULLUP); 

  digitalWrite(led,LOW);



} 

 



void loop() { 

  etat_bouton = digitalRead(bouton); 

  //Serial.write(bouton); 

  if (etat_bouton ==0){ 



    digitalWrite(led, HIGH);   


  } 

  else{ 

    digitalWrite(21, LOW);    

  } 

} 
