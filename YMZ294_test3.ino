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

 ymz.Reset();
 ymz.SetMixer(0b111, 0b100);
 ymz.SetVolume(CH_A, 0b00001111);
 ymz.SetFreqBit(CH_A, 0);
 ymz.SetVolume(CH_B, 0b00001111);
 ymz.SetFreqBit(CH_B, 0);
 ymz.SetVolume(CH_C, 0b00001111);
 ymz.SetFreqBit(CH_C, 0);

}

void loop() {

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
}

void talk(Channel ch, word freq, int len) {
 ymz.SetFrequency(ch, freq);
 delay(len);
 ymz.SetFreqBit(ch, 0);
}
