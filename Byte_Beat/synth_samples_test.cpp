/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "AudioStream.h"
#include "synth_samples_test.h"


/******************************************************************/
void AudioSynthSamplesTest::flush(void)
{
  if(s_block_idx) {
  	while(s_block_idx < AUDIO_BLOCK_SAMPLES) {
      s_block->data[s_block_idx++] = 0;
    }
  	transmit(s_block,0);
  	release(s_block);
  	s_block = NULL;
  	s_block_idx = 0;
  }
}

/******************************************************************/
bool AudioSynthSamplesTest::store_sample(int16_t s)
{
  if(s_block_idx >= AUDIO_BLOCK_SAMPLES)return true;
  if(s_block == NULL) {
  	s_block = allocate();
  	s_block_idx = 0;
  }
  s_block->data[s_block_idx++] = s;
  return false;
}

/******************************************************************/
void AudioSynthSamplesTest::update(void)
{
  if(s_block_idx >= AUDIO_BLOCK_SAMPLES) {
  	transmit(s_block,0);
  	release(s_block);
  	s_block = allocate();
    s_block_idx = 0;
  }

}
