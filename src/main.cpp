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


#include <ESPAsyncWebServer.h>

#include <ElegantOTA.h>


#include "functions.h"
#include "index_html_file.h"

#define SCK_PIN1 18
#define CS_PIN1 5
#define SO_PIN1 19

#define SCK_PIN2 14
#define CS_PIN2 12
#define SO_PIN2 13

double tempEvacuare = 0;
double tempApa = 0;

int kontor = 0;

double Sneck_perioadaArdere = 12;
double Sneck_timpArdere = 2.7;

String stareVentilator = "OFF";
String stareRezistenta = "OFF";
String stareSneck = "OFF";
String starePompa = "OFF";

String tempDormitor;
String tempDressing;
String tempTerasa;
String tempLiving;

WiFiClient client;
HTTPClient http;

Ticker startSneckAprindere;
Ticker perioadaSneckArdereOn;
Ticker perioadaSneckArdereOff;
Ticker perioadaAprindere;
Ticker curatareFinal;
Ticker perioadaStabil;
Ticker perioadaSneckStabilOn;
Ticker perioadaSneckStabilOff;
Ticker startVentilatorAprindere;
Ticker stareTempEvac;
Ticker Pompa;
Ticker preStabilP;
Ticker pompaFinal;
Ticker rezistentaApr;
Ticker rezistentaAprindereTimer;

int sneck = 4;
int ventilator = 16;
int rezistenta = 17;
int pompa = 18;

double tempApa1 = 0;

int rest = 0;



float temp_centrala = 0;

int val = 0;
double temperaturaAprindereInitiala;
double temperaturaAprindereCurenta;
double temperaturaArdereCurenta;
int modulatie = 0;


unsigned long lastTime = 0;
unsigned long timerDelay = 9000;

const char *PARAM_INPUT_10 = "input10";
const char *PARAM_INPUT_11 = "input11";
const char *PARAM_INPUT_12 = "input12";
const char *PARAM_INPUT_13 = "input13";
const char *PARAM_INPUT_14 = "input14";
const char *PARAM_INPUT_15 = "input15";
const char *PARAM_INPUT_16 = "input16";
const char *PARAM_INPUT_17 = "input17";

AsyncWebServer server(4444);

Thermocouple *temp_evacuare = new MAX6675_Thermocouple(SCK_PIN1, CS_PIN1, SO_PIN1);
Thermocouple *temp_apa = new MAX6675_Thermocouple(SCK_PIN2, CS_PIN2, SO_PIN2);

String readMAXTemperature(Thermocouple *temp_evacuare) {
  tempEvacuare = temp_evacuare->readCelsius();
  return String(tempEvacuare);
}

double readMAXTemperature_double(Thermocouple *temp_evacuare) {
  tempEvacuare = temp_evacuare->readCelsius();
  return tempEvacuare;
}

String readMAXTemperature1(Thermocouple *temp_apa) {
  tempApa = temp_apa->readCelsius();
  return String(tempApa);
}

String readStatus(int kontor) {
  if (kontor == 1) {
    return "Aprindere";
  }
  if (kontor == 2) {
    return "Stabil";
  }
  if (kontor == 3) {
    return "Ardere";
  }
  if (kontor == 4) {
    return "Stop Ardere";
  }
  if (kontor == 7) {
    return "Eroare Aprindere";
  }
  if (kontor == 8) {
    return "Eroare Ardere";
  }
  return "OFF";
}

