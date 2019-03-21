#include "YMZ294.h"

// MML char to Freqyency Convert Function
word CalcFreqByMML(byte octave, char note, bool is_sharp)
{
  int pos = 0;
  switch (note) {
    case 'C':
    case 'c':
      break;
    case 'D':
    case 'd':
      pos = 2;
      break;
    case 'E':
    case 'e':
      pos = 4;
      break;
    case 'F':
    case 'f':
      pos = 5;
      break;
    case 'G':
    case 'g':
      pos = 7;
      break;
    case 'A':
    case 'a':
      pos = 9;
      break;
    case 'B':
    case 'b':
      pos = 11;
      break;
    default:
      break;
  }
  return noteFreq[octave * 12 + pos + (is_sharp ? 1 : 0)];
}

/* ------------------------------------------------------------------------ */
// Constructor
/* ------------------------------------------------------------------------ */
YMZ294::YMZ294(byte wrcs_pin, byte a0_pin, byte reset_pin)
 : WRCS_PIN(wrcs_pin), A0_PIN(a0_pin), RESET_PIN(reset_pin)
{
	param_reset();
}

/* ------------------------------------------------------------------------ */
// Public Functions
/* ------------------------------------------------------------------------ */
void YMZ294::Reset(void)
{
	param_reset();
	hardware_reset();
}

// ------ Square Channel Functions ---------------------------------------- */
// Channel On/Off
void YMZ294::SetEnable(Channel ch, bool enable)
{
	if(enable)
		mixer |= ~(1 << ch); // enable is 0
	else
		mixer |= (1 << ch); // disable is 1
	set_register(REG_MIXER, mixer);
}

// Set 12bit Frequency Bit to Channel
void YMZ294::SetFreqBit(Channel ch, word freqbit)
{
	sq_freqbits[ch] = freqbit & 0b0000111111111111; // 12bit
	set_register(REG_A_L + (ch * 2), sq_freqbits[ch] & 0xff);
	set_register(REG_A_H + (ch * 2), (sq_freqbits[ch] >> 8) & 0xff);
}

// Set Frequency(Hz) to Channel
void YMZ294::SetFrequency(Channel ch, word freq)
{
	SetFreqBit(ch, (BASE_FREQ / freq));
}

// Set Volume (4bit)
void YMZ294::SetVolume(Channel ch, byte volume)
{
	volumes[ch] = volume;
	set_register(REG_VOLUME_A + ch, volumes[ch]);
}

// ------ Envelope Functions ---------------------------------------- */
// Set Envelope (Volume Disable)
void YMZ294::SetEnvEnable(Channel ch, bool enable)
{
	volumes[ch] = (((enable? 1: 0) << 4) | (volumes[ch] & 0b00001111));
	set_register(REG_VOLUME_A + ch, volumes[ch]);
}

// Set Envelope Frequency Bit (16bit)
void YMZ294::SetEnvFreqBit(word freqbit)
{
	env_freqbit = freqbit;
	set_register(REG_ENV_L, env_freqbit & 0xff);
	set_register(REG_ENV_H, (env_freqbit >> 8) & 0xff);
}

// Set Envelope Frequency(Hz)
void YMZ294::SetEnvFrequency(word freq)
{
	SetEnvFreqBit(BASE_FREQ / freq);
}

// Set Envelope Shape (4bit)
void YMZ294::SetEnvShape(bool cont, bool att, bool alt, bool hold)
{
	env_shape = (cont<< 3) |
				(att << 2) |
				(alt << 1) |
				 hold;
	set_register(REG_ENV_SHAPE, env_shape);
}

// ------ Noise Channel Functions ---------------------------------------- */
// Set 5bit Frequency Bit to Noise Channel
void YMZ294::SetNoiseFreqBit(byte freqbit)
{
	noise_freqbit = freqbit & 0b00011111; // 5bit
	set_register(REG_NOISE, noise_freqbit);
}

// Set Frequency(Hz) to Noise Channel
void YMZ294::SetNoiseFrequency(word freq)
{
	SetNoiseFreqBit(BASE_FREQ / freq);
}

// ------ Mixer Functions ---------------------------------------- */
void YMZ294::SetMixer(byte noise, byte square)
{
	mixer = ((noise & 0b111) << 3) | (square & 0b111);
	set_register(REG_MIXER, mixer);
}

/* ------------------------------------------------------------------------ */
// Private Functions
/* ------------------------------------------------------------------------ */
void YMZ294::param_reset(void)
{
	set_register(REG_A_L, 0);
	set_register(REG_A_H, 0);
	set_register(REG_B_L, 0);
	set_register(REG_B_H, 0);
	set_register(REG_C_L, 0);
	set_register(REG_C_H, 0);
	set_register(REG_NOISE, 0);

	set_register(REG_MIXER, 0);
	set_register(REG_VOLUME_A, 0);
	set_register(REG_VOLUME_B, 0);
	set_register(REG_VOLUME_C, 0);

	set_register(REG_ENV_L, 0);
	set_register(REG_ENV_H, 0);
	set_register(REG_ENV_SHAPE, 0);

	for (int i = 0; i < CH_COUNT; i++){
		sq_freqbits[i] = 0;
		volumes[i] = 0;
	}
	mixer = 0b00111111; // All Channel Off
	env_freqbit = 0;
	env_shape = 0;
	
	
}

void YMZ294::hardware_reset(void)
{
	digitalWrite(WRCS_PIN, HIGH);
	digitalWrite(A0_PIN, LOW);
	digitalWrite(RESET_PIN, LOW);
	delay(10);
	digitalWrite(RESET_PIN, HIGH);
}

void YMZ294::set_register(byte addr, byte value)
{
  // addr
  digitalWrite(WRCS_PIN, LOW);
  digitalWrite(A0_PIN, LOW);
  PORTD = addr;
  digitalWrite(WRCS_PIN, HIGH);

  // value
  digitalWrite(WRCS_PIN, LOW);
  digitalWrite(A0_PIN, HIGH);
  PORTD = value;
  digitalWrite(WRCS_PIN, HIGH);
}

