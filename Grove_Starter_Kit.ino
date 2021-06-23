#include <U8g2lib.h>
#include <Wire.h>
#include <MsTimer2.h>
#include "DHT.h"
#include "Seeed_BMP280.h"
#include "LIS3DHTR.h"
#define WIRE Wire

//20*20
const unsigned char sound_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3e, 0x00, 0x80, 0x3f, 0x0c, 0xc0, 0x3b, 0x0c, 0xfe, 0xb8, 0x0d, 0x7f, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0xff, 0xb8, 0x0d, 0xc0, 0x39, 0x0c, 0x80, 0x3f, 0x0c, 0x00, 0x3e, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00};
//20*30
const unsigned char temp_bmp[] U8X8_PROGMEM = {0x00, 0x06, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x80, 0x19, 0x00, 0x80, 0x19, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x3f, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x06, 0x00};
//20*20
const unsigned char hum_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x20, 0x40, 0x00, 0x20, 0x40, 0x00, 0x10, 0x80, 0x00, 0x10, 0x80, 0x00, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x80, 0x10, 0x00};
//20*20
const unsigned char pressure_bmp1[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x80, 0x96, 0x01, 0x80, 0x1f, 0x03, 0x00, 0x0f, 0x06, 0x18, 0x06, 0x04, 0x1c, 0x04, 0x04, 0x06, 0x00, 0x06, 0xc6, 0xff, 0x03, 0xc6, 0xff, 0x01, 0x04, 0x00, 0x00, 0xfc, 0xff, 0x03, 0xf8, 0xff, 0x03, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0x00, 0x00, 0x00};
//30*30
const unsigned char pressure_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc8, 0xc4, 0x01, 0x00, 0xf8, 0x87, 0x07, 0x00, 0xf8, 0x87, 0x07, 0x60, 0xf0, 0x03, 0x04, 0x60, 0xf0, 0x03, 0x04, 0xf0, 0xc0, 0x00, 0x04, 0xf0, 0xc0, 0x00, 0x04, 0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 0x08, 0xfc, 0xff, 0x03, 0x08, 0xfc, 0xff, 0x03, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//30*30
const unsigned char light_tmp[] U8X8_PROGMEM = {0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0xc1, 0x60, 0x00, 0x80, 0xc3, 0x70, 0x00, 0x00, 0xc3, 0x30, 0x00, 0x00, 0xc7, 0x38, 0x00, 0x00, 0x06, 0x18, 0x00, 0x0c, 0xf0, 0x03, 0x0c, 0x3c, 0xfc, 0x0f, 0x0f, 0x78, 0x1e, 0x9e, 0x07, 0x60, 0x07, 0xb8, 0x01, 0x00, 0x03, 0x30, 0x00, 0x80, 0x03, 0x70, 0x00, 0x80, 0x01, 0x60, 0x00, 0xbf, 0x01, 0x60, 0x3f, 0xbf, 0x01, 0x60, 0x3f, 0x80, 0x01, 0x60, 0x00, 0x80, 0x03, 0x70, 0x00, 0x00, 0x03, 0x30, 0x00, 0x60, 0x07, 0xb8, 0x01, 0x78, 0x1e, 0x9e, 0x07, 0x3c, 0xfc, 0x0f, 0x0f, 0x0c, 0xf0, 0x03, 0x0c, 0x00, 0x06, 0x18, 0x00, 0x00, 0xc7, 0x38, 0x00, 0x00, 0xc3, 0x30, 0x00, 0x80, 0xc3, 0x70, 0x00, 0x80, 0xc1, 0x60, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00};
//30*30
const unsigned char sound_bmp1[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x70, 0xc0, 0x00, 0x00, 0x48, 0x80, 0x01, 0x00, 0x4c, 0x18, 0x03, 0x00, 0x46, 0x30, 0x02, 0x00, 0x43, 0x60, 0x04, 0x80, 0x41, 0x43, 0x04, 0xfc, 0x40, 0x84, 0x08, 0x46, 0x40, 0x8c, 0x08, 0x46, 0x40, 0x88, 0x08, 0x46, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x19, 0x06, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x09, 0x46, 0x40, 0x18, 0x09, 0x46, 0x40, 0x88, 0x08, 0x46, 0x40, 0x8c, 0x08, 0xfc, 0x40, 0x86, 0x0c, 0x80, 0x41, 0x43, 0x04, 0x00, 0x43, 0x20, 0x04, 0x00, 0x42, 0x30, 0x02, 0x00, 0x44, 0x0c, 0x03, 0x00, 0x48, 0x80, 0x01, 0x00, 0x50, 0xc0, 0x00, 0x00, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//30*30
const unsigned char acel_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0x07, 0x1c, 0x00, 0x80, 0x01, 0x60, 0x00, 0x60, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x02, 0x08, 0x00, 0x00, 0x04, 0x0c, 0x00, 0x00, 0x04, 0x04, 0x20, 0x01, 0x08, 0x04, 0x10, 0x02, 0x08, 0x02, 0xf8, 0x03, 0x08, 0x02, 0x0c, 0x0e, 0x10, 0x02, 0x0a, 0x10, 0x10, 0x02, 0x0a, 0x10, 0x10, 0x02, 0x02, 0x0a, 0x10, 0x02, 0x18, 0x06, 0x18, 0x06, 0x10, 0x02, 0x08, 0x04, 0x20, 0x01, 0x08, 0x04, 0xc0, 0x00, 0x0c, 0x08, 0x00, 0x00, 0x04, 0x18, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x03, 0x60, 0x00, 0x80, 0x01, 0xc0, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x30, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//30*30
const unsigned char temp_bmp1[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0x1f, 0x8f, 0xff, 0xff, 0x3f, 0x0f, 0x00, 0x00, 0x3e, 0x0f, 0x00, 0x00, 0x3e, 0x8f, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x07, 0xfc, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define BoardVersion 2
#if BoardVersion == 1
char led = 5;
char buzzer = 6;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);
char button = 2;
char rotary = A1;
char light = A2;
char sound = A0;
DHT dht(4, DHT11);
BMP280 bmp280;
// LIS3DHTR<TwoWire> accelemeter(I2C_MODE);
LIS3DHTR<TwoWire> accelemeter; //IIC
#elif BoardVersion == 2
char led = 4;
char buzzer = 5;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);
char button = 6;
char rotary = A0;
char light = A6;
char sound = A2;
DHT dht(3, DHT11);
BMP280 bmp280;
//LIS3DHTR<TwoWire> accelemeter(I2C_MODE);
LIS3DHTR<TwoWire> accelemeter; //IIC
#endif
#define CLICKS 100
int BuzzerFrequency = 300;
char MODE = 1; // original 1
char LongPress = false;
//int x = 50, y = 13;
int x = 80, y = 35;
char PressCounter = 0;
char BlinkEnable = true;
#define BLINK 10
#define SQueueLEN 10
int SQueue[SQueueLEN] = {0};

