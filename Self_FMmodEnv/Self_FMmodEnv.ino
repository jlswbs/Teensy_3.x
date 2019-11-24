// Simple self modulated FM oscillators with envelope //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>


AudioSynthWaveformSineModulated sine1;
AudioSynthWaveformSineModulated sine2;
AudioEffectEnvelope env;
AudioMixer4 mixer;
AudioOutputAnalog dac;
AudioOutputI2S    out;

AudioConnection c0(sine2,0,sine1,0);
AudioConnection c1(sine1,0,mixer,0);
AudioConnection c2(sine1,0,sine2,0);
AudioConnection c3(sine2,0,mixer,1);
AudioConnection c4(mixer,0,env,0);
AudioConnection c5(env,0,dac,0);
AudioConnection c6(env,0,out,0);
AudioConnection c7(env,0,out,1);

AudioControlSGTL5000 audioShield; 


void setup() {

  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);
  
  sine1.frequency(220);
  sine1.amplitude(0.5);
  
  sine2.frequency(440);
  sine2.amplitude(0.5);
  
  mixer.gain(0,0.4);
  mixer.gain(1,0.4);
  
  env.attack(1.5);
  env.decay(50.0);
  env.sustain(50.0);
  env.release(50.0);

}


void loop() {
  
  sine1.frequency(220+rand()%220);
  
  sine2.frequency(440+rand()%440);
  
  env.noteOn();

  delay (5);
  
  env.noteOff();
  
  delay(235);
  
}
