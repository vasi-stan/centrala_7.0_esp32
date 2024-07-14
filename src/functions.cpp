#include "functions.h"


// Thermocouple *temp_evacuare = new MAX6675_Thermocouple(SCK_PIN1, CS_PIN1, SO_PIN1);
// Thermocouple *temp_apa = new MAX6675_Thermocouple(SCK_PIN2, CS_PIN2, SO_PIN2);

// String readMAXTemperature() {
//   tempEvacuare = temp_evacuare->readCelsius();
//   return String(tempEvacuare);
// }

// double readMAXTemperature_double() {
//   tempEvacuare = temp_evacuare->readCelsius();
//   return tempEvacuare;
// }

// String readMAXTemperature1() {
//   tempApa = temp_apa->readCelsius();
//   return String(tempApa);
// }

// String readStatus(int kontor) {
//   if (kontor == 1) {
//     return "Aprindere";
//   }
//   if (kontor == 2) {
//     return "Stabil";
//   }
//   if (kontor == 3) {
//     return "Ardere";
//   }
//   if (kontor == 4) {
//     return "Stop Ardere";
//   }
//   if (kontor == 7) {
//     return "Eroare Aprindere";
//   }
//   if (kontor == 8) {
//     return "Eroare Ardere";
//   }
//   return "OFF";
// }

// String processor(const String &var) {
//   if (var == "TEMPERATUREC") {
//     return readMAXTemperature1();
//   }
//   if (var == "TEMPERATUREE") {
//     return readMAXTemperature();
//   }
//   if (var == "STATUS") {
//     return readStatus();
//   }
//   if (var == "SNEPERARD") {
//     return String(Sneck_perioadaArdere);
//   }
//   if (var == "SNETIMARD") {
//     return String(Sneck_timpArdere);
//   }
//   if (var == "VENTIL") {
//     return stareVentilator;
//   }
//   if (var == "SNECK") {
//     return stareSneck;
//   }
//   if (var == "REZISTENTA") {
//     return stareRezistenta;
//   }
//   if (var == "POMPA") {
//     return starePompa;
//   }
//   if (var == "VALKONTOR") {
//     return String(kontor);
//   }
//   if (var == "DORMITOR") {
//     return tempDormitor;
//   }
//   if (var == "DRESSING") {
//     return tempDressing;
//   }
//   if (var == "TERASA") {
//     return tempTerasa;
//   }
//   if (var == "LIVING") {
//     return tempLiving;
//   }
//   return String();
// }

// String temper(String loc) {
//   String locatie;
//   String raspuns;
//   if (loc == "dressing") {
//     locatie = "http://192.168.1.196:5555/temperature";
//   }
//   if (loc == "terasa") {
//     locatie = "http://192.168.1.116:5555/temperature";
//   }
//   if (loc == "dormitor") {
//     locatie = "http://192.168.1.182:5555/temperature";
//   }
//   if (loc == "living") {
//     locatie = "http://192.168.1.42:5555/temperature";
//   }
//   http.begin(client, locatie.c_str());
  
//   // If you need Node-RED/server authentication, insert user and password below
//   //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
    
//   int httpResponseCode = http.GET();
  
//   if (httpResponseCode>0) {
//     String payload = http.getString();
//     Serial.println(loc + ": " + payload);
//     raspuns = payload;
//   }
//   else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
//   http.end();

//   return raspuns;
// }

// void pFinal() {
//   pompaFinal.detach();
//   digitalWrite(pompa, LOW);
//   starePompa = "OFF";
// }

// void ventilatorFin() {
//   curatareFinal.detach();
//   digitalWrite(ventilator, LOW);
//   stareVentilator = "OFF";
//   kontor = 0;
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
//   EEPROM.put(12, 0);
//   EEPROM.commit();
//   EEPROM.put(8, 0);
//   EEPROM.commit();
//   pompaFinal.attach(120, pFinal);
// }

// void eroare(int x) {
//   kontor = x;
//   perioadaSneckArdereOn.detach();
//   perioadaSneckArdereOff.detach();
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
//   EEPROM.put(12, 0);
//   EEPROM.commit();
//   EEPROM.put(8, 0);
//   EEPROM.commit();
// }

// void stopSneckArdere() {
//   perioadaSneckArdereOff.detach();
//   digitalWrite(sneck, LOW);
//   stareSneck = "OFF";
// }

// void stopArdere() {
//   perioadaSneckArdereOn.detach();
//   perioadaSneckArdereOff.detach();
//   curatareFinal.attach(350, ventilatorFin);
//   digitalWrite(sneck, LOW);
//   stareSneck = "OFF";
//   kontor = 4;
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
// }