int alert[] = { 0, 0, 0, 0, 0 }; // Luz, sonido, temperatura, humedad, precion

#define NOTE_G6  1568
#define NOTE_C7  2093
#define NOTE_G7  3136
#define NOTE_E7  2637

int melody[] = {

  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

};

int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

void Checker() {
  static char LEDBlink = 0;
  if (BlinkEnable)
  {
    digitalWrite(led, HIGH);
    LEDBlink ++;
    if (LEDBlink > BLINK)
    {
      LEDBlink = 0;
      BlinkEnable = false;
      digitalWrite(led, LOW);
    }
  }
  if (digitalRead(button) == HIGH)
  {
    PressCounter ++;
    if (PressCounter > CLICKS)
    {
      PressCounter = CLICKS + 1;
    }
  }
  else
  {
    PressCounter = 0;
  }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!bmp280.init()) {
    Serial.println("bmp280 init error!");
  }
  //accelemeter.begin(Wire);
  accelemeter.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  //accelemeter.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  accelemeter.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);

  if (!accelemeter) {
    Serial.println("LIS3DHTR didn't connect.");
  }
  pinMode(rotary, INPUT);
  pinMode(button, INPUT);
  pinMode(light, INPUT);
  pinMode(sound, INPUT);
  for (int Index = 0 ; Index < SQueueLEN ; Index ++)
  {
    SQueue[Index] = analogRead(sound);
  }
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  u8g2.begin();
  MsTimer2::set(10, Checker); // 10ms period
  MsTimer2::start();
}

