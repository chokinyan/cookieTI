#include <compression.h>
#include <graphx.h>
#include <stdint.h>
#include <sys/timers.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>

#include "animation/cookie.h"
#include "data/bigdata.h"
#include "sprite/sprite.h"


uint32_t get_time_ms() { return timer_GetSafe(1, TIMER_UP) >> 5; }

int main(void) {
  gfx_sprite_t *cookie;
  timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_UP); // Init timer to part 1
  Animation_State_t cookie_anim = {
      .time_delay = 30,
      .playing = 0,
      .frame = 0,
      .last_time = get_time_ms(),
  };

  BigNum_t cookie_num;
  BigNum_Init(&cookie_num, 0.0);

  char cookie_num_buffer[1024];

  gfx_SetDrawBuffer();

  if (!(cookie = gfx_MallocSprite(perfectCookie_width, perfectCookie_height)))
    return 1;

  zx0_Decompress(cookie, perfectCookie_compressed);
  gfx_Begin();

  gfx_SetPalette(global_palette, sizeof_global_palette, 0);

  gfx_ScaledSprite_NoClip(cookie, (GFX_LCD_WIDTH - perfectCookie_width * 5) / 2,
                          (GFX_LCD_HEIGHT - perfectCookie_height * 5) / 2 - 30,
                          5, 5);

  bool end = 0;

  while (!end) {
    uint8_t csc = os_GetCSC();

    switch (csc) {
    case sk_Mode:
      end = 1;
      break;
    case sk_0:
      BigNum_Add(&cookie_num, 0.01);
      cookie_anim.playing = 1;
      break;
    default:
      break;
    }

    gfx_FillScreen(0);

    update_animation(&cookie_anim, cookie);

    BigNum_ToString("cookies: ", &cookie_num, cookie_num_buffer);

    gfx_SetTextFGColor(0xA2);
    gfx_SetTextXY(0, GFX_LCD_HEIGHT - 10);
    gfx_PrintString(cookie_num_buffer);

    gfx_SwapDraw();
  };

  gfx_FillScreen(0);
  gfx_SwapDraw();

  free(cookie);
  gfx_End();

  return 0;
}