String processor(const String &var) {
  if (var == "TEMPERATUREC") {
    return readMAXTemperature1(temp_apa);
  }
  if (var == "TEMPERATUREE") {
    return readMAXTemperature(temp_evacuare);
  }
  if (var == "STATUS") {
    return readStatus(kontor);
  }
  if (var == "SNEPERARD") {
    return String(Sneck_perioadaArdere);
  }
  if (var == "SNETIMARD") {
    return String(Sneck_timpArdere);
  }
  if (var == "VENTIL") {
    return stareVentilator;
  }
  if (var == "SNECK") {
    return stareSneck;
  }
  if (var == "REZISTENTA") {
    return stareRezistenta;
  }
  if (var == "POMPA") {
    return starePompa;
  }
  if (var == "VALKONTOR") {
    return String(kontor);
  }
  if (var == "DORMITOR") {
    return tempDormitor;
  }
  if (var == "DRESSING") {
    return tempDressing;
  }
  if (var == "TERASA") {
    return tempTerasa;
  }
  if (var == "LIVING") {
    return tempLiving;
  }
  return String();
}

String temper(String loc) {
  String url_locatie;
  String raspuns;
  if (loc == "dressing") {
    url_locatie = "http://192.168.1.196:5555/temperature";
  }
  if (loc == "terasa") {
    url_locatie = "http://192.168.1.116:5555/temperature";
  }
  if (loc == "dormitor") {
    url_locatie = "http://192.168.1.182:5555/temperature";
  }
  if (loc == "living") {
    url_locatie = "http://192.168.1.42:5555/temperature";
  }
  http.begin(client, url_locatie.c_str());
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
    
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
    String payload = http.getString();
    Serial.println(loc + ": " + payload);
    raspuns = payload;
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return raspuns;
}

void pFinal() {
  pompaFinal.detach();
  digitalWrite(pompa, LOW);
  starePompa = "OFF";
}

void ventilatorFin() {
  curatareFinal.detach();
  digitalWrite(ventilator, LOW);
  stareVentilator = "OFF";
  kontor = 0;
  EEPROM.put(0, kontor);
  EEPROM.commit();
  EEPROM.put(12, 0);
  EEPROM.commit();
  EEPROM.put(8, 0);
  EEPROM.commit();
  pompaFinal.attach(120, pFinal);
}

void eroare(int x) {
  kontor = x;
  perioadaSneckArdereOn.detach();
  perioadaSneckArdereOff.detach();
  EEPROM.put(0, kontor);
  EEPROM.commit();
  EEPROM.put(12, 0);
  EEPROM.commit();
  EEPROM.put(8, 0);
  EEPROM.commit();
}

void stopSneckArdere() {
  perioadaSneckArdereOff.detach();
  digitalWrite(sneck, LOW);
  stareSneck = "OFF";
}

void stopArdere() {
  perioadaSneckArdereOn.detach();
  perioadaSneckArdereOff.detach();
  curatareFinal.attach(350, ventilatorFin);
  digitalWrite(sneck, LOW);
  stareSneck = "OFF";
  kontor = 4;
  EEPROM.put(0, kontor);
  EEPROM.commit();
}

void startSneckArdere() {
  if (val == 0) {
    perioadaSneckArdereOn.detach();
    perioadaSneckArdereOff.detach();
    stopArdere();
  } else {
    temperaturaArdereCurenta = temp_evacuare->readCelsius();
    if (temperaturaArdereCurenta < 30) {
      perioadaSneckArdereOn.detach();
      perioadaSneckArdereOff.detach();
      eroare(8);
    } else {
      perioadaSneckArdereOn.detach();
      perioadaSneckArdereOn.attach(Sneck_perioadaArdere, startSneckArdere);
      perioadaSneckArdereOff.attach(Sneck_timpArdere, stopSneckArdere);
      digitalWrite(sneck, HIGH);
      stareSneck = "ON";
    }
  }
}

void ardere() {
  perioadaAprindere.detach();
  kontor = 3;
  EEPROM.put(0, kontor);
  EEPROM.commit();
  digitalWrite(ventilator, HIGH);
  stareVentilator = "ON";
  digitalWrite(pompa, HIGH);
  starePompa = "ON";
  perioadaSneckArdereOn.attach(Sneck_perioadaArdere, startSneckArdere);
}

