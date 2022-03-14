
#include "WiFi.h"

const char* ssid = "ISEN-ESP32-AP";
const char* password = "toto12345";


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  //Configuration du point d'accès
  Serial.println("Config AP (Access Point)…");
  // Retirer le paramètere du password si on veut que le point d'accès (AP) soit ouvert à tous.
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP(); //On déclare un objet de type IPAddress pour contenir l'adredsse IP de notre point d'accès
  Serial.print("Adresse IP: ");
  Serial.println(IP);

  // A cette étape le point d'accès est en marche et visible en tant que réseau WiFi
 

}

void loop() {
  // put your main code here, to run repeatedly:

}
