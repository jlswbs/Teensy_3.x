// Simple Karplus Strong //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "synth_samples_test.h"

#define SR 48000.
#define DELAY_SIZE 256

uint8_t Delay_buffer[DELAY_SIZE];
uint8_t Delay_index;
uint16_t Delay_phase;

uint16_t Attack;

int i;

uint8_t Noise_buffer[DELAY_SIZE];


AudioSynthSamplesTest  samples;
AudioMixer4       mixer;
AudioOutputAnalog dac;
AudioOutputI2S    out;

AudioConnection c0(samples, 0, mixer, 0);
AudioConnection c1(mixer, 0, dac, 0);
AudioConnection c2(mixer, 0, out, 0);
AudioConnection c3(mixer, 0, out, 1);

AudioControlSGTL5000 audioShield;


void setup() {

  AudioMemory(10);

  audioShield.enable();
  audioShield.volume(0.2);
   
  for (i = 0; i < DELAY_SIZE; i += 1) Noise_buffer[i] = rand() & 255;
  
  mixer.gain(0,0.4);
  
}


void loop() {

  write_note(48, 24+rand()%256, 2);

}


uint8_t process(uint16_t period) {
  uint8_t x;
  if (Attack) {
    Delay_buffer[Delay_index] = Noise_buffer[Delay_index];
    Attack -= 1;
  }
  x = Delay_buffer[Delay_index];
  Delay_phase += period;
  Delay_index += Delay_phase >> 14;
  Delay_phase &= 16383;
  Delay_buffer[Delay_index] = (x + Delay_buffer[Delay_index]) >> 1;
  return x;
}


void write_note(int attack, int freq, int duration) {
  uint8_t sample;
  int i;

  Attack = attack;
  for (i = 0; i < SR / duration; i+= 1) {
    sample = process(16383 * DELAY_SIZE * (freq / SR));
    while(samples.store_sample(((int16_t)sample-128) << 8));
  }
  
}
