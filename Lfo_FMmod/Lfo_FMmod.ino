// Lfo modulated FM oscillators //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioSynthWaveform lfo1;
AudioSynthWaveform lfo2;
AudioSynthWaveform lfo3;
AudioSynthWaveformSineModulated sine1;
AudioSynthWaveformSineModulated sine2;
AudioSynthWaveformSineModulated sine3;
AudioMixer4 mixer;
AudioOutputAnalog dac;
AudioOutputI2S     out;

AudioConnection c0(lfo1,0,sine1,0);
AudioConnection c1(sine1,0,mixer,0);
AudioConnection c2(lfo2,0,sine2,0);
AudioConnection c3(sine2,0,mixer,1);
AudioConnection c4(lfo3,0,sine3,0);
AudioConnection c5(sine3,0,mixer,2);
AudioConnection c6(mixer,0,dac,0);
AudioConnection c7(mixer,0,out,0);
AudioConnection c8(mixer,0,out,1);

AudioControlSGTL5000 audioShield; 


void setup() {

  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);

  lfo1.begin(0.5,1.0,WAVEFORM_SQUARE);
  
  lfo2.begin(0.5,0.5,WAVEFORM_SQUARE);
  
  lfo3.begin(0.5,1.5,WAVEFORM_SQUARE);
  
  sine1.frequency(220);
  sine1.amplitude(0.5);
  
  sine2.frequency(440);
  sine2.amplitude(0.5);
  
  sine3.frequency(660);
  sine3.amplitude(0.5);
  
  mixer.gain(0,0.4);
  mixer.gain(1,0.4);
  mixer.gain(2,0.4);

}

void loop() {
  
}
