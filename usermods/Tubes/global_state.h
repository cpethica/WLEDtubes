#pragma once

#include "wled.h"
#include "beats.h"
#include "effects.h"


class TubeState {
  public:
    // Global clock: frames are defined as 1/64th of a beat
    accum88 bpm = 0;            // BPM in high 8 bits, fraction in low 8 bits 
    BeatFrame_24_8 beat_frame = 0;  // current beat (24 bits) and fractional beat (8bits)
  
    uint16_t pattern_phrase;
    uint8_t pattern_id;
    uint8_t pattern_sync_id;
  
    uint16_t palette_phrase;
    uint8_t palette_id;
  
    uint16_t effect_phrase;
    EffectParameters effect_params;

    // add in variable for new message (should go in new class later)
    uint16_t test;
    uint16_t test1;
    uint16_t test2;
    uint16_t test3;

  void print() {
    uint16_t phrase = beat_frame >> 12;
    uint8_t frac = scale8(100, bpm & 0xFF);
    char buf[128];
    sprintf(buf, "[%d.%d P%d,%d C%d E%d,%d,%d,%d %d.%02dbpm]",
      phrase,
      (beat_frame >> 8) % 16,
      pattern_id,
      pattern_sync_id,
      palette_id,
      effect_params.effect,
      effect_params.pen,
      effect_params.beat,
      effect_params.chance,
      bpm >> 8,
      frac
    );
    Serial.print(buf);
  }
  void print_newdata() {
  char buf[128];
  sprintf(buf, "[%d %d %d %d]",
      test,
      test1,
      test2,
      test3
  );
  Serial.print(buf);
}

};


// make object for WLED settings of master controller for sending to other nodes
class WLEDState {
  public:
    // add in variable for new message (should go in new class later)
    uint16_t brightness;
    uint16_t test1;
    uint16_t test2;
    uint16_t test3;


  void print() {
  char buf[128];
  sprintf(buf, "[%d %d %d %d]",
      test,
      test1,
      test2,
      test3
  );
  Serial.print(buf);
}

};

typedef uint8_t CommandId;

const static CommandId COMMAND_OPTIONS = 0x10;
const static CommandId COMMAND_STATE = 0x20;
const static CommandId COMMAND_ACTION = 0x30;
const static CommandId COMMAND_INFO = 0x40;
const static CommandId COMMAND_BEATS = 0x50;
const static CommandId COMMAND_UPGRADE = 0xE0;
