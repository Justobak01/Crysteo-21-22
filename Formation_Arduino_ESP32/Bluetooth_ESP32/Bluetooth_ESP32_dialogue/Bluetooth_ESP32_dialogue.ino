

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Le module bluetooth n est pas active! Revoir la configuration
#endif

BluetoothSerial ISEN_Bluetooth;

char x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ISEN_Bluetooth.begin("ESP32_ISEN_BT"); //nom de notre bluetooth
  Serial.println("Bluetooth active! amuse toi bien !!");

}

void loop() {
  // put your main code here, to run repeatedly:

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
      Serial.write(ISEN_Bluetooth.read());
    }
    
    Serial.println("");
    
  }

  delay(20);

}
