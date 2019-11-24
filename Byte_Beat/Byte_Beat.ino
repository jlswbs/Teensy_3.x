// Byte Beat algoritmic one line music //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "synth_samples_test.h"

#define SR 48000.
#define DELAY_SIZE 256

int i;
long t;
uint8_t temp;

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
  
  mixer.gain(0,0.4);
  
}


void loop() {

  temp = ((((t/(2+((t>>17)&3)))&(((t>>11)&1)|((t>>12)&2)|((t>>9)&4)))|((t/(2+((t>>15)&3)))&(((t>>10)&1)|((t>>8)&2)|((t>>11)&4))))&7)*32;
  
  write_byte(24+temp, 8000);
  
  t++;

}


void write_byte(int freq, int rate) {
  
  uint8_t sample;
  int i;

  for (i = 0; i < SR / rate; i+= 1) {
    sample = 16383 * DELAY_SIZE * (freq / SR);
    while(samples.store_sample(((int16_t)sample-128) << 8));
  }
  
}