void stopAprindere() {
  perioadaAprindere.detach();
  startVentilatorAprindere.detach();
  stareTempEvac.detach();
  digitalWrite(rezistenta, LOW);
  stareRezistenta = "OFF";
  digitalWrite(ventilator, LOW);
  stareVentilator = "OFF";
  eroare(7);
}

void stabilArdere() {
  perioadaStabil.detach();
  ardere();
}

void stabilAprindere3() {
  perioadaSneckStabilOff.detach();
  perioadaAprindere.detach();
  digitalWrite(sneck, LOW);
  stareSneck = "OFF";
}

void stabilArdere1() {
  perioadaSneckStabilOn.detach();
  perioadaAprindere.detach();
  digitalWrite(sneck, HIGH);
  stareSneck = "ON";
  perioadaSneckStabilOff.attach(5, stabilAprindere3);
}

void stareTemperaturaEvac() {
  temperaturaAprindereCurenta = temp_evacuare->readCelsius();
  if (temperaturaAprindereCurenta - temperaturaAprindereInitiala > 10) {
    stareTempEvac.detach();
    perioadaAprindere.detach();
    startVentilatorAprindere.detach();
    rezistentaAprindereTimer.detach();
    digitalWrite(rezistenta, LOW);
    stareRezistenta = "OFF";
    digitalWrite(ventilator, HIGH);
    stareVentilator = "ON";
    perioadaStabil.attach(120, stabilArdere);
    perioadaSneckStabilOn.attach(55, stabilArdere1);
    kontor = 2;
    EEPROM.put(0, kontor);
    EEPROM.commit();
  }
}

void pompa_stare() {
  temp_centrala = temp_apa->readCelsius();
  tempEvacuare = temp_evacuare->readCelsius();

  if (temp_centrala >= 40) {
    digitalWrite(pompa, HIGH);
    starePompa = "ON";
    if (temp_centrala > 64 && kontor == 3) {
      if (modulatie == 0) {
        modulatie = 1;
        Sneck_perioadaArdere += 5;
      }
    }
    if (temp_centrala < 64 && kontor == 3) {
      if (modulatie == 1) {
        modulatie = 0;
        Sneck_perioadaArdere -= 5;
      }
    }
    if (temp_centrala > 70 && kontor == 3) {
      stopArdere();
    }
  } else {
    digitalWrite(pompa, LOW);
    starePompa = "OFF";
  }
}

void ventAprin() {
  digitalWrite(ventilator, !digitalRead(ventilator));
  if (digitalRead(ventilator) == HIGH) {
    stareVentilator = "ON";
  } else {
    stareVentilator = "OFF";
  }
}

void rezistentaAprindere() {
  rezistentaAprindereTimer.detach();
  startVentilatorAprindere.attach(8, ventAprin);
}

void stopSneck() {
  kontor = 1;
  EEPROM.put(0, kontor);
  EEPROM.commit();
  startSneckAprindere.detach();
  digitalWrite(sneck, LOW);
  stareSneck = "OFF";
  perioadaAprindere.attach(900, stopAprindere);
  digitalWrite(rezistenta, HIGH);
  stareRezistenta = "ON";
  rezistentaAprindereTimer.attach(120, rezistentaAprindere);
  stareTempEvac.attach(3, stareTemperaturaEvac);
}

