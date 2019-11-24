// Euclidean sequence with two wavetables and envelope //
// http://en.wikipedia.org/wiki/Euclidean_Rhythm //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "AKWF_0001.h"
#include "AKWF_0002.h"

  int steps = 8;
  int hits = 3;

  int nx;
  int ny;
  
  int tx, ty;

AudioSynthWaveform    wave1;
AudioSynthWaveform    wave2;
AudioEffectEnvelope env;
AudioMixer4        mix;
AudioOutputAnalog  dac;
AudioOutputI2S     out;

AudioConnection c1(wave1, 0, mix, 0);
AudioConnection c2(wave2, 0, mix, 1);
AudioConnection c3(mix, 0, env, 0);
AudioConnection c4(env, 0, dac, 0);
AudioConnection c5(env, 0, out, 0);
AudioConnection c6(env, 0, out, 1);

AudioControlSGTL5000 audioShield;


void setup() {
 
  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);
  
  wave1.begin(1.0,1,WAVEFORM_ARBITRARY);
  
  wave1.arbitraryWaveform(AKWF_0001,600);
  
  wave2.begin(1.0,1,WAVEFORM_ARBITRARY);
  
  wave2.arbitraryWaveform(AKWF_0002,600);
  
  mix.gain(0, 0.4);
  mix.gain(1, 0.4);

  env.attack(1.5);
  env.decay(50.0);
  env.sustain(50.0);
  env.release(50.0);

}

void loop() {
  
        nx = tx;
        ny = ty;
       
        if (ny == 0) {
          
          tx = rand()%steps;
          ty = hits; 
          
        } else { 
          
          tx = ny;
          ty = nx % ny;
          
        }
  
  wave1.frequency(110+220*nx);
  
  wave2.frequency(110+110*ny);
  
  env.noteOn();

  delay (5);
  
  env.noteOff();
  
  delay (235);

}
