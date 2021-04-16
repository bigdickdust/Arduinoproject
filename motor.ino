
int trigger=7;
int echo=6;
long dauer=0;
long entfernung=0; 
int motorPin1=2;
int motorPin2=3;
const int abstand_linie_auto = 500;
int entfernung_links = 0;
int entfernung_rechts = 0;

const int IR_INPUT_PIN = A0;
const int IR_LED_PIN = 13;

 void setup() { //Ultraschallsensor misst entfernungen 
    Serial.begin (9600); 
    pinMode(trigger, OUTPUT); 
    pinMode(echo, INPUT); 
  
    Serial.begin(9600); 
    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);
    pinMode(motorPin1,OUTPUT);
    pinMode(motorPin2,OUTPUT);
} 
 int messen (){         //Töne and und aus machen 
   digitalWrite(trigger, LOW);
   delay(5);
    digitalWrite(trigger, HIGH); 
    delay(10);
    digitalWrite(trigger, LOW);
    dauer = pulseIn(echo, HIGH); 
    entfernung = (dauer/2) * 0.03432; 
    if (0 < entfernung < abstand_linie_auto ) {
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

 void loop() //ADC und LED Übergang im Übergang 
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
  
     pinMode(detectorPin, INPUT);  //schwarze Materialien unterscheiden können von hellen 
     pinMode(ledPin, OUTPUT);
}

int readRPR220(int ledPin, int detectorPin){ //gibt linearisierten Abstand an RPR an die Pins zurück 
    int val = 0;
  
     digitalWrite(ledPin, LOW);
     delay(5);
     val = analogRead(detectorPin);
  
     digitalWrite(ledPin, HIGH);
     delay(5);
     val = analogRead(detectorPin) - val;
     return 9000/(val - 12);
     
} void fahren(int einschlag, int geschwindigkeit){              //Nicos code 
 
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  delay(500);
}


  void motorStop(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  delay(500);
  









 
}
 

void einparken(){ //Auto soll Lücke erkennen, vorbei fahren, dann rückwärts einparken 
  
  digitalWrite(motorPin1,HIGH);   // Motor Vor
  digitalWrite(motorPin2,LOW);
  delay(1000);

  motorStop();                    // Motor Stop
 
   if (500 > entfernung > 0 ) {
        Serial.println("Kein Messwert"); 
    }
    else 
    {
      Serial.print(entfernung); 
      Serial.println(" cm"); 
    }
     delay(10000);
 
 fahren(-45, -20);       //Rückwärts fahren links einschlagen 

  digitalWrite(motorPin1,LOW);    // Motor Rueck
  digitalWrite(motorPin2,HIGH);
  delay(1000);

  motorStop();                    // Motor Stop


 if (entfernung_links == 500 &&  entfernung_rechts == 500 ) {
        Serial.println("Kein Messwert"); 
    }
    else 
    {
      Serial.print(entfernung); 
      Serial.println(" cm"); 
    }
     delay(1000);
fahren(0, -20);   //rückwarts gerade fahren 

 digitalWrite(motorPin1, LOW);   // Motor langsam zu schnell
  for (int i=0; i<255; i++){
    analogWrite(motorPin2, i);
    delay(20);
  }
  motorStop();                    // Motor Stop


if (entfernung >= 0|| entfernung <= 0 ) {
        Serial.println("Kein Messwert"); 
}
    else 
    {
      Serial.print(entfernung);                   //Anhalten, stehen 
      Serial.println(" cm"); 
    }
     delay(1000);
fahren(0, 0);}
