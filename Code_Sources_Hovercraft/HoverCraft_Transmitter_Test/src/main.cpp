
/********************
** Potentiometer Test
********************* 
*/

/*
#include <Arduino.h>
#include <Servo.h>

int j1VRX = A7;
int j1VRY = A6;
int j2VRX = A5;
int j2VRY = A4;
int test = 0;
Servo servo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(A3);
  Serial.println("HoverCraft transmitter Test");
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("map values");
Serial.println(map(analogRead(j2VRX), 0,1023,50,150));
test = map(analogRead(j2VRX), 0,1023,50,150);
servo.write(test);

//Serial.println("No map values");
//Serial.println(analogRead(VRX));
delay(50);

}

*/





/********************
** Transmitter Test
*********************
*/


#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Define the digital inputs
#define jB1 8  // Joystick button 1
#define jB2 7  // Joystick button 1

RF24 radio(9, 10);   // nRF24L01 (CE, CSN)
//const byte address[6] = "00001"; //Hovercraft 1
const byte address[6] = "00002"; //Hovercraft 2
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  int j1VRX;
  int j1VRY;
  int j1Button;
  int j2VRX;
  int j2VRY;
  int j2Button;
};

Data_Package data; //Create a variable with the above structure



void setup() {
  Serial.begin(9600);
  // Define the radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  
  // Activate the Arduino internal pull-up resistors
  pinMode(jB1, INPUT_PULLUP);
  pinMode(jB2, INPUT_PULLUP);  
  // Set initial default values
  data.j1VRX = 93; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  data.j1VRY = 93;
  data.j2VRX = 101; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  data.j2VRY = 93;
}
void loop() {

  // Read all analog inputs and map them to one Byte value
  data.j1VRX = map(analogRead(A7), 0, 1023, 180, 0); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  data.j1VRY = map(analogRead(A6), 0, 1023, 180, 0);
  data.j2VRX = map(analogRead(A5), 0, 1023, 150, 50);
  data.j2VRY = map(analogRead(A4), 0, 1023, 180, 0);
  
  //On J1VRY when the jostick in on the middle we only needs the  uppers values from joystick
  data.j1VRY = constrain(data.j1VRY,93,180);
  data.j1VRY = map(data.j1VRY,93, 180, 0, 180);
  

  //if (data.j1VRX <= 93)
  //{
    //data.j1VRX = 0;

  //}

  //if (data.j1VRY <= 93)
  //{
    //data.j1VRY = 0;

  //}

  //if (data.j2VRX >= 23 && <= 26)
  //{
    //data.j2VRX = 25;

 // }

  //if (data.j2VRY <= 127)
  //{
    //data.j2VRY = 0;

  //}
  
  // Read all digital inputs
  data.j1Button = digitalRead(jB1);
  data.j2Button = digitalRead(jB2);

  Serial.print("J1VRX:");
  Serial.println(data.j1VRX);

  Serial.print("J1VRY:");
  Serial.println(data.j1VRY);

  Serial.print("J2VRX:");
  Serial.println(data.j2VRX);

  Serial.print("J2VRY:");
  Serial.println(data.j2VRY);

  Serial.print("J1Button:");
  Serial.println(data.j1Button);

  Serial.print("J2Button:");
  Serial.println(data.j2Button);
  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));
}



/***************
 * Receiver Test
****************
*/
/*
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte j1VRX;
  byte j1VRY;
  byte j1Button;
};
Data_Package data; //Create a variable with the above structure

void resetData();


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
}
void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    Serial.println("connected ");
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }
  // Print the data in the Serial Monitor
  Serial.println("j1PotX: ");
  Serial.println(data.j1VRX);
  Serial.println("; j1PotY: ");
  Serial.println(data.j1VRY);
  //Serial.print("; button1: ");
  //Serial.print(data.button1);
}
void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1VRX = 127;
  data.j1VRY = 127;
  data.j1Button = 1;
}

*/