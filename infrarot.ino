
const int IR_LED_PIN = 13;
void setup(){
    Serial.begin(9600); 
    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);

}


void loop(){
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
     
}
