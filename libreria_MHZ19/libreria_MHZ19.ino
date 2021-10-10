#include "MHZ19.h"
MHZ19 myMHZ19;
unsigned long getDataTimer = 0;
int i = 0;
int valor = 0;
int CO2; int mapCO2;
unsigned long intervalo = 150000;   //2' 30''
unsigned long millisAnterior = 0;                                 // Device to MH-Z19 Serial baudrate (should not be changed)


void setup()
{
  Serial.begin(9600);                                     // Device to serial monitor feedback



  myMHZ19.begin(Serial);
  myMHZ19.autoCalibration();             // Calibration ON (OFF autoCalibration(false))
  millisAnterior = millis();


}

void loop()
{
  testlines();
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
