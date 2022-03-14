

int led = 2;
int potentiometre = 15;
int analog_value;
int luminosite;
#include <Arduino.h>



void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  analog_value = analogRead(potentiometre);
  Serial.println("valeur");
  Serial.println(analog_value);
  
  /* contrôle de la luminosité de la led*/
  
  //l'idéal aurait été d'utiliser la fonction analogWrite 
  //à la place de la fonction digitalWrite.
  //mais cette dernière n'a pas été développée sur ESP32
  
  //luminosite = map (analog_value,0,4095,0,255);
  //digitalWrite(led,luminosite);
  
  delay(100);
  

}
