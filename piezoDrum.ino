
#include<MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

int piezoPin, piezoPin2, piezoPin3, piezoVal, piezoVal2, piezoVal3;
int threshold, vel, vel2, vel3;
long currentTime1,currentTime2, currentTime3;
bool aux1,aux2,aux3;



void setup() {
  MIDI.begin();
  Serial.begin(115200);

  piezoPin  = A5;
  piezoPin2  = A2;
  piezoPin3  = A1;
  threshold = 20;
  aux1 = true;
  aux2 = true;
  aux3 = true;
}

void loop() {
  piezoVal = analogRead(piezoPin);
  piezoVal2 = analogRead(piezoPin2);
  piezoVal3 = analogRead(piezoPin3);
  vel = map(piezoVal, 0, 1000, 1, 127);
  vel2 = map(piezoVal2, 0, 1000, 1, 127);
  vel3 = map(piezoVal3, 0, 1000, 1, 127);
  
  
  if(piezoVal>threshold and aux1 == true){
    MIDI.sendNoteOn(42, vel, 10);
    aux1=false;
    currentTime1 = millis();
  }


  
if(piezoVal2>threshold and aux2 == true){
    MIDI.sendNoteOn(38, vel2+30, 12);
    aux2=false;
    currentTime2 = millis();
  }
  
if(piezoVal3>threshold and aux3 == true){
  MIDI.sendNoteOn(36, vel2+30, 12);
    aux3=false;
    currentTime3 = millis();
  }

if (int (millis() - currentTime1) > 100.0 and aux1 == false) {
  aux1 = true;
  MIDI.sendNoteOff(42, 0, 10);
  }

if (int (millis() - currentTime2) > 100.0 and aux2 == false) {
  aux2 = true;
  MIDI.sendNoteOff(38, 0, 10);
  
  }

if (int (millis() - currentTime3) > 100.0 and aux3 == false) {
  aux3 = true;
  MIDI.sendNoteOff(36, 0, 10);
  }

  
}
