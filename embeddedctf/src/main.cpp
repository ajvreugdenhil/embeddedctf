#include <Arduino.h>

#define FLAGLESS 1

#ifdef FLAGLESS
#define BLINKFLAG "ECTF{PLACEHOLDER}"
#define UARTFLAG "ECTF{PLACEHOLDER}"
#define BOFFLAG "ECTF{PLACEHOLDER}"
#else
#define BLINKFLAG "ECTF{BLINK}"
#define UARTFLAG "ECTF{UART}"
#define BOFFLAG "ECTF{BOF}"
#endif

#define UARTKEY "TODO"

#define BLINKLED LED_BUILTIN

unsigned int previous_tick = 0;

void print_bof_flag()
{
  Serial.println(BOFFLAG);
}

void setup()
{
  Serial.begin(57600);
  pinMode(BLINKLED, OUTPUT);
  Serial.printf("An interesting function can be found at 0x%lx", &print_bof_flag);
}

void tick_blink()
{
  char blink_flag[] = BLINKFLAG;
  int blink_flag_length = strlen(blink_flag);
  int step = (millis() / 100) % (blink_flag_length * 8);
  pinMode(BLINKLED, ((blink_flag[((int)step / 8)] >> (step % 8))) & 1);
}

char uart_buffer[127] = {0x41};
int uart_buffer_len = 0;
void tick_uart()
{
  if (Serial.available())
  {
    char b = Serial.read();
    if (b != '\n')
    {
      uart_buffer[uart_buffer_len] = b; // Intentionally vulnerable
      uart_buffer_len += 1;
      Serial.print(b);
    }
    else
    {
      uart_buffer[uart_buffer_len - 1] = '\0';
      if (strcmp(UARTKEY, uart_buffer) == 0)
      {
        Serial.print("\nCongrats! here's the flag: ");
        Serial.println(UARTFLAG);
      }
      else
      {
        Serial.print("\nIncorrect key: '");
        Serial.print(uart_buffer);
        Serial.print("' \n-> ");
      }

      uart_buffer_len = 0;
    }
  }
}

void loop()
{
  tick_blink();
  tick_uart();
}
