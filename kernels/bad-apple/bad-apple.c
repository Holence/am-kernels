#include <am.h>
#include <stdio.h>
#include <klib-macros.h>
#include <string.h>
#include <stdlib.h>

#define HAS_GUI // 开启VGA

#define FPS 30
#define CHAR_WHITE '.'
#define CHAR_BLACK 'X'

typedef struct {
  uint8_t pixel[VIDEO_ROW * VIDEO_COL / 8];
} frame_t;

static void sleep_until(uint64_t next) {
  while (io_read(AM_TIMER_UPTIME).us < next) ;
}

static uint8_t getbit(uint8_t *p, int idx) {
  int byte_idx = idx / 8;
  int bit_idx = idx % 8;
  bit_idx = 7 - bit_idx;
  uint8_t byte = p[byte_idx];
  uint8_t bit = (byte >> bit_idx) & 1;
  return bit;
}

int main() {
  extern uint8_t video_payload, video_payload_end;
  extern uint8_t audio_payload, audio_payload_end;
  int audio_len = 0, audio_left = 0;
  Area sbuf;

  ioe_init();

  frame_t *f = (void *)&video_payload;
  frame_t *fend = (void *)&video_payload_end;
  #ifdef HAS_GUI
  uint32_t* buffer = malloc(VIDEO_ROW * VIDEO_COL* sizeof(uint32_t));
  /*
  这里不能用栈来存大数组！！！
  // uint32_t buffer[VIDEO_ROW * VIDEO_COL];
  因为/abstract-machine/scripts/linker.ld中把客户程序的栈区写死了，为0x8000个字节（32KB）
  ```
  _stack_top = ALIGN(0x1000);
  . = _stack_top + 0x8000;
  _stack_pointer = .;
  ```
  0x8000 == 32768 Bytes
  而如果是128x96的尺寸，96*128*4 == 49152 Bytes
  buffer的地址为 0x81C0DFB0，已经跨越了_stack_top的底线，跑到了全局变量区
  buffer比lut的地址还低，buffer[index]是往高处写，把全局变量区都抹了，调用ioe_write时函数都找不到
  */
  AM_GPU_CONFIG_T info = io_read(AM_GPU_CONFIG);
  int vga_x = (info.width - VIDEO_COL) / 2;
  int vga_y = (info.height - VIDEO_ROW) / 2;
  #else
  printf("\033[H\033[J");  // screan_clear
  #endif

  bool has_audio = io_read(AM_AUDIO_CONFIG).present;
  if (has_audio) {
    io_write(AM_AUDIO_CTRL, AUDIO_FREQ, AUDIO_CHANNEL, 1024);
    audio_left = audio_len = &audio_payload_end - &audio_payload;
    sbuf.start = &audio_payload;
  }
  
  uint64_t now = io_read(AM_TIMER_UPTIME).us;
  for (; f < fend; f ++) {
    #ifdef HAS_GUI
      memset(buffer, 0, VIDEO_ROW * VIDEO_COL * sizeof(uint32_t));
      int index = 0;
      for (int y = 0; y < VIDEO_ROW; y++) {
        for (int x = 0; x < VIDEO_COL; x++) {
          uint8_t p = getbit(f->pixel, y * VIDEO_COL + x);
          if (p) {
            buffer[index] = 0x00FFFFFF;
          }
          index++;
        }
      }
      io_write(AM_GPU_FBDRAW, vga_x, vga_y, buffer, VIDEO_COL, VIDEO_ROW, true);
    #else
     printf("\033[0;0H");  // reset cursor
     for (int y = 0; y < VIDEO_ROW; y++) {
       for (int x = 0; x < VIDEO_COL; x++) {
         uint8_t p = getbit(f->pixel, y * VIDEO_COL + x);
         putch(p ? CHAR_BLACK : CHAR_WHITE);
       }
       putch('\n');
     }
    #endif

     if (has_audio) {
       int should_play = (AUDIO_FREQ / FPS) * sizeof(int16_t);
       if (should_play > audio_left) should_play = audio_left;
       while (should_play > 0) {
         int len = (should_play > 4096 ? 4096 : should_play);
         sbuf.end = sbuf.start + len;
         io_write(AM_AUDIO_PLAY, sbuf);
         sbuf.start += len;
         should_play -= len;
       }
       audio_left -= should_play;
     }

     uint64_t next = now + (1000 * 1000 / FPS);
     sleep_until(next);
     now = next;
  }
  return 0;
}
