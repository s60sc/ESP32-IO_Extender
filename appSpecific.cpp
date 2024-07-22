// IO_Extender specific web & prefs functions
//
// s60sc 2022, 2024

#include "appGlobals.h"

const size_t prvtkey_len = 0;
const size_t cacert_len = 0;
const char* prvtkey_pem = "";
const char* cacert_pem = "";

/************************ webServer callbacks *************************/

bool updateAppStatus(const char* variable, const char* value, bool fromUser) {
  // update vars from browser input
  bool res = true; 
  int intVal = atoi(value);
  float fltVal = atof(value);
  // peripherals
  if (!strcmp(variable, "custom")) return res;
  else if(!strcmp(variable, "useIOextender")) useIOextender = (bool)intVal;
  else if(!strcmp(variable, "useUART0")) useUART0 = (bool)intVal;
  else if(!strcmp(variable, "uartTxdPin")) uartTxdPin = intVal;
  else if(!strcmp(variable, "uartRxdPin")) uartRxdPin = intVal;
  else if(!strcmp(variable, "pirUse")) pirUse = (bool)intVal;
  else if(!strcmp(variable, "lampUse")) lampUse = (bool)intVal;
  else if(!strcmp(variable, "lampAuto")) lampAuto = (bool)intVal;
  else if(!strcmp(variable, "servoUse")) servoUse = (bool)intVal;
  else if(!strcmp(variable, "voltUse")) voltUse = (bool)intVal; 
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
  else if(!strcmp(variable, "voltLow")) voltLow = fltVal;
  else if(!strcmp(variable, "voltInterval")) voltInterval = intVal;
  return res;
}

void appSpecificWsBinHandler(uint8_t* wsMsg, size_t wsMsgLen) {
  LOG_ERR("Unexpected websocket binary frame");
}

void appSpecificWsHandler(const char* wsMsg) { 
  // message from web socket
  int wsLen = strlen(wsMsg) - 1;
  switch ((char)wsMsg[0]) {
    case 'X':
    break;
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
      killSocket();
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

esp_err_t appSpecificWebHandler(httpd_req_t *req, const char* variable, const char* value) {
  return ESP_OK;
}

esp_err_t appSpecificSustainHandler(httpd_req_t* req) {
  return ESP_OK;
}

void externalAlert(const char* subject, const char* message) {
  // alert any configured external servers
}

bool appDataFiles() {
  // callback from setupAssist.cpp, for any app specific files
  return true;
}

void doAppPing() {
  doIOExtPing();
}

void OTAprereq() {
  stopPing();
}

void stepperDone() {
}

/************** default app configuration **************/
const char* appConfig = R"~(
restart~~99~T~na
ST_SSID~~0~T~Wifi SSID name
ST_Pass~~0~T~Wifi SSID password
ST_ip~~0~T~Static IP address
ST_gw~~0~T~Router IP address
ST_sn~255.255.255.0~0~T~Router subnet
ST_ns1~~0~T~DNS server
ST_ns2~~0~T~Alt DNS server
AP_Pass~~0~T~AP Password
AP_ip~~0~T~AP IP Address if not 192.168.4.1
AP_sn~~0~T~AP subnet
AP_gw~~0~T~AP gateway
allowAP~1~0~C~Allow simultaneous AP
useHttps~0~0~C~Use HTTPS
useSecure~0~0~C~Validate server cert
timezone~GMT0~0~T~Timezone string: tinyurl.com/TZstring
logType~1~99~N~Output log selection
Auth_Name~~0~T~Optional user name for web page login
Auth_Pass~~0~T~Optional user name for web page password
formatIfMountFailed~0~2~C~Format file system on failure
wifiTimeoutSecs~30~0~N~WiFi connect timeout (secs)
useUART0~0~3~C~Use UART0 for IO Extender
uartTxdPin~~3~N~UART1 TX pin
uartRxdPin~~3~N~UART1 RX pin
pirUse~0~3~C~Use PIR for detection
lampUse~0~3~C~Use lamp
lampAuto~0~99~C~Lamp activated by PIR
servoUse~0~3~C~Use servos
micUse~0~99~C~Use microphone
pirPin~~3~N~Pin used for PIR
lampPin~~3~N~Pin used for Lamp
servoPanPin~~3~N~Pin used for Pan Servo
servoTiltPin~~3~N~Pin used for Tilt Servo
ds18b20Pin~~3~N~Pin used for DS18B20 temperature sensor
micSckPin~~99~N~Pin used for I2S microphone SCK 
micWsPin~~99~N~Pin used for I2S microphone WS
micSdPin~~99~N~Pin used for I2S microphone SD
servoDelay~0~3~N~Delay between each 1 degree change (ms) 
servoMinAngle~0~3~N~Set min angle for servo model
servoMaxAngle~180~3~N~Set max angle for servo model
servoMinPulseWidth~544~3~N~Set min pulse width for servo model (usecs)
servoMaxPulseWidth~2400~3~N~Set max pulse width for servo model (usecs)
voltDivider~2~3~N~Voltage divider resistor ratio
voltLow~3~99~N~Warning level for low voltage
voltInterval~5~3~N~Voltage check interval (mins)
voltPin~~3~N~ADC Pin used for battery voltage
voltUse~0~3~C~Use Voltage check
usePing~1~0~C~Use ping
)~";
