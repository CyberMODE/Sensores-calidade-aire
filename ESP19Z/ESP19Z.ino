#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#include "MHZ19.h"
MHZ19 myMHZ19;
unsigned long getDataTimer = 0;
int i = 0;
int valor = 0;
int CO2; int mapCO2;
unsigned long intervalo = 150000;   //2' 30''
unsigned long millisAnterior = 0;                                 // Device to MH-Z19 Serial baudrate (should not be changed)

#include <SPI.h>
#include "epd1in54_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[1024];
Paint paint(image, 0, 0);

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1

unsigned long startTime = millis();

void setup() {
  Serial.begin(115200);

  myMHZ19.begin(Serial);
  myMHZ19.autoCalibration();             // Calibration ON (OFF autoCalibration(false))
  millisAnterior = millis();

  // e-Paper

  epd.LDirInit();
  epd.Clear();

}


void loop() {
  testlines();

  epd.Clear();

  paint.SetWidth(200);
  paint.SetHeight(24);

  Serial.println("e-Paper paint");
  paint.Clear(COLORED);
  paint.DrawStringAt(30, 4, "Amigus Labs", &Font16, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(30, 4, "e-Paper Demo", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(64);
  paint.SetHeight(64);


  delay(10000);


}



void testlines() {
  CO2 = myMHZ19.getCO2();                             // Solicita CO2 en ppm
  mapCO2 = map(CO2, 0, 2000, 0, 240);                 //Ajusta a display 240x320
  Serial.print("CO2 (ppm): ");
  Serial.print(CO2);
  Serial.print("-- mapCO2 (ppm): ");
  Serial.println(mapCO2);

  int8_t Temp;
  Temp = myMHZ19.getTemperature();                     // Temperatura en Celsius
  Serial.print("Temperature (C): ");
  Serial.println(Temp);


}