void loop() {
  if (digitalRead(button) == HIGH)
  {
    delay(5);
    if (digitalRead(button) == HIGH)
    {
      BlinkEnable = true;
      if (PressCounter > CLICKS)
      {
        PressCounter = 0;
        if (digitalRead(button) == HIGH)
        {
          LongPress = true;
          while (digitalRead(button))
          {
            if (LongPress)
            {
              LongPress = false;
              tone(buzzer, BuzzerFrequency);
              delay(200);
              noTone(buzzer);
            }
          }
          while (1)
          {
            int n = analogRead(rotary) / 204.8 + 1;
            digitalWrite(led, HIGH);
            digitalWrite(buzzer, LOW);
            select_mode(n);
            if (digitalRead(button) == HIGH)
            {
              delay(4);
              if (digitalRead(button) == HIGH)
              {
                MODE = analogRead(rotary) / 204.8 + 1;
                while (digitalRead(button));
                digitalWrite(led, LOW);
                digitalWrite(buzzer, LOW);
                break;
              }
            }
          }
        }
      }
    }
  }
  if (MODE == 1) {
    Light_show();
  } else if (MODE == 2) {
    Sound_show();
  } else if (MODE == 3) {
    Temp_show();
  } else if (MODE == 4) {
    Pressure_show();
  } else if (MODE == 5) {
    Acele_show();
  }
}
void select_mode(int n)
{
  switch (n)
  {
    case 1:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 16, 30, 30, light_tmp);
        u8g2.setCursor(44, 46);
        u8g2.print(F("Light")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 2:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, sound_bmp1);
        u8g2.setCursor(44, 48);
        u8g2.print(F("Sound")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 3:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_12b_mr);//
        u8g2.drawXBMP(49, 0, 30, 30, temp_bmp1);
        u8g2.setCursor(31, 35);
        u8g2.print(F("Temperature")); // write something to the internal memory
        u8g2.setCursor(43, 49);
        u8g2.print(F("Humidity"));    // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 4:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, pressure_bmp);
        u8g2.setCursor(16, 48);
        u8g2.print(F("Air Pressure")); // write something to the internal memory
      } while (u8g2.nextPage());

      break;
    case 5:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, acel_bmp);
        u8g2.setCursor(16, 48);
        u8g2.print(F("Acceleration")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
  }
}


void Light_show()
{
  int l = analogRead(light);
  Alert(50, l, 0); // int referencia, int Original, int Num
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.drawCircle(8, 8, 8, U8G2_DRAW_ALL);
    if (l >= 50 && l < 100) {
      u8g2.drawDisc(8, 8, 8, U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 100 & l < 200) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 200 && l < 350) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 350) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_ALL);
    }
    u8g2.setCursor(26, 32);
    u8g2.print(F("Light:"));
    u8g2.setCursor(80, 32);
    u8g2.print(l);
    u8g2.drawHLine(0, 48, 128);
  } while (u8g2.nextPage());
}

void Pressure_show()
{
  float pressure = bmp280.getPressure();
  Alert(35, pressure, 4); // int referencia, int Original, int Num

  Serial.println(pressure);
  u8g2.setFont(u8g2_font_t0_16b_mr);
  u8g2.firstPage();
  do {
    u8g2.setCursor(76, 32);
    u8g2.drawXBMP(0, 0, 20, 20, pressure_bmp1);
    u8g2.setCursor(30, 37);
    u8g2.print("Pressure:");
    u8g2.setCursor(25, 51);
    u8g2.print(pressure);
    u8g2.print("Pa");
  } while (u8g2.nextPage());
}

void Temp_show()
{
  int temp = 0, humid = 0;
  temp = dht.readTemperature();
  Alert(3, temp, 2); // int referencia, int Original, int Num
  humid = dht.readHumidity();
  Alert(10, humid, 3); // int referencia, int Original, int Num
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(32, 16);
    u8g2.print(F("temp:"));
    u8g2.setCursor(72, 16);
    u8g2.print(temp);
    u8g2.setCursor(88, 16);
    u8g2.print("C");
    u8g2.setCursor(32, 48);
    u8g2.print(F("humid:"));
    u8g2.setCursor(80, 48);
    u8g2.print(humid);
    u8g2.drawLine(25, 0, 25, 64);
    u8g2.drawLine(103, 0, 103, 64);
    u8g2.drawXBMP(0, 0, 20, 30, temp_bmp);
    u8g2.drawXBMP(0, 35, 20, 20, hum_bmp);
  } while (u8g2.nextPage());

}


