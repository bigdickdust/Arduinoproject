
//Variablen
long dauer=0;
long entfernung=0;

int ambient = 0;
int lit = 0;
int value = 0;
int fahren_start_zeit = 0;
int helligkeit;
  

//Pins
const int IR_INPUT_PIN = A0;
const int IR_LED_PIN = 13;
const int ECHO = 6;
const int TRIGGER = 7;

void setup() { 
    Serial.begin (9600);
    //Ultraschallsensor Setup 
    pinMode(TRIGGER, OUTPUT); 
    pinMode(ECHO, INPUT); 
  
    //IR Sensor Setup
    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);
} 
int messen (){  
    // Funktion gibt enfernung als int zurück        
    //Töne(Ultraschall) and und aus machen 
    digitalWrite(TRIGGER, LOW);
    delay(5);
    digitalWrite(TRIGGER, HIGH); 
    delay(10);
    digitalWrite(TRIGGER, LOW);
    dauer = pulseIn(ECHO, HIGH); 
    entfernung = long((dauer/2) * 0.03432); 
    if (entfernung >= 500 || entfernung <= 0) {
        //ungültiger Messbereich
        Serial.println("Kein Messwert"); 
    }
    else 
    {
      Serial.print(entfernung); 
      Serial.println(" cm"); 
    }

    return entfernung;
 }


int markierungErkennen() { 
    //liefert Wert für Helligkeit(schwarz => kleinerer Wert)
    digitalWrite(IR_LED_PIN, LOW);
    delay(5); 
    //misst umgebungshelligkeit                          
    ambient = analogRead(IR_INPUT_PIN);
  
    digitalWrite(IR_LED_PIN, HIGH);
    delay(5);
    lit = analogRead(IR_INPUT_PIN);
    //differenz zum Umgebungslicht berechnen
    value = lit - ambient;
    
    return value;
}



void fahren(int einschlag, int geschwindigkeit){              
    //Nicos code
}


void einparken(){ 
    //nur rückwärts links falls Zeit rückwärts rechts hinzufügen
    //Auto soll Lücke erkennen, vorbei fahren, dann rückwärts einparken 
    //delays müssen auf das getriebe abgestimmt werden => Tests
    helligkeit = markierungErkennen();
    while (helligkeit > 300){//Wert für schwarz muss noch ermittelt werden
        //fahren bis Parklücke erkannt
        fahren(0, 50);
    }
    //Parklücke gefunden
    fahren(0,0);
    delay(100);
    //an Parklücke vorbei fahren
    fahren(0,100);
    delay(2000);
    //rückwärts einparken
    entfernung = messen();
    fahren_start_zeit = millis();
    while(entfernung > 10 && (fahren_start_zeit - millis()) < 2000){// fährt für 2 sec oder bis 10 cm vor Wand Rückwärts links (Zeit bis gerade in Parklücke)
        fahren(-45, -40);
    }

    fahren(0,0);
    delay(100);

    //rückwärtsfahren bis ganz in Parklücke
    while (entfernung > 10){
        fahren(0, -40);
    }
}
void loop() {
