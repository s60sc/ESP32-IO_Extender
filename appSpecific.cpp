// IO_Extender specific web & prefs functions
//
// s60sc 2022

#include "globals.h"

bool updateAppStatus(const char* variable, const char* value) {
  // update vars from browser input
  bool res = true; 
  int intVal = atoi(value);
  // peripherals
  if(!strcmp(variable, "useIOextender")) useIOextender = (bool)intVal;
  else if(!strcmp(variable, "useUART0")) useUART0 = (bool)intVal;
  else if(!strcmp(variable, "uartTxdPin")) uartTxdPin = intVal;
  else if(!strcmp(variable, "uartRxdPin")) uartRxdPin = intVal;
  else if(!strcmp(variable, "pirUse")) pirUse = (bool)intVal;
  else if(!strcmp(variable, "lampUse")) lampUse = (bool)intVal;
  else if(!strcmp(variable, "lampAuto")) lampAuto = (bool)intVal;
  else if(!strcmp(variable, "servoUse")) servoUse = (bool)intVal;
  else if(!strcmp(variable, "micUse")) micUse = (bool)intVal;
  else if(!strcmp(variable, "pirPin")) pirPin = intVal;
  else if(!strcmp(variable, "lampPin")) lampPin = intVal;
  else if(!strcmp(variable, "servoPanPin")) servoPanPin = intVal;
  else if(!strcmp(variable, "servoTiltPin")) servoTiltPin = intVal;
  else if(!strcmp(variable, "ds18b20Pin")) ds18b20Pin = intVal;
  else if(!strcmp(variable, "voltPin")) voltPin = intVal;
  else if(!strcmp(variable, "micSckPin")) micSckPin = intVal;
  else if(!strcmp(variable, "micWsPin")) micWsPin = intVal;
  else if(!strcmp(variable, "micSdPin")) micSdPin = intVal;
  else if(!strcmp(variable, "servoDelay")) servoDelay = intVal;
  else if(!strcmp(variable, "servoMinAngle")) servoMinAngle = intVal;
  else if(!strcmp(variable, "servoMaxAngle")) servoMaxAngle = intVal;
  else if(!strcmp(variable, "servoMinPulseWidth")) servoMinPulseWidth = intVal;
  else if(!strcmp(variable, "servoMaxPulseWidth")) servoMaxPulseWidth = intVal;
  else if(!strcmp(variable, "voltDivider")) voltDivider = intVal;
  else if(!strcmp(variable, "voltLow")) voltLow = intVal;
  else if(!strcmp(variable, "voltInterval")) voltInterval = intVal;
  return res;
}

void buildAppJsonString(bool quick) {
  // build app specific part of json string
}

esp_err_t webAppSpecificHandler(httpd_req_t *req, const char* variable, const char* value) {
  return ESP_OK;
}

void processAppWSmsg(const char* wsMsg) {
  // process websocket message & send response if required
}

void appDataFiles() {
  // callback from setupAssist.cpp, for any app specific files 
}