// void startSneckArdere() {
//   if (val == 0) {
//     perioadaSneckArdereOn.detach();
//     perioadaSneckArdereOff.detach();
//     stopArdere();
//   } else {
//     temperaturaArdereCurenta = temp_evacuare->readCelsius();
//     if (temperaturaArdereCurenta < 30) {
//       perioadaSneckArdereOn.detach();
//       perioadaSneckArdereOff.detach();
//       eroare(8);
//     } else {
//       perioadaSneckArdereOn.detach();
//       perioadaSneckArdereOn.attach(Sneck_perioadaArdere, startSneckArdere);
//       perioadaSneckArdereOff.attach(Sneck_timpArdere, stopSneckArdere);
//       digitalWrite(sneck, HIGH);
//       stareSneck = "ON";
//     }
//   }
// }

// void ardere() {
//   perioadaAprindere.detach();
//   kontor = 3;
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
//   digitalWrite(ventilator, HIGH);
//   stareVentilator = "ON";
//   digitalWrite(pompa, HIGH);
//   starePompa = "ON";
//   perioadaSneckArdereOn.attach(Sneck_perioadaArdere, startSneckArdere);
// }

// void stopAprindere() {
//   perioadaAprindere.detach();
//   startVentilatorAprindere.detach();
//   stareTempEvac.detach();
//   digitalWrite(rezistenta, LOW);
//   stareRezistenta = "OFF";
//   digitalWrite(ventilator, LOW);
//   stareVentilator = "OFF";
//   eroare(7);
// }

// void stabilArdere() {
//   perioadaStabil.detach();
//   ardere();
// }

// void stabilAprindere3() {
//   perioadaSneckStabilOff.detach();
//   perioadaAprindere.detach();
//   digitalWrite(sneck, LOW);
//   stareSneck = "OFF";
// }

// void stabilArdere1() {
//   perioadaSneckStabilOn.detach();
//   perioadaAprindere.detach();
//   digitalWrite(sneck, HIGH);
//   stareSneck = "ON";
//   perioadaSneckStabilOff.attach(5, stabilAprindere3);
// }

// void stareTemperaturaEvac() {
//   temperaturaAprindereCurenta = temp_evacuare->readCelsius();
//   if (temperaturaAprindereCurenta - temperaturaAprindereInitiala > 10) {
//     stareTempEvac.detach();
//     perioadaAprindere.detach();
//     startVentilatorAprindere.detach();
//     rezistentaAprindereTimer.detach();
//     digitalWrite(rezistenta, LOW);
//     stareRezistenta = "OFF";
//     digitalWrite(ventilator, HIGH);
//     stareVentilator = "ON";
//     perioadaStabil.attach(120, stabilArdere);
//     perioadaSneckStabilOn.attach(55, stabilArdere1);
//     kontor = 2;
//     EEPROM.put(0, kontor);
//     EEPROM.commit();
//   }
// }

// void pompa_stare() {
//   temp_centrala = temp_apa->readCelsius();
//   tempEvacuare = temp_evacuare->readCelsius();

//   if (temp_centrala >= 40) {
//     digitalWrite(pompa, HIGH);
//     starePompa = "ON";
//     if (temp_centrala > 64 && kontor == 3) {
//       if (modulatie == 0) {
//         modulatie = 1;
//         Sneck_perioadaArdere += 5;
//       }
//     }
//     if (temp_centrala < 64 && kontor == 3) {
//       if (modulatie == 1) {
//         modulatie = 0;
//         Sneck_perioadaArdere -= 5;
//       }
//     }
//     if (temp_centrala > 70 && kontor == 3) {
//       stopArdere();
//     }
//   } else {
//     digitalWrite(pompa, LOW);
//     starePompa = "OFF";
//   }
// }

// void ventAprin() {
//   digitalWrite(ventilator, !digitalRead(ventilator));
//   if (digitalRead(ventilator) == HIGH) {
//     stareVentilator = "ON";
//   } else {
//     stareVentilator = "OFF";
//   }
// }

// void rezistentaAprindere() {
//   rezistentaAprindereTimer.detach();
//   startVentilatorAprindere.attach(8, ventAprin);
// }

// void stopSneck() {
//   kontor = 1;
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
//   startSneckAprindere.detach();
//   digitalWrite(sneck, LOW);
//   stareSneck = "OFF";
//   perioadaAprindere.attach(900, stopAprindere);
//   digitalWrite(rezistenta, HIGH);
//   stareRezistenta = "ON";
//   rezistentaAprindereTimer.attach(120, rezistentaAprindere);
//   stareTempEvac.attach(3, stareTemperaturaEvac);
// }

// void aprindere() {
//   kontor = 1;
//   EEPROM.put(0, kontor);
//   EEPROM.commit();
//   digitalWrite(sneck, HIGH);
//   stareSneck = "ON";
//   digitalWrite(rezistenta, LOW);
//   stareRezistenta = "OFF";
//   startSneckAprindere.attach(100, stopSneck);
// }

