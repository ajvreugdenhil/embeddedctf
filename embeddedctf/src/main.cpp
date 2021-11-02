#include <Arduino.h>

#ifdef SUPPORT_WIFI
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif

#ifdef FLAGLESS
#define BLINKFLAG "ECTF{PLACEHOLDER}"
#define UARTFLAG "ECTF{PLACEHOLDER}"
#define UNDOCUMENTEDUARTFLAG "ECTF{PLACEHOLDER}"
#define BOFFLAG "ECTF{PLACEHOLDER}"
#define NETWORKFLAG "ECTF{PLACEHOLDER}"
#else
#define BLINKFLAG "ECTF{Embedded_d3v_is_just_f4ncy_blinking}"
#define UARTFLAG "ECTF{Uart_1s_lov3_uart_1s_lif3}"
#define UNDOCUMENTEDUARTFLAG "ECTF{rtfm_with_sc3pticism}"
#define BOFFLAG "ECTF{Bof_on_emb3dded!}"
#define NETWORKFLAG "ECTF{my_s3cr3ts_are_not_5afe_for_you}"
#endif

#define UARTKEY "S3CRIT_UART_KEY"
#define WELCOMEFLAG "ECTF{Str1ngs_1s_y0ur_fri3nd}"

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
  String welcomeflag = WELCOMEFLAG;
  Serial.print("Version: ");
  Serial.println(ECTF_VERSION);
  Serial.print("An interesting function can be found at 0x");
  Serial.println((unsigned long)&print_bof_flag, HEX);
#ifdef SUPPORT_WIFI
  WiFi.softAPdisconnect(true);
#endif
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
  Serial.println("uartflag");
  Serial.println("networkcheck <ssid> <password>");
  Serial.println("integritycheck");
}

void shell_uart_flag()
{
  Serial.println(UARTFLAG);
}

#ifdef SUPPORT_WIFI
void shell_network_check(char *user_input)
{
  WiFi.disconnect(true);

  const int user_input_max = 64;
  char ignored[user_input_max];
  char ssid[user_input_max];
  char password[user_input_max];
  sscanf(user_input, "%s %s %s", ignored, ssid, password);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to AP");

  int i = 0;
  while ((WiFi.status() != WL_CONNECTED) && i < 60)
  {
    delay(500);
    Serial.print(".");
    i++;
  }

  Serial.println("");

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    WiFiClient client;
    HTTPClient http;
    Serial.println("Trying to contact remote server...");

    const int remote_len = 80;
    char remote[remote_len];
    snprintf(remote, remote_len, "http://binpurple.student.fhict.nl?flag=%s", NETWORKFLAG);
    http.begin(client, remote);
    http.GET();
    Serial.println("Remote server seems to be offline.");
    WiFi.disconnect(true);
  }
  else
  {
    Serial.println("Could not connect!");
  }
}
#else
void shell_network_check(char *user_input)
{
  Serial.println("ECTF was compiled without network support!");
}
#endif

#ifdef SUPPORT_I2C
void shell_i2c()
{
  Serial.println("This part of the ctf is WIP and not functioning");
}
#else
void shell_i2c()
{
  Serial.println("ECTF was compiled without I2C support!");
}
#endif

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
      else if (strncmp(uart_buffer, "networkcheck", 12) == 0)
      {
        shell_network_check(uart_buffer);
      }
      else if (strncmp(uart_buffer, "uartflag", 9) == 0)
      {
        shell_uart_flag();
      }
      else if (strncmp(uart_buffer, "integritycheck", 15) == 0)
      {
        shell_i2c();
      }
      else if (uart_buffer_len < 2)
      {
        // do nothing
      }
      else if (strcmp(uart_buffer, UARTKEY) == 0)
      {
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
