// YMZ294 tiny primitive synthesizer sample
// Harmonica? with pitch change
// Kodera2t, Mar.23, 2019
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
  ymz.SetMixer(0b111, 0b000); 

  allon();
}


void loop() {
boolean sw1, sw2, sw3, sw4;
int val,val2;
  sw1=digitalRead(11);
  sw2=digitalRead(12);
  sw3=digitalRead(13);
  sw4=digitalRead(A0);
  val=analogRead(A1)/200;
  val2=analogRead(A3)/200;  
  if(sw1==0){
  allon();
  envset();
  ymz.SetFrequency(CH_A, CalcFreqByMML(5+val, 'C'+val2));
  ymz.SetFrequency(CH_B, CalcFreqByMML(5+val, 'E'+val2));
  ymz.SetFrequency(CH_C, CalcFreqByMML(5+val, 'G'+val2));  
  delay(500);
  allzero(); 
  }
  if(sw2==0){
  allon();
  envset(); 
  ymz.SetFrequency(CH_A, CalcFreqByMML(5+val, 'D'+val2));
  ymz.SetFrequency(CH_B, CalcFreqByMML(5+val, 'F'+val2));
  ymz.SetFrequency(CH_C, CalcFreqByMML(5+val, 'A'+val2));  
  delay(500);
  allzero();
  }
  if(sw3==0){
  allon();
  envset();
  ymz.SetFrequency(CH_A, CalcFreqByMML(5+val, 'E'+val2));
  ymz.SetFrequency(CH_B, CalcFreqByMML(5+val, 'G'+val2));
  ymz.SetFrequency(CH_C, CalcFreqByMML(5+val, 'B'+val2));  
  delay(500);
  allzero();  
  }
  if(sw4==0){
  allon();
  envset();
  ymz.SetFrequency(CH_A, CalcFreqByMML(5+val, 'F'+val2));
  ymz.SetFrequency(CH_B, CalcFreqByMML(5+val, 'A'+val2));
  ymz.SetFrequency(CH_C, CalcFreqByMML(6+val, 'C'+val2));
  delay(500);
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
  ymz.SetVolume(CH_A, 0b00001111);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetVolume(CH_B, 0b00001111);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_C, 0b00001111);
  ymz.SetFreqBit(CH_C, 0);
}
void volset(int cha, int chb, int chc){
  ymz.SetVolume(CH_A, cha);
  ymz.SetFreqBit(CH_A, 0);
  ymz.SetVolume(CH_B, chb);
  ymz.SetFreqBit(CH_B, 0);
  ymz.SetVolume(CH_C, chc);
  ymz.SetFreqBit(CH_C, 0);
}

void envset(){
   ymz.SetEnvFrequency(60);
   ymz.SetEnvShape(1,1,1,0); 
   ymz.SetEnvEnable(CH_A, 1);
   ymz.SetEnvEnable(CH_B, 1);
   ymz.SetEnvEnable(CH_C, 1);  
}

