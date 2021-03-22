
int trigger=7;
int echo=6;
long dauer=0;
long entfernung=0;

const int IR_INPUT_PIN = A0;
const int IR_LED_PIN = 13;

 void setup() {
    Serial.begin (9600); 
    pinMode(trigger, OUTPUT); 
    pinMode(echo, INPUT); 
  
    Serial.begin(9600); 
    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);
} 
 int messen (){ 
   digitalWrite(trigger, LOW);
   delay(5);
    digitalWrite(trigger, HIGH); 
    delay(10);
    digitalWrite(trigger, LOW);
    dauer = pulseIn(echo, HIGH); 
    entfernung = (dauer/2) * 0.03432; 
    if (entfernung >= 500 || entfernung <= 0) {
        Serial.println("Kein Messwert"); 
    }
    else 
    {
      Serial.print(entfernung); 
      Serial.println(" cm"); 
    }
     delay(1000);

    return entfernung;
 }

 void loop()
 { 
  messen();
    int ambient = 0;
    int lit = 0;
    int value = 0;
  
     digitalWrite(IR_LED_PIN, LOW);
     delay(5);                           
     ambient = analogRead(IR_INPUT_PIN);
  
     digitalWrite(IR_LED_PIN, HIGH);
     delay(5);
     lit = analogRead(IR_INPUT_PIN);
  
     value = lit - ambient;
  
     Serial.println(value);
     delay(500);
}


void initRPR220(int ledPin, int detectorPin){
  
     pinMode(detectorPin, INPUT);
     pinMode(ledPin, OUTPUT);
}

int readRPR220(int ledPin, int detectorPin){
    int val = 0;
  
     digitalWrite(ledPin, LOW);
     delay(5);
     val = analogRead(detectorPin);
  
     digitalWrite(ledPin, HIGH);
     delay(5);
     val = analogRead(detectorPin) - val;
     return 9000/(val - 12);
     
} void fahren(){              Nicos code 
 
 
}
void einparken(){ 
  
 
 
Lenkeinschlag(-45 - 45); 
 
 
 
 
