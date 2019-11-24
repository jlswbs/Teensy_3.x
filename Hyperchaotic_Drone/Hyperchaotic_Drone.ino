// Hyperchaotic Lorenz attractor drone //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

  float x = 5;
  float y = 8;
  float z = 12;
  float w = 21;
  float dt = 0.001;
  float a = 10;
  float b = 2.667;
  float c = 28;
  float d = 1.1;

AudioSynthWaveform    wave1;
AudioSynthWaveform    wave2;
AudioSynthWaveform    wave3;
AudioSynthWaveform    wave4;
AudioMixer4        mixl;
AudioMixer4        mixr;
AudioOutputAnalog  dac;
AudioOutputI2S     out;

AudioConnection c1(wave1, 0, mixl, 0);
AudioConnection c2(wave2, 0, mixl, 1);
AudioConnection c3(wave3, 0, mixr, 0);
AudioConnection c4(wave4, 0, mixr, 1);
AudioConnection c5(mixl, 0, dac, 0);
AudioConnection c6(mixr, 0, dac, 0);
AudioConnection c7(mixl, 0, out, 0);
AudioConnection c8(mixr, 0, out, 1);

AudioControlSGTL5000 audioShield;


void setup() {
 
  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);
  
  wave1.begin(1.0,220,WAVEFORM_SINE); 
  wave2.begin(1.0,220,WAVEFORM_TRIANGLE);
  wave3.begin(1.0,220,WAVEFORM_TRIANGLE); 
  wave4.begin(1.0,220,WAVEFORM_SINE);
  
  mixl.gain(0, 0.4);
  mixl.gain(1, 0.4);
  
  mixr.gain(0, 0.4);
  mixr.gain(1, 0.4);

}


void loop() {
  
  float nx = x;
  float ny = y;
  float nz = z;
  float nw = w;
        
  x = nx + dt * (a * (ny - nx) + nw);
  y = ny + dt * (- nx * nz + c * nx - ny);
  z = nz + dt * (- b * nz + nx * ny);
  w = nw + dt * (d * nw - nx * nz);
  
  wave1.frequency(220+4*x);
  wave2.frequency(220+4*y);
  wave3.frequency(220+4*z);
  wave4.frequency(220+4*w);

}
