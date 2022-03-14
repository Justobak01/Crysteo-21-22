
#include "WiFi.h"

const char* ssid = "ISEN-ESP32-AP";
const char* password = "toto12345";

int led = 2;
String etat_led = "off";

// Variable to store the HTTP request
String header;

//On crée notre server et on le fait opérer sur le port 80
WiFiServer Crysteo_IoT_server (80);
 WiFiClient client;


void web_server_html_page(WiFiClient client)
{

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // Style CSS  des boutons à l'état on/off 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Page Web vue par le client
            client.println("<body><h1>Crysteo IoT Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 2 - etat : " + etat_led + "</p>");
            // If the output26State is off, it displays the ON button       
            if (etat_led =="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            client.println("</body></html>");
  
}

void web_page_request(String header)
{

            // mettre la led à on ou off
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              etat_led = "on";
              digitalWrite(led, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              etat_led = "off";
              digitalWrite(led, LOW);
            } 

  
}


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);

  //COnfiguration du point d'accès
  Serial.println("Config AP (Access Point)…");
  
  // On peut retirer le paramètere du password si on veut que le point d'accès (AP) soit ouvert à tous.
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP(); //On déclare un objet de type IPAddress pour contenir l'adredsse IP de notre point d'accès
  Serial.print("Adresse IP: ");
  Serial.println(IP);

  // A cette étape le point d'accès est en marche et visible en tant que réseau WiFi
 
 //On met maintenant en marche le server Web vers lequel notre AP nous renverra chaque fois qu'on saisira son adresse IP
 Crysteo_IoT_server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
 client = Crysteo_IoT_server.available();   // Listen for incoming clients

  if (client) {                             // si un client est connecté
    Serial.println("Nouveau Client.");          // on affiche le message "client connecté dans le moniteur"
    String currentLine = "";                // on crée une chaîne de caractère pour stoquer les informations d'identification du client
    while (client.connected()) 
    {
      if (client.available()) {             // s'il y a quelque chose à lire du client
        char c = client.read();             // on fait alors une lecture bit par bit
        Serial.write(c);                    // on affiche cette info sur le moniteur série
        header += c;                        //on recupère le paquet de données renvoyé par le client
        
        if (c == '\n') {   
        if (currentLine.length() == 0) {

            web_page_request(header); // on fait une lecture des requêtes ou demandes du client contenenues dans le paquet reçu si elles existent

            web_server_html_page(client); // on renvoi au client la page HTML avec laquelle il est sensé interragir
             
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
        }else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
            
            
} else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
          
    }

  }

//A cette étape ci, nous sommes en fin/rupture de connexion avec le client
//on libère le client et on vide la variable de paquet
 
 // Clear the header variable
 header = "";

    // On ferme la connection
    client.stop();
    Serial.println("Client disconnecté.");
    Serial.println("");
  }



}
