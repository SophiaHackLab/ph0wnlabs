#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define WS2812_PIN 5

PIO pio = pio0;

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) << 8) |
      ((uint32_t) (g) << 16) |
      (uint32_t) (b);
}

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

void ws2812_init() {
  int sm = 0;
  
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
}

int main() {
  stdio_init_all();
  ws2812_init();
  char flag[] = "ph0wn{je-me-suis-fait-avoir-1er-avril}";

  while (!stdio_usb_connected()) {
    // yellow
    put_pixel(urgb_u32(0xf6, 0xd4, 0x1f));
    put_pixel(urgb_u32(0xf6, 0xd4, 0x1f));
    sleep_ms(80);
  }

  while(true) {
    printf("                               __   __       \n");
    printf("                              (o |_| o)_______    \n");
    printf("                              |  _____________)  \n");
    printf("                              \\              / \n");
    printf("                               \\            / \n");
    printf("                                \\__________/  \n");
    printf("\n\n");
    printf("A Ph0wn 2026, un flag ultra secret permettra de flagger\n");
    printf("tous les challenges. Mémorisez le bien: \n");

    for (int i=0;i<strlen(flag); i++) {
      printf("%c", flag[i]);
      for (uint32_t j = 0x000000ff; j < 0x01000000; j = j << 8) {
	put_pixel(j);
	put_pixel(j);
	sleep_ms(150);
      }
    }
    printf("\n");
    
    // green
    put_pixel(urgb_u32(0x00, 0xff, 0x00));
    put_pixel(urgb_u32(0x00, 0xff, 0x00));
    sleep_ms(30*1000);
  }

  return 0;
}
