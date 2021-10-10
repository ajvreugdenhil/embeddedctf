#include <Arduino.h>

#define FLAGLESS 1

#ifdef FLAGLESS
#define BLINKFLAG "ECTF{PLACEHOLDER}"
#define UARTFLAG "ECTF{PLACEHOLDER}"
#define UNDOCUMENTEDUARTFLAG "ECTF{PLACEHOLDER}"
#define BOFFLAG "ECTF{PLACEHOLDER}"
#else
#define BLINKFLAG "ECTF{BLINK}"
#define UARTFLAG "ECTF{UART}"
#define UNDOCUMENTEDUARTFLAG "ECTF{UNDOC_UART}"
#define BOFFLAG "ECTF{BOF}"
#endif

#define UARTKEY "TODO"

#define BLINKLED LED_BUILTIN_AUX

unsigned int previous_tick = 0;

void print_bof_flag()
{
  Serial.println(BOFFLAG);
}

void setup()
{
  Serial.begin(57600);
  pinMode(BLINKLED, OUTPUT);
  Serial.printf("An interesting function can be found at 0x%lx", ((unsigned long)(&print_bof_flag)));
}

void tick_blink()
{
  char blink_flag[] = BLINKFLAG;
  int blink_flag_length = strlen(blink_flag);
  int step = (millis() / 100) % (blink_flag_length * 8);
  pinMode(BLINKLED, ((blink_flag[((int)step / 8)] >> (step % 8))) & 1);
}

void shell_help()
{
  Serial.println("Available commands:");
  Serial.println("help");
  Serial.println("networkcheck");
  Serial.println("showuartflag");
  Serial.println("i2ctest");
}

void shell_uart_flag()
{
  Serial.println(UARTFLAG);
}

void shell_network_check()
{
  Serial.println("This part of the ctf is WIP");
}

void shell_i2c_test()
{
  Serial.println("This part of the ctf is WIP");
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
      Serial.println();
      uart_buffer[uart_buffer_len - 1] = '\0';
      if (strcmp(uart_buffer, "help") == 0)
      {
        shell_help();
      }
      else if (strncmp(uart_buffer, "networkcheck", 13) == 0)
      {
        shell_network_check();
      }
      else if (strncmp(uart_buffer, "showuartflag", 13) == 0)
      {
        shell_uart_flag();
      }
      else if (strncmp(uart_buffer, "i2ctest", 8) == 0)
      {
        shell_i2c_test();
      }
      else if (uart_buffer_len < 2)
      {
        // do nothing
      }
      else if (strcmp(uart_buffer, UARTKEY) == 0)
      {
        Serial.print("\nCongrats on finding the undocumented command! Here's the flag: ");
        Serial.println(UNDOCUMENTEDUARTFLAG);
      }
      else
      {
        Serial.print(uart_buffer);
        Serial.println(": command not found");
        shell_help();
      }
      Serial.print("\n-> ");

      uart_buffer_len = 0;
    }
  }
}

void loop()
{
  tick_blink();
  tick_uart();
}
