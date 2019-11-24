// Four drums random sequence //

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "AudioSampleSnare.h"
#include "AudioSampleTomtom.h"
#include "AudioSampleHihat.h"
#include "AudioSampleKick.h"

AudioPlayMemory    sound0;
AudioPlayMemory    sound1;
AudioPlayMemory    sound2;
AudioPlayMemory    sound3;
AudioMixer4        mix;
AudioOutputAnalog  dac;
AudioOutputI2S     out;

AudioConnection c1(sound0, 0, mix, 0);
AudioConnection c2(sound1, 0, mix, 1);
AudioConnection c3(sound2, 0, mix, 2);
AudioConnection c4(sound3, 0, mix, 3);
AudioConnection c5(mix, 0, dac, 0);
AudioConnection c6(mix, 0, out, 0);
AudioConnection c7(mix, 0, out, 1);

AudioControlSGTL5000 audioShield;


void setup() {
 
  AudioMemory(10);
  
  audioShield.enable();
  audioShield.volume(0.2);
  
  mix.gain(0, 0.4);
  mix.gain(1, 0.4);
  mix.gain(2, 0.4);
  mix.gain(3, 0.4);

}

void loop() {

  int rnd = rand()%4;
  
  if (rnd == 0) sound0.play(AudioSampleSnare);
  
  if (rnd == 1) sound1.play(AudioSampleTomtom);
  
  if (rnd == 2) sound2.play(AudioSampleHihat);
    
  if (rnd == 3) sound3.play(AudioSampleKick);
  
  delay (240);

}
