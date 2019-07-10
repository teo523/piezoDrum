

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); 
byte resetMIDI = 4;

#define CTRLCHANNEL 0xB0
#define CTRLINSTRUMENT 0xC0
#define CTRLON 0x09
#define CTRLOFF 0x08
#define SETVOLUME 0x07

//SOUND BANKS LOCATIONS
#define BNKPERCUSSION 0x78
#define BNKMELODY 0x79



int piezoPin0, piezoPin1, piezoPin2, piezoPin3, piezoVal0, piezoVal1, piezoVal2, piezoVal3;
int threshold, vel0, vel1, vel2, vel3;
long currentTime0, currentTime1,currentTime2, currentTime3;
bool aux0,aux1,aux2,aux3;



void setup() {
  //MIDI.begin();
  Serial.begin(57600);
  mySerial.begin(31250);
  //Reset the chip (vs1053)
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
 

  piezoPin0  = A0;
  piezoPin1 = A1;
  piezoPin2  = A2;
  piezoPin3  = A3;
  
  threshold = 10;
  aux0 = true;
  aux1 = true;
  aux2 = true;
  aux3 = true;
  talkMIDI(CTRLCHANNEL, 0, BNKPERCUSSION);
  talkMIDI(CTRLINSTRUMENT, 100,0);
  
}

void loop() {
  piezoVal0 = 0;
  piezoVal1 = 0;
  piezoVal2 = 0;
  piezoVal3 = 0;

  for (int i=0;i<8;i++){
  piezoVal0 = piezoVal0 + analogRead(piezoPin0);
  piezoVal1 = piezoVal1 + analogRead(piezoPin1);
  piezoVal2 = piezoVal2 + analogRead(piezoPin2);
  piezoVal3 = piezoVal3 + analogRead(piezoPin3);}

  piezoVal0 = piezoVal0 / 8;
  piezoVal1 = piezoVal1 / 8;
  piezoVal2 = piezoVal2 / 8;
  piezoVal3 = piezoVal3 / 8;
  
  vel0 = map(piezoVal0, 10, 700, 20, 127);
  vel1 = map(piezoVal1, 10, 700, 20, 127);
  vel2 = map(piezoVal2, 10, 700, 20, 127);
  vel3 = map(piezoVal3, 10, 700, 20, 127);
  
  
//  if(piezoVal0>threshold and aux0 == true){
//    noteOn(0, 36, vel0);
//    aux0=false;
//    currentTime0 = millis();
//  }
//
//    if(piezoVal1>threshold and aux1 == true){
//    noteOn(0, 38, vel1);
//    aux1=false;
//    currentTime1 = millis();
//  }
//  
//if(piezoVal2>threshold and aux2 == true){
//    noteOn(0, 40, vel2);
//    aux2=false;
//    currentTime2 = millis();
//  }
  
if(piezoVal3>threshold and aux3 == true){
  noteOn(0, 42, vel3);
    aux3=false;
    currentTime3 = millis();
  }

//if (int (millis() - currentTime0) > 100.0 and aux0 == false) {
//  aux0 = true;
//  //MIDI.sendNoteOff(42, 0, 10);
//  noteOff(0, 36, 0);
//  }
//
// if (int (millis() - currentTime1) > 100.0 and aux1 == false) {
//  aux1 = true;
//  //MIDI.sendNoteOff(42, 0, 10);
//  noteOff(0, 38, 0);
//  }
//
//if (int (millis() - currentTime2) > 100.0 and aux2 == false) {
//  aux2 = true;
//  //MIDI.sendNoteOff(38, 0, 10);
//  noteOff(0, 40, 0);
//  }

if (int (millis() - currentTime3) > 100.0 and aux3 == false) {
  aux3 = true;
  //MIDI.sendNoteOff(36, 0, 10);
  noteOff(0, 42, 0);
  }

  
}

void noteOn(byte channel, byte note, byte attack_velocity) 
{
  talkMIDI( (0x90 | channel), note, attack_velocity);
}
//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) 
{
  talkMIDI( (0x80 | channel), note, release_velocity);
}
//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2)
{
  mySerial.write(cmd);
  mySerial.write(data1);
  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);
}
