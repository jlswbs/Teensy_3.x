// Simple self modulated FM oscillators //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioSynthWaveformSineModulated sine1;
AudioSynthWaveformSineModulated sine2;
AudioMixer4 mixer;
AudioOutputAnalog dac;
AudioOutputI2S    out;

AudioConnection c0(sine2,0,sine1,0);
AudioConnection c1(sine1,0,mixer,0);
AudioConnection c2(sine1,0,sine2,0);
AudioConnection c3(sine2,0,mixer,1);
AudioConnection c6(mixer,0,dac,0);
AudioConnection c7(mixer,0,out,0);
AudioConnection c8(mixer,0,out,1);

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

}

void loop() {
  
  sine1.frequency(220+rand()%220);
  
  sine2.frequency(440+rand()%440);
  
  delay(500);
  
}
