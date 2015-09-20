#include <stdint.h>

#ifndef config
#define config

#define SIZE 16

#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 4096 / 8
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

#define PI 3.141592653589

#define MICROPHONE A7
#define GAIN_CONTROL D5

extern uint8_t PIXEL_RGB[NUM_STRIPS * NUM_LEDS_PER_STRIP * 3];

#endif
