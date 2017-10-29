
/*
 * Demo for SSD1306 based 128x64 OLED module using Adafruit SSD1306
 * library (https://github.com/adafruit/Adafruit_SSD1306).
 *
 * See https://github.com/pacodelgado/arduino/wiki/SSD1306-based-OLED-connected-to-Arduino
 * for more information.
 *
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI  11   //D1
#define OLED_CLK   12   //D0
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()   {
//  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
  #endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // adjust date and time
  //rtc.adjust(DateTime(2017, 10, 29, 19, 29, 0));
}

void loop()
{
  DateTime now = rtc.now();

  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;
  display.clearDisplay();
  display.setCursor(0,0);

  // time
  display.print(now.hour());
  display.print(":");
  display.print(now.minute());
  display.print(":");
  display.print(now.second());
  display.print("\n");

  // date
  display.print(now.day());
  display.print("-");
  display.print(now.month());
  display.print("-");
  display.print(now.year());
  display.print("\n");

  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print("\n");

  display.print("Temp: 23C \n");

  display.display();
}
