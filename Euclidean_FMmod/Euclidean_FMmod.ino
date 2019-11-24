// Euclidean sequence - two FM modulated oscillators //
// http://en.wikipedia.org/wiki/Euclidean_Rhythm //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

  int steps = 8;
  int hits = 3;

  int nx;
  int ny;
  
  int tx, ty;

  AudioSynthWaveform ton1;
  AudioSynthWaveform ton2;
  AudioSynthWaveformSineModulated sine1;
  AudioSynthWaveformSineModulated sine2;
  AudioMixer4 mixer;
  AudioOutputAnalog dac;
  AudioOutputI2S     out;

  AudioConnection c0(ton1,0,sine1,0);
  AudioConnection c1(sine1,0,mixer,0);
  AudioConnection c2(ton2,0,sine2,0);
  AudioConnection c3(sine2,0,mixer,1);
  AudioConnection c4(mixer,0,dac,0);
  AudioConnection c5(mixer,0,out,0);
  AudioConnection c6(mixer,0,out,1);

AudioControlSGTL5000 audioShield; 


void setup() {

  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);

  ton1.begin(0.1,2,WAVEFORM_SQUARE);
  
  ton2.begin(0.1,0.5,WAVEFORM_SQUARE); 
  
  sine1.frequency(440);
  sine1.amplitude(1.0);
  
  sine2.frequency(220);
  sine2.amplitude(1.0);
  
  mixer.gain(0,0.4);
  mixer.gain(1,0.4);

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
  
  sine1.frequency(220*nx);
  sine2.frequency(110*ny);
  
  delay(500);
  
}
