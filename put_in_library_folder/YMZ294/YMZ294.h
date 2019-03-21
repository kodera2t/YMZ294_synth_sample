#ifndef YMZ294_H
#define YMZ294_H

#include "Arduino.h"

// YMZ294 Registers
#define	REG_A_L	0x00
#define	REG_A_H	0x01
#define	REG_B_L	0x02
#define	REG_B_H	0x03
#define	REG_C_L	0x04
#define	REG_C_H	0x05
#define	REG_NOISE	0x06

#define	REG_MIXER	0x07
#define	REG_VOLUME_A	0x08
#define	REG_VOLUME_B	0x09
#define	REG_VOLUME_C	0x0a

#define	REG_ENV_L	0x0b
#define	REG_ENV_H	0x0c
#define	REG_ENV_SHAPE	0x0d

// YMZ294 Channels
enum Channel{
  CH_A = 0,
  CH_B = 1,
  CH_C = 2,
};
const byte CH_COUNT = 3;

#define BASE_FREQ 125000

// MML char to FreqBit Convert Table
const int noteFreq[] = {
  0,  9,  9, 10,  10, 11,   12,	12,	13,	14,	15,	15,
  16,  17, 18, 19,  21, 22,  23,	25,	26,	28,	29,	31,
  33,  35, 37,	39,  41, 44,  46,	49,	52,	55,	58,	62,
  65,	69, 73,	78,  82, 87,  93,	98,	104,	110,	117,	124,
  131, 139, 147, 156, 165, 175, 185,	196,	208,	220,	233,	247,
  262, 277, 294, 311, 330, 349, 370,	392,	415,	440,	466,	494,
  523, 554, 587, 622, 659, 699, 740,	784,	831,	880,	932,	988,
  1047, 1109, 1175, 1245, 1319, 1397,	1480,	1568,	1661,	1760,	1865,	1976,
  2093, 2218, 2349, 2489, 2637,	2794,	2960,	3136,	3322,	3520,	3729,	3951,
  4186, 4435, 4699, 4978, 5274,	5587,	5920,	6272,	6645,	7040,	7459,	7902,
  8372, 8870, 9397, 9956, 10548,11175,	11840,	12544
};

// MML char to Freqyency Convert Function
word CalcFreqByMML(byte octave, char note, bool is_sharp = false);

class YMZ294 {
public:
		YMZ294(byte wrcs_pin, byte a0_pin, byte reset_pin);

	void Reset(void);
	
	// Square Wave
	void SetEnable(Channel channel, bool enable);
	void SetFreqBit(Channel ch, word freqbit);
	void SetFrequency(Channel ch, word freq);
	void SetVolume(Channel ch, byte Volume);

	// Envelope
	void SetEnvEnable(Channel ch, bool enable);
	void SetEnvFreqBit(word freq);
	void SetEnvFrequency(word freq);
	void SetEnvShape(bool cont, bool att, bool alt, bool hold);

	// Noise Channel
//	void SetNoiseEnable(bool enable);
	void SetNoiseFreqBit(byte freqbit);
	void SetNoiseFrequency(word freq);

	// Set Mixer Channel
	void SetMixer(byte noisemsk, byte tonemsk);

	// Get Parameter
	word FreqBit(Channel ch){return sq_freqbits[ch];}
	byte NoiseFreqBit(void){return noise_freqbit;}
	byte Mixer(void){return mixer;}
	byte Volume(byte ch){return volumes[ch];}
	word EnvFreqBit(void){return env_freqbit;}
	byte EnvShape(void){return env_shape;}

	// Get Pin No.
	byte GetWRCS(){return WRCS_PIN;}
	byte GetA0(){return A0_PIN;}
	byte GetRESET(){return RESET_PIN;}
	
private:
	// Arduino Pins
	const byte WRCS_PIN;
	const byte A0_PIN;
	const byte RESET_PIN;
	
	// YMZ294 Parameters
	word sq_freqbits[CH_COUNT];	// Square Wave Frequency Information A/B/C (12bit * 3)
	byte noise_freqbit;			// Noise Frequency Information (5bit)
	byte mixer;					// Mixer Status (6bit)
	byte volumes[CH_COUNT];		// Volume Status (5bit * 3)
	word env_freqbit;			// Envelope Frequency Information (16bit)
	byte env_shape;				// Envelope Shape (4bit)
	
	void param_reset(void);
	void hardware_reset(void);
	void set_register(byte addr, byte value);
};

#endif
