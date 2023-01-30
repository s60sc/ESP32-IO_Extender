// IO_Extender specific web & prefs functions
//
// s60sc 2022

#include "appGlobals.h"


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
  else if(!strcmp(variable, "voltUse")) voltUse = (bool)intVal; 
  else if(!strcmp(variable, "micUse")) micUse = (bool)intVal;
  else if(!strcmp(variable, "pirPin")) pirPin = intVal;
  else if(!strcmp(variable, "lampPin")) lampPin = intVal;
  else if(!strcmp(variable, "servoPanPin")) servoPanPin = intVal;
  else if(!strcmp(variable, "servoTiltPin")) servoTiltPin = intVal;
  else if(!strcmp(variable, "ds18b20Pin")) ds18b20Pin = intVal;
  else if(!strcmp(variable, "voltPin")) voltPin = intVal;
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

void wsAppSpecificHandler(const char* wsMsg) {
  // message from web socket
  int wsLen = strlen(wsMsg) - 1;
  switch ((char)wsMsg[0]) {
    case 'H': 
      // keepalive heartbeat, return status
    break;
    case 'S': 
      // status request
      buildJsonString(wsLen); // required config number 
      logPrint("%s\n", jsonBuff);
    break;   
    case 'U': 
      // update or control request
      memcpy(jsonBuff, wsMsg + 1, wsLen); // remove 'U'
      parseJson(wsLen);
    break;
    case 'K': 
      // kill websocket connection
      killWebSocket();
    break;
    default:
      LOG_WRN("unknown command %c", (char)wsMsg[0]);
    break;
  }
}

void buildAppJsonString(bool filter) {
  // build app specific part of json string
  char* p = jsonBuff + 1;
  *p = 0;
}

esp_err_t webAppSpecificHandler(httpd_req_t *req, const char* variable, const char* value) {
  return ESP_OK;
}

bool appDataFiles() {
  // callback from setupAssist.cpp, for any app specific files 
  return true;
}

void OTAprereq() {} // dummy 

