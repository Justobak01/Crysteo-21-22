/*****************************
 * CODE TO USE ISEN HOVERCRAFT
******************************
*/


#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define BACK_MOTOR_ESC_PIN 5
#define MIDDLE_MOTOR_ESC_PIN 6


RF24 radio(9, 10);   // nRF24L01 (CE, CSN)--- On Hovercraft CE and CSN are on 
//const byte address[6] = "00001"; //Hovercraft 1
const byte address[6] = "00002"; //Hovercraft 2
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
int levitation = 0;  // value from the analog pin
int DIRECTION_SERVO_MOTOR_PIN = A4 ;


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



Servo ESC_Motor_Back;     // create servo object to control the ESC
Servo ESC_Motor_Mid;     // create servo object to control the ESC
Servo Direction_Servo_Motor;



//useful fonctions for this project
void ESC_Calibration(int Moteur_Pin, Servo ESC_Moteur);
void resetData();
void NRF24_Receiver_Initialisation();

void setup() {

  //Send the communication speed
  Serial.begin(9600);

  //NRF24 Receiver Initialisation
  NRF24_Receiver_Initialisation();
  resetData(); //Reset Data to the default Values to prevent unexpected behavior before starting something

  // Attach the ESC_Motor_Back on pin 5 , ESC_Motor_Mid on pin 6 and servo motor on pin 8
  ESC_Motor_Back.attach(BACK_MOTOR_ESC_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC_Motor_Mid.attach(MIDDLE_MOTOR_ESC_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Direction_Servo_Motor.attach(DIRECTION_SERVO_MOTOR_PIN);
  
  // ESCs calibration
  //ESC_Calibration(BACK_MOTOR_ESC_PIN,ESC_Motor_Back);
  //delay(100);
  //ESC_Calibration(MIDDLE_MOTOR_ESC_PIN,ESC_Motor_Mid);
  //delay(100);

  //ESC_Motor_Back.write(0);    // Send the signal to the ESC
 // delay(3000);
  //ESC_Motor_Back.write(180);    // Send the signal to the ESC
  //delay(3000);

  ESC_Motor_Back.write(0);    // Send the signal to the ESC

//ESC_Calibration(MIDDLE_MOTOR_ESC_PIN,ESC_Motor_Mid);
  //ESC_Motor_Mid.write(0);    // Send the signal to the ESC
  //delay(3000);
  //ESC_Motor_Mid.write(180);    // Send the signal to the ESC
  //delay(3000);

  ESC_Motor_Mid.write(0);    // Send the signal to the ESC
  //Cut off the Motors by default
  
  
 
}



void loop() {

  
  // Check whether there is data to be received
  if (radio.available()) {
    //Serial.println("connected ");
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data

    ESC_Motor_Back.write(data.j1VRY);    // Send the signal to the ESC
  //if (data.j1VRY <= 180)
  //{
    //ESC_Motor_Back.write(data.j1VRY);    // Send the signal to the ESC

  //}

  Direction_Servo_Motor.write(data.j2VRX);


  if (levitation < 0)
  {
    levitation = 0;
    ESC_Motor_Mid.write(levitation);    // Send the signal to the ESC
    //levitation = map(data.j2Button, 0, 255, 180, 0);
  }


  if ((data.j1Button == 0) && levitation >= 0)
  {
    
    levitation += 10;
    ESC_Motor_Mid.write(levitation);    // Send the signal to the ESC
    //levitation = map(data.j1Button, 0, 255, 180, 0);
  }
  
  
    if ((data.j2Button == 0) && levitation >= 0)
  {
    levitation -= 10;
    ESC_Motor_Mid.write(levitation);    // Send the signal to the ESC
    //levitation = map(data.j2Button, 0, 255, 180, 0);
  }

   
  
  //ESC_Motor_Mid.write(levitation);    // Send the signal to the ESC
  


  // Print the data in the Serial Monitor
  Serial.println("j1VRX: ");
  Serial.println(data.j1VRX);
  Serial.println("; j1VRY: ");
  Serial.println(data.j1VRY);
  Serial.println("; j2Button: ");
  Serial.println(data.j2Button);
  Serial.println("; j1Button: ");
  Serial.println(data.j1Button);
  Serial.println("; levitation: ");
  Serial.println(levitation);
  //Serial.print("; button1: ");
  //Serial.print(data.button1);



  }

  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }

  

}

void ESC_Calibration(int Moteur_Pin, Servo ESC_Motor)
{

  ESC_Motor.write(0);    // Send the signal to the ESC
  delay(3000);
  ESC_Motor.write(180);    // Send the signal to the ESC
  delay(3000);
}

void NRF24_Receiver_Initialisation()
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

}

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1VRX = 93;
  data.j1VRY = 93;
  data.j2VRX = 25;
  data.j2VRY = 93;
  data.j1Button = 1;
  data.j2Button = 1;
}





/*************************
 * CALIBRATION ESC MOTORS
**************************
*/

/*
#include <Arduino.h>
#include <Servo.h>

#define BACK_MOTOR_ESC_PIN 5
#define MIDDLE_MOTOR_ESC_PIN 6
#define DIRECTION_SERVO_MOTOR_PIN 8

Servo ESC_Motor_Back;     // create servo object to control the ESC
Servo ESC_Motor_Mid;     // create servo object to control the ESC

void ESC_Calibration(int Moteur_Pin, Servo ESC_Motor);

void setup()
{

  ESC_Motor_Back.attach(BACK_MOTOR_ESC_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC_Motor_Mid.attach(MIDDLE_MOTOR_ESC_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

  //ESCs calibration
  ESC_Calibration(BACK_MOTOR_ESC_PIN,ESC_Motor_Back);
  //delay(100);
  //ESC_Calibration(MIDDLE_MOTOR_ESC_PIN,ESC_Motor_Mid);
  //delay(100);

  ESC_Motor_Back.write(0);    // Send the signal to the ESC
 // delay(3000);
  //ESC_Motor_Back.write(180);    // Send the signal to the ESC
  //delay(3000);

  //ESC_Motor_Back.write(0);    // Send the signal to the ESC

  ESC_Calibration(MIDDLE_MOTOR_ESC_PIN,ESC_Motor_Mid);
  //ESC_Motor_Mid.write(0);    // Send the signal to the ESC
  //delay(3000);
  //ESC_Motor_Mid.write(180);    // Send the signal to the ESC
  //delay(3000);

  ESC_Motor_Mid.write(0);    // Send the signal to the ESC
  //Cut off the Motors by default


  //ESC_Motor_Back.write(0);    // Send the signal to the ESC
  //delay(3000);
  //ESC_Motor_Back.write(180);    // Send the signal to the ESC
  //delay(3000);

  //ESC_Motor_Back.write(0); 

  //ESC_Motor_Mid.write(0);    // Send the signal to the ESC
  //delay(3000);
  //ESC_Motor_Mid.write(180);    // Send the signal to the ESC
  //delay(3000);

  //ESC_Motor_Mid.write(0); 

}


void loop()
{

  ESC_Motor_Back.write(20); 
  ESC_Motor_Mid.write(20); 



}

void ESC_Calibration(int Moteur_Pin, Servo ESC_Motor)
{

  ESC_Motor.write(0);    // Send the signal to the ESC
  delay(3000);
  ESC_Motor.write(180);    // Send the signal to the ESC
  delay(3000);
}


*/
