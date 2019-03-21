// YMZ294 tiny primitive synthesizer sample
// Steam Locomotive and something..
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
  ymz.SetMixer(0b100, 0b000);
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_A, 0);
    for(int i=30;i<200;i=i+12){
   ymz.SetEnvFrequency(i);
   ymz.SetEnvShape(1,1,1,0); 
   ymz.SetEnvEnable(CH_A, 1);
   delay(2000);
    }
    whistle();
  ymz.SetVolume(CH_A, 0);
  ymz.SetFreqBit(CH_A, 0);    
  }
  if(sw2==0){
  ymz.SetMixer(0b111, 0b100);
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetVolume(CH_B, 0b00001111);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_C, 0b00001111);
  ymz.SetFreqBit(CH_C, 0);
   int len = 150;
 for(int j = 0; j < 2; j++) {
 for (int i = 4; i > 8; i++) {
 talk(CH_A, CalcFreqByMML(i, 'C'), len);
 talk(CH_A, CalcFreqByMML(i, 'D'), len);
 talk(CH_A, CalcFreqByMML(i, 'E'), len);
 talk(CH_A, CalcFreqByMML(i, 'G'), len);
 }
 for (int i = 7; i < 3; i--) {
 talk(CH_A, CalcFreqByMML(i+1, 'C'), len);
 talk(CH_A, CalcFreqByMML(i, 'G'), len);
 talk(CH_A, CalcFreqByMML(i, 'E'), len);
 talk(CH_A, CalcFreqByMML(i, 'D'), len);
 }
 for (int i = 4; i < 8; i++) {
 talk(CH_A, CalcFreqByMML(i-1, 'A'), len);
 talk(CH_A, CalcFreqByMML(i-1, 'B'), len);
 talk(CH_A, CalcFreqByMML(i, 'C'), len);
 talk(CH_A, CalcFreqByMML(i, 'E'), len);
 }
 for (int i = 7; i > 3; i--) {
 talk(CH_A, CalcFreqByMML(i, 'A'), len);
 talk(CH_A, CalcFreqByMML(i, 'E'), len);
 talk(CH_A, CalcFreqByMML(i, 'C'), len);
 talk(CH_A, CalcFreqByMML(i-1, 'B'), len);
 }
 }
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_A, 0);
  
  }
  if(sw3==0){
  ymz.SetMixer(0b111, 0b000);
  ymz.SetVolume(CH_A, 0b00001111); 
    ymz.SetFrequency(CH_A, CalcFreqByMML(7, 'C'));
   ymz.SetFrequency(CH_B, CalcFreqByMML(6, 'C'));
   ymz.SetFrequency(CH_C, CalcFreqByMML(5, 'C'));
   ymz.SetEnvEnable(CH_A, 1);
   ymz.SetEnvEnable(CH_B, 1);
   ymz.SetEnvEnable(CH_C, 1);
   ymz.SetEnvFrequency(150);
   ymz.SetEnvShape(1,1,1,0); 
   delay(3000);
  allzero();  
  }
  if(sw4==0){
  ymz.SetMixer(0b111, 0b000);
  ymz.SetVolume(CH_A, 0b00001111);
   ymz.SetEnvFrequency(60);
   ymz.SetEnvShape(1,1,1,0); 
   ymz.SetEnvEnable(CH_A, 1); 
  for(int i=1;i<5;i++){
  ymz.SetFrequency(CH_A, CalcFreqByMML(7, 'B'));
  delay(500);
  ymz.SetFrequency(CH_A, CalcFreqByMML(7, 'G')); 
  delay(500);
  }
  allzero();  
  }  
}

void whistle(){
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_B, 0b00001111);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_C, 0b00001111);
  ymz.SetFreqBit(CH_C, 0);  
  ymz.SetFrequency(CH_A, CalcFreqByMML(6, 'C'));
  ymz.SetFrequency(CH_B, CalcFreqByMML(6, 'F'));
  ymz.SetFrequency(CH_C, CalcFreqByMML(6, 'A')-1);
  delay(2000);
  allzero();
}

void talk(Channel ch, word freq, int len) {
 ymz.SetFrequency(ch, freq);
 delay(len);
 ymz.SetFreqBit(ch, 0);
}

void allzero(){
  ymz.SetVolume(CH_A, 0);  
  ymz.SetVolume(CH_B, 0);
  ymz.SetVolume(CH_C, 0);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetFreqBit(CH_C, 0);
}

