

int led_rouge = 3;
int led_verte = 4;
int led_orange = 5;



void setup() {
  // put your setup code here, to run once:
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(led_orange, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(led_rouge,HIGH);
  delay(3000);
  digitalWrite(led_rouge,LOW);
  digitalWrite(led_orange,HIGH);
  delay(2000);
  digitalWrite(led_orange,LOW);
  digitalWrite(led_verte,HIGH);
  delay(3000);
  digitalWrite(led_verte,LOW);

}
