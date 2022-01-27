// Code from Gotronic
# include <SoftwareSerial.h>

#define rxPin 11 
#define txPin 10

void setup() {

    pinMode(rxPin,INPUT); 
    pinMode(txPin,OUTPUT);
    mySerial.begin(38400);
    Serial.begin(38400);
    
    

}

void loop() {
  int i =0; 
  char data[32] = {0};
  if(Serial.available()){
    do {
      data[i++] = Serial.read();
      delay(3);
    }while (Serial.available()>0);

    mySerial.println(data);
    Serial.println(data);
  }
  while (mySerial.available())
    }
    Serial.print((char)mySerial.read());
    }

}
