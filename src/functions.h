#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Arduino.h>
#include <Ticker.h>
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <EEPROM.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#endif

// #define SCK_PIN1 18
// #define CS_PIN1 5
// #define SO_PIN1 19

// #define SCK_PIN2 14
// #define CS_PIN2 12
// #define SO_PIN2 13

// double tempEvacuare = 0;
// double tempApa = 0;

// int kontor = 0;

// double Sneck_perioadaArdere = 12;
// double Sneck_timpArdere = 2.7;

// String stareVentilator = "OFF";
// String stareRezistenta = "OFF";
// String stareSneck = "OFF";
// String starePompa = "OFF";

// String tempDormitor;
// String tempDressing;
// String tempTerasa;
// String tempLiving;

// WiFiClient client;
// HTTPClient http;

// Ticker startSneckAprindere;
// Ticker perioadaSneckArdereOn;
// Ticker perioadaSneckArdereOff;
// Ticker perioadaAprindere;
// Ticker curatareFinal;
// Ticker perioadaStabil;
// Ticker perioadaSneckStabilOn;
// Ticker perioadaSneckStabilOff;
// Ticker startVentilatorAprindere;
// Ticker stareTempEvac;
// Ticker Pompa;
// Ticker preStabilP;
// Ticker pompaFinal;
// Ticker rezistentaApr;
// Ticker rezistentaAprindereTimer;

// int sneck = 4;
// int ventilator = 16;
// int rezistenta = 17;
// int pompa = 18;

// double tempApa1 = 0;

// int rest = 0;



// float temp_centrala = 0;

// int val = 0;
// double temperaturaAprindereInitiala;
// double temperaturaAprindereCurenta;
// double temperaturaArdereCurenta;
// int modulatie = 0;

// String readMAXTemperature();
// double readMAXTemperature_double();
// String readMAXTemperature1();
// String readStatus(int kontor);
// String processor(const String &var);
// String temper(String loc);
// void pFinal();
// void ventilatorFin();
// void eroare(int x);
// void stopSneckArdere();
// void stopArdere();
// void startSneckArdere();
// void ardere();
// void stopAprindere();
// void stabilArdere();
// void stabilAprindere3();
// void stabilArdere1();
// void stareTemperaturaEvac();
// void pompa_stare();
// void ventAprin();
// void rezistentaAprindere();
// void stopSneck();
// void aprindere();





#endif