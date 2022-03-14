

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Le module bluetooth n est pas active! Revoir la configuration
#endif

BluetoothSerial ISEN_Bluetooth;

int led = 2;
char x;
String instruction ="";

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW); // On éteint la led par défaut
  Serial.begin(115200);
  ISEN_Bluetooth.begin("ESP32_ISEN_BT"); //nom de notre bluetooth
  Serial.println("Bluetooth active! amuse toi bien !!");

}

void loop() {
  // put your main code here, to run repeatedly:
  
//On vérifie si une donnée ou quelque chose est disponible sur le port série
  if(Serial.available())
  {
    Serial.print("EXTERNAL_DEVICE < ");
    while(Serial.available())
    {
      x = Serial.read();
      ISEN_Bluetooth.write(x);
      Serial.write(x);  
      
    }  

    Serial.println("");
    
  }

  if(ISEN_Bluetooth.available())
  {
    Serial.print("EXTERNAL_DEVICE > ");
    while(ISEN_Bluetooth.available())
    {
      x = ISEN_Bluetooth.read();
      Serial.write(x);
      instruction += x;
      
    }
  
    Serial.println("");
    
  }

//On vérifie la consigne reçue puis on exécute l'action correspndante
  
if(instruction == "on")
  {

    digitalWrite(led,HIGH);
  }
  else 
  {

    if(instruction == "off")
    {
  
      digitalWrite(led,LOW);
    }
      
  
  }
  
  instruction = "";

  delay(20);

}
