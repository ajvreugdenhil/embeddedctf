#include <Arduino.h>

#define FLAGLESS 1

#ifdef FLAGLESS
#define BLINKFLAG "ECTF{FLAGLESS}"
#else
#define BLINKFLAG "ECTF{}"
#endif

#define BLINKLED LED_BUILTIN

unsigned int previous_tick = 0;

void setup() {
  pinMode(BLINKLED, OUTPUT);
}

void tick_blink()
{
  char blink_flag[] = BLINKFLAG;
  int blink_flag_length = strlen(blink_flag);
  int step = (millis()/100) % (blink_flag_length * 8);
  pinMode(BLINKLED, ((blink_flag[((int)step/8)] >> (step%8))) & 1);
}

void loop() {
  tick_blink();
}
