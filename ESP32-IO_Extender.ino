
// IO Extender
// Use of an ESP32, such as ESP32-C3 to provide additional peripheral pins
// to another ESP32 with limited free pins, such as ESP-Cam module
// The ESPs communicate using a UART interface.
// The interface only supports peripherals that receive or output a numeric value.
// It is only suitable for low data rate peripherals, it cannot support clocked 
// data streams such as a microphone.
// This version of the app is configured to support peripherals for ESP32_MJPEG2SD
// Modify peripherals.cpp to add further peripherals
//
// Compile with partition scheme: Minimal Spiffs ...
//
// s60sc 2022

#include "globals.h"

void OTAprereq() {} // dummy

void setup() {
  startSpiffs();
  loadConfig();
#ifdef DEV_ONLY
  devSetup();
#endif
  // connect wifi or start config AP if router details not available
  startWifi(); 
  startWebServer();
  LOG_INF(APP_NAME " v" APP_VER " ready ...");
  prepPeripherals();
  checkMemory();
}

void loop() {
  getPeripheralsRequest();
}
