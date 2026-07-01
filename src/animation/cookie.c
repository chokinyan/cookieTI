#include "cookie.h"
#include "../sprite/sprite.h"

void update_animation(Animation_State_t *anim, gfx_sprite_t *sprite) {
  if (!anim->playing) {
    gfx_ScaledSprite_NoClip(
        sprite, (GFX_LCD_WIDTH - perfectCookie_width * 5) / 2,
        (GFX_LCD_HEIGHT - perfectCookie_height * 5) / 2 - 30, 5, 5);
    return;
  }

  uint32_t time = get_time_ms();
  if (time - anim->last_time < anim->time_delay) {
    return;
  }

  anim->last_time = time;
  anim->frame++;
  if (anim->frame == 10) {
    anim->frame = 0;
    anim->playing = 0;
    return;
  }
  if (anim->frame == 5)
    return;
  uint8_t scale = anim->frame > 5 ? anim->frame - 5 : anim->frame;

  gfx_ScaledSprite_NoClip(
      sprite, (GFX_LCD_WIDTH - perfectCookie_width * scale) / 2,
      (GFX_LCD_HEIGHT - perfectCookie_height * scale) / 2 - 30, scale, scale);
}