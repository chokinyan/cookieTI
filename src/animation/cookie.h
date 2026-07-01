#ifndef cookie_animation_h
#define cookie_animation_h

#include "stdbool.h"
#include <stdint.h>
#include <graphx.h>

typedef struct {
  uint8_t frame;
  uint32_t last_time;
  uint8_t time_delay;
  bool playing;
} Animation_State_t;

uint32_t get_time_ms();

void update_animation(Animation_State_t *anim, gfx_sprite_t *sprite);

#endif