void aprindere() {
  kontor = 1;
  EEPROM.put(0, kontor);
  EEPROM.commit();
  digitalWrite(sneck, HIGH);
  stareSneck = "ON";
  digitalWrite(rezistenta, LOW);
  stareRezistenta = "OFF";
  startSneckAprindere.attach(100, stopSneck);
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println();

  WiFi.begin("TP-Link_06E8", "92511163");
  // IPAddress ip(192, 168, 0, 39);
  // IPAddress gateway(192, 168, 0, 1);
  // IPAddress subnet(255, 255, 255, 0);
  // WiFi.config(ip, gateway, subnet);
  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  EEPROM.begin(32);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html, processor);
  });
  server.on("/temperaturec", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readMAXTemperature1(temp_apa).c_str());
  });
  server.on("/temperaturee", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readMAXTemperature(temp_evacuare).c_str());
  });
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readStatus(kontor).c_str());
  });
  server.on("/sneperard", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(Sneck_perioadaArdere).c_str());
  });
  server.on("/snetimard", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(Sneck_timpArdere).c_str());
  });
  server.on("/vent1", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(stareVentilator).c_str());
  });
  server.on("/sneck1", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(stareSneck).c_str());
  });
  server.on("/rezist1", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(stareRezistenta).c_str());
  });
  server.on("/pompa1", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(starePompa).c_str());
  });
  server.on("/vKontor", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(kontor).c_str());
  });
  server.on("/dormitor", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tempDormitor).c_str());
  });

  server.on("/dressing", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tempDressing).c_str());
  });

  server.on("/terasa", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tempTerasa).c_str());
  });

  server.on("/living", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tempLiving).c_str());
  });
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_14)) {
      inputMessage = request->getParam(PARAM_INPUT_14)->value();
      inputParam = PARAM_INPUT_14;
      if (inputMessage == "START") {
        digitalWrite(ventilator, HIGH);
        stareVentilator = "ON";
      }
      if (inputMessage == "STOP") {
        digitalWrite(ventilator, LOW);
        stareVentilator = "OFF";
      }
    }
    if (request->hasParam(PARAM_INPUT_15)) {
      inputMessage = request->getParam(PARAM_INPUT_15)->value();
      inputParam = PARAM_INPUT_15;
      if (inputMessage == "START") {
        digitalWrite(sneck, HIGH);
        stareSneck = "ON";
      }
      if (inputMessage == "STOP") {
        digitalWrite(sneck, LOW);
        stareSneck = "OFF";
      }
    }
    if (request->hasParam(PARAM_INPUT_16)) {
      inputMessage = request->getParam(PARAM_INPUT_16)->value();
      inputParam = PARAM_INPUT_16;
      if (inputMessage == "START") {
        digitalWrite(rezistenta, HIGH);
        stareRezistenta = "ON";
      }
      if (inputMessage == "STOP") {
        digitalWrite(rezistenta, LOW);
        stareRezistenta = "OFF";
      }
    }
    if (request->hasParam(PARAM_INPUT_17)) {
      inputMessage = request->getParam(PARAM_INPUT_17)->value();
      inputParam = PARAM_INPUT_17;
      if (inputMessage == "START") {
        digitalWrite(pompa, HIGH);
        starePompa = "ON";
      }
      if (inputMessage == "STOP") {
        digitalWrite(pompa, LOW);
        starePompa = "OFF";
      }
    }
    if (request->hasParam(PARAM_INPUT_10)) {
      inputMessage = request->getParam(PARAM_INPUT_10)->value();
      inputParam = PARAM_INPUT_10;
      if (inputMessage == "START") {
        val = 1;
        EEPROM.put(4, val);
        EEPROM.commit();

        if (kontor == 0) {
          EEPROM.put(8, temperaturaAprindereInitiala);
          EEPROM.commit();
          aprindere();
        }
      }
      if (inputMessage == "STOP") {
        val = 0;
        EEPROM.put(4, val);
        EEPROM.commit();
      }
      if (inputMessage == "RESTART") {
        ESP.restart();
      }
      if (inputMessage == "APRIND") {
        aprindere();
      }
      if (inputMessage == "RESETCONTOR") {
        EEPROM.put(12, 0);
        EEPROM.commit();
      }
      if (inputMessage == "OF") {
        startSneckAprindere.detach();
        perioadaSneckArdereOn.detach();
        perioadaSneckArdereOff.detach();
        perioadaAprindere.detach();
        curatareFinal.detach();
        perioadaStabil.detach();
        perioadaSneckStabilOn.detach();
        perioadaSneckStabilOff.detach();
        startVentilatorAprindere.detach();
        stareTempEvac.detach();
        preStabilP.detach();
        pompaFinal.detach();
        rezistentaApr.detach();
        rezistentaAprindereTimer.detach();
      }
    } else if (request->hasParam(PARAM_INPUT_11)) {
      inputMessage = request->getParam(PARAM_INPUT_11)->value();
      inputParam = PARAM_INPUT_11;
      Sneck_perioadaArdere = String(inputMessage).toFloat();
    } else if (request->hasParam(PARAM_INPUT_12)) {
      inputMessage = request->getParam(PARAM_INPUT_12)->value();
      inputParam = PARAM_INPUT_12;
      Sneck_timpArdere = String(inputMessage).toDouble();
      EEPROM.put(16, Sneck_timpArdere);
      EEPROM.commit();
    } else if (request->hasParam(PARAM_INPUT_13)) {
      inputMessage = request->getParam(PARAM_INPUT_13)->value();
      inputParam = PARAM_INPUT_13;
      kontor = String(inputMessage).toFloat();
      EEPROM.put(0, kontor);
      EEPROM.commit();
      if (kontor == 1) {
        temperaturaAprindereInitiala = readMAXTemperature_double(temp_evacuare);
        EEPROM.put(8, temperaturaAprindereInitiala);
        EEPROM.commit();
        aprindere();
      }
      if (kontor == 2) {
        digitalWrite(rezistenta, LOW);
        stareRezistenta = "OFF";
        digitalWrite(ventilator, HIGH);
        stareVentilator = "ON";
        perioadaStabil.attach(120, stabilArdere);
        perioadaSneckStabilOn.attach(55, stabilArdere1);
      }
      if (kontor == 3) {
        ardere();
      }
      if (kontor == 4) {
        stopArdere();
      }
      if (kontor == 7) {
        eroare(7);
      }
      if (kontor == 8) {
        eroare(8);
      }
      if (kontor == 6) {
        // temperaturaAprindereInitiala = temp_evacuare->readCelsius();
        temperaturaAprindereInitiala = readMAXTemperature_double(temp_evacuare);
        EEPROM.put(8, temperaturaAprindereInitiala);
        EEPROM.commit();
        stopSneck();
      }
    }
    request->send(200, "text/html", index_html, processor);
  });
  ElegantOTA.begin(&server);

  server.begin();

  pinMode(sneck, OUTPUT);
  pinMode(ventilator, OUTPUT);
  pinMode(rezistenta, OUTPUT);
  pinMode(pompa, OUTPUT);

  digitalWrite(sneck, LOW);
  stareSneck = "OFF";
  digitalWrite(pompa, LOW);
  starePompa = "OFF";
  digitalWrite(ventilator, LOW);
  stareVentilator = "OFF";
  digitalWrite(rezistenta, LOW);
  stareRezistenta = "OFF";
  Pompa.attach(3, pompa_stare);
  EEPROM.get(0, kontor);
  EEPROM.get(16, Sneck_timpArdere);
  EEPROM.get(4, val);

  //EEPROM.put(12, 0);
  //EEPROM.commit();
  EEPROM.get(12, rest);

  if (kontor == 1) {
    EEPROM.get(8, temperaturaAprindereInitiala);
    aprindere();
  }
  if (kontor == 2) {
    perioadaStabil.attach(120, stabilArdere);
    perioadaSneckStabilOn.attach(55, stabilArdere1);
  }
  if (kontor == 3) {
    ardere();
  }
  if (kontor == 4) {
    stopArdere();
  }
  if (kontor == 7) {
    eroare(7);
  }
  if (kontor == 8) {
    eroare(8);
  }
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){

      tempDormitor = temper("dormitor");
      tempDressing = temper("dressing");
      tempTerasa = temper("terasa");
      tempLiving = temper("living");

    Serial.println("-------------------------");

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