void Sound_show()
{
  int s = analogRead(sound);
  s = filter1(s, SQueue, SQueueLEN);
  Alert(50, s, 1); // int referencia, int Original, int Num
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(28, 32);
    u8g2.print(F("Sound:"));
    u8g2.setCursor(76, 32);
    u8g2.drawXBMP(0, 0, 20, 20, sound_bmp);
    u8g2.print(s);
  } while (u8g2.nextPage());
}


int filter1(int NEW_DATA, int QUEUE[], char n)
{
  int max;
  int min;
  int sum;
  char i;
  QUEUE[0] = NEW_DATA;
  if (QUEUE[0] < 0)
    QUEUE[0] = 0;
  max = QUEUE[0];
  min = QUEUE[0];
  sum = QUEUE[0];
  for (i = n - 1; i != 0; i--) {
    if (QUEUE[i] > max)max = QUEUE[i];
    else if (QUEUE[i] < min)min = QUEUE[i];
    sum = sum + QUEUE[i];
    QUEUE[i] = QUEUE[i - 1];
  }

  i = n - 2;
  sum = sum - max - min + i / 2;
  sum = sum / i;

  return ((int)sum);
}

void Acele_show()
{
  float ax, ay, az;
  ax = accelemeter.getAccelerationX();
  ay = -accelemeter.getAccelerationY();
  az = accelemeter.getAccelerationZ();

  if (y >= 13 && x <= 108 ) {
    if (ay > 0.2 && ay < 0.5) {
      x = x + 1;
    } else if (ay >= 0.5 && ay < 0.8) {
      x = x + 2;
    } else if (ay >= 0.8) {
      x = x + 3;
    }
  }
  if (y < 57 && x >= 52) {
    if (ay < -0.2 && ay > -0.5) {
      x = x - 1;
    } else if (ay <= -0.5 && ay > -0.8) {
      x = x - 2;
    } else if (ay <= -0.8) {
      x = x - 3;
    }
  }

  if ( y <= 65 && y >= 13 ) {

    if (ax > 0.2 && ax < 0.5) {
      y = y - 1;
    } else if (ax >= 0.5 && ax < 0.8) {

      y = y - 2;
    } else if (ax >= 0.8) {
      y = y - 3;
    }
  }
  if ( y >= 10 && y <= 57  ) {

    if (ax < -0.2 && ax > -0.5) {

      y = y + 1;
    } else if (ax <= -0.5 && ax > -0.8) {

      y = y + 2;
    } else if (ax <= -0.8) {

      y = y + 3;
    }
  }


  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_12b_mr);
    u8g2.setCursor(0, 16);
    u8g2.print(F("X:"));
    u8g2.setCursor(16, 16);
    u8g2.print(ax);
    u8g2.setCursor(0, 32);
    u8g2.print(F("Y:"));
    u8g2.setCursor(16, 32);
    u8g2.print(ay);
    u8g2.setCursor(0, 48);
    u8g2.print(F("Z:"));
    u8g2.setCursor(16, 48);
    u8g2.print(az);
    u8g2.drawLine(50, 60, 50, 10);
    u8g2.drawLine(110, 10, 50, 10);
    u8g2.drawLine(110, 60, 50, 60);
    u8g2.drawLine(110, 60, 110, 10);

    u8g2.drawDisc(x, y, 3, U8G2_DRAW_ALL);

    Serial.println("");
    Serial.print("Eje x");
    Serial.println(ax);

    Serial.print("Eje y");
    Serial.println(ay);
    Serial.println("");

  } while (u8g2.nextPage());
}

void Alert( int referencia, int Original, int n ) {

  int resultado = Original - alert[n];

  if ( alert[n] == 0 ) {
    alert[n] = Original;
  }

  if ( resultado > referencia || resultado < -referencia ) {
    Serial.print("-----------");

    digitalWrite(led, HIGH);

    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(buzzer, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(buzzer, 0, noteDuration);

    }

    alert[n] = Original;

  } else {
    digitalWrite(led, LOW);
    noTone(buzzer);
  }

}



void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time…
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
  digitalWrite(13, LOW);

}
