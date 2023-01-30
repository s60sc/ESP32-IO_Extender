// Global IO_Extender declarations
//
// s60sc 2022

#pragma once
#include "globals.h"

/********************* fixed defines leave as is *******************/ 
/** Do not change anything below here unless you know what you are doing **/

#define DEV_ONLY // leave commented out
#define STATIC_IP_OCTAL "160" // dev only
#define CHECK_MEM false // leave as false
#define FLUSH_DELAY 0 // for debugging crashes
 
#define APP_NAME "ESP_IO_Extender" // max 15 chars
#define APP_VER "1.3"

#define MAX_CLIENTS 2 // allowing too many concurrent web clients can cause errors
#define DATA_DIR "/data"
#define HTML_EXT ".htm"
#define TEXT_EXT ".txt"
#define JS_EXT ".js"
#define CSS_EXT ".css"
#define ICO_EXT ".ico"
#define SVG_EXT ".svg"
#define INDEX_PAGE_PATH DATA_DIR "/IO_EXT" HTML_EXT
#define CONFIG_FILE_PATH DATA_DIR "/configs" TEXT_EXT
#define LOG_FILE_PATH DATA_DIR "/log" TEXT_EXT
#define OTA_FILE_PATH DATA_DIR "/OTA" HTML_EXT 
#define FILE_NAME_LEN 64
#define ONEMEG (1024 * 1024)
#define MAX_PWD_LEN 64
#define JSON_BUFF_LEN (1024 * 4) 
#define MAX_CONFIGS 50 // > number of entries in configs.txt
#define GITHUB_URL "https://raw.githubusercontent.com/s60sc/ESP32-IO_Extender/main"

#define FILLSTAR "****************************************************************"
#define DELIM '~'
#define STORAGE LittleFS // use of SPIFFS, LIttleFS or SD_MMC
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
//#define INCLUDE_FTP 
//#define INCLUDE_SMTP
//#define INCLUDE_SD

#define IS_IO_EXTENDER true // must be true for IO_Extender
#define EXTPIN 100


/******************** Function declarations *******************/

// global app specific functions

void getPeripheralsRequest();
bool getPIRval();
float readTemperature(bool isCelsius);
void setCamPan(int panVal);
void setCamTilt(int tiltVal);
void setLamp(uint8_t lampVal);


/******************** Global app declarations *******************/

// status & control fields 

// buffers
extern byte* uartData;

// peripherals

// IO Extender use
extern bool useIOextender; // true to use IO Extender, otherwise false
extern bool useUART0;
extern int uartTxdPin;
extern int uartRxdPin;
// peripherals used
extern bool pirUse; // true to use PIR for motion detection
extern bool lampUse; // true to use lamp
extern bool lampAuto; // if true in conjunction with usePir & useLamp, switch on lamp when PIR activated
extern bool servoUse; // true to use pan / tilt servo control
extern bool voltUse; // true to report on ADC pin eg for for battery
// microphone cannot be used on IO Extender
extern bool micUse; // true to use external I2S microphone 

// sensors 
extern int pirPin; // if usePir is true
extern bool pirVal;
extern int lampPin; // if useLamp is true
// Pan / Tilt Servos 
extern int servoPanPin; // if useServos is true
extern int servoTiltPin;
// ambient / module temperature reading 
extern int ds18b20Pin; // if INCLUDE_DS18B20 uncommented
// batt monitoring 
extern int voltPin; 

// configure for specific servo model, eg for SG90
extern int servoDelay;
extern int servoMinAngle; // degrees
extern int servoMaxAngle;
extern int servoMinPulseWidth; // usecs
extern int servoMaxPulseWidth;

// battery monitor
extern int voltDivider;
extern int voltLow;
extern int voltInterval;     

// task handling
extern TaskHandle_t DS18B20handle;
extern TaskHandle_t servoHandle;
extern TaskHandle_t uartClientHandle;
