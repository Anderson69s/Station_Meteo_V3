#include <LiquidCrystal.h>//lcd librairie
#include <Wire.h>// wire librairie for i2c
#include <ChainableLED.h>//chainable rgb led librarie
#include "Barometer.h"//bmp085 librarie
#include "RGBdriver.h"//led strip librarie
#include <AirQuality.h>//air quality sensor librarie
#include"Arduino.h"//air quality sensor librarie
#include "RTClib.h"//rtc librairie
LiquidCrystal lcd(44, 45, 46, 47, 48, 49);//define pin for lcd 20x4
#define CLK 10//pins definitions for the led strip driver
#define DIO 11//pins definitions for the led strip driver
RGBdriver Driver(CLK, DIO); //pins definitions for the led strip driver
#define NUM_LEDS  4//number of chainable rgb leds
ChainableLED leds(12, 13, NUM_LEDS);//pins of rgb chainable leds
Barometer myBarometer;//define t et p for bmp085
AirQuality airqualitysensor;//define class for airsnesor quality
int current_quality = -1; //define current quality for air quality sensor
RTC_DS1307 RTC;// define class for RTC

void setup()
{
  Serial.begin(9600);//start serial
  Wire.begin();//start I2C
  lcd.begin(20, 4);//start lcd 20x4
  myBarometer.init();//start bmp085
  airqualitysensor.init(7);//start air quality sensor
  RTC.begin();//start RTC
}
void loop()
{
  DateTime now = RTC.now();//read date & time
  delay(10); // little delay
  DateTime future (now.unixtime() + 7 * 86400L + 30);//calculate a future date
  delay(10);//little delay
  int t = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
  delay(10);//little delay
  double p = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); //Get the temperature
  delay(10);//little delay
  int range = map(t, -20, 60, 0, 5); //mapping t into range
  switch (range) {
  case 0:    //make white
    for (byte i = 0; i < NUM_LEDS; i++)
    {
      leds.setColorRGB(i, 255, 255, 255);
    }
    break;
  case 1:    //make blue
    for (byte i = 0; i < NUM_LEDS; i++)
    {
      leds.setColorRGB(i, 0, 0, 255);
    }
    break;
  case 2:    //make green
    for (byte i = 0; i < NUM_LEDS; i++)
    {
      leds.setColorRGB(i, 0, 255, 0);
    }
    break;
  case 3:    //make orange
    for (byte i = 0; i < NUM_LEDS; i++)
    {
      leds.setColorRGB(i, 255, 255, 0);
    }
    break;
  case 4:    //make red
    for (byte i = 0; i < NUM_LEDS; i++)
    {
      leds.setColorRGB(i, 255, 0, 0);
    }
    break;
  }
  current_quality = airqualitysensor.slope();
  if (current_quality >= 0)// if a valid data returned.
  {
    if (current_quality == 0) {
      Driver.begin();//led strip
      Driver.SetColor(0, 0, 255);//blue force signal active
      Driver.end();
    }
    else if (current_quality == 1) {
      Driver.begin();//led strip
      Driver.SetColor(255, 0, 0);// high pollution red
      Driver.end();
    }
    else if (current_quality == 2) {
      Driver.begin();//led strip
      Driver.SetColor(255, 255, 0);//low pollution green and red
      Driver.end();
    }
    else if (current_quality == 3) {
      Driver.begin();//led strip
      Driver.SetColor(0, 255, 0);//no pollution green
      Driver.end();
    }

  }
  //Printing information on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P:");
  lcd.print(p ,0);
  lcd.print("        T:");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.setCursor(0, 2);
  lcd.print("     ");
  lcd.print(now.year(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  lcd.setCursor(0, 3);
  lcd.print("   ");
  lcd.print("By Anderson69s");
  //LCD END
  //Sending data to serial
  Serial.print(p);
  Serial.print('/');
  Serial.print(t);
  Serial.print('\n');//very important!!!!!
  delay(2000);
}


ISR(TIMER2_OVF_vect)
{
  if (airqualitysensor.counter == 122) //set 2 seconds as a detected duty
  {

    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = analogRead(A0);
    airqualitysensor.counter = 0;
    airqualitysensor.timer_index = 1;
    PORTB = PORTB ^ 0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}













