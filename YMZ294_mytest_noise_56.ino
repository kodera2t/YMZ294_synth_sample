// YMZ294 tiny primitive synthesizer sample
// space missile launch?
// Kodera2t, Mar.21, 2019
#include <YMZ294.h>

// Output Pins
const byte WRCS_PIN = 8;
const byte A0_PIN = 9;
const byte RESET_PIN = 10;

YMZ294 ymz(WRCS_PIN, A0_PIN, RESET_PIN);

void setup() {
  DDRD = 0b11111111;
  pinMode(WRCS_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
  ymz.Reset();
}


void loop() {
boolean sw1, sw2, sw3, sw4;
  sw1=digitalRead(11);
  sw2=digitalRead(12);
  sw3=digitalRead(13);
  sw4=digitalRead(A0);
  if(sw1==0){
  allon();
  for(int i=500;i>0;i=i-2){
    ymz.SetFrequency(CH_A,i);
    ymz.SetFrequency(CH_B,i/2);
    ymz.SetFreqBit(CH_C,i/4);    
  }
  allzero();  
  }
  if(sw2==0){
  allon();
  for(int i=0;i<500;i=i+2){
    ymz.SetFrequency(CH_A,i);
    ymz.SetFrequency(CH_B,i/2);
    ymz.SetFreqBit(CH_C,i/4);    
  }
  allzero();
  }
  if(sw3==0){
  allon();
  for(int i=0;i<500;i=i+1){
    ymz.SetFrequency(CH_A,i);
    ymz.SetFrequency(CH_B,i/2);
    ymz.SetFreqBit(CH_C,i/4);    
  }
  allzero();  
  }
  if(sw4==0){
  allon();
  for(int i=500;i>0;i=i-1){
    ymz.SetFrequency(CH_A,i);
    ymz.SetFrequency(CH_B,i/2);
    ymz.SetFreqBit(CH_C,i/4);    
  }
  allzero();  
  }  
}

void allzero(){
  ymz.SetVolume(CH_A, 0);  
  ymz.SetVolume(CH_B, 0);
  ymz.SetVolume(CH_C, 0);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetFreqBit(CH_C, 0);
}

void allon(){
  ymz.SetMixer(0b111, 0b000);
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetVolume(CH_B, 0b00001111);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_C, 0b00001111);
  ymz.SetFreqBit(CH_C, 0);
}

