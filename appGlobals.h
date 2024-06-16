// Global IO_Extender declarations
//
// s60sc 2022

#pragma once
#include "globals.h"

#define ALLOW_SPACES false // set true to allow whitespace in configs.txt key values

#define USE_DS18B20 false  // if true, requires additional libraries: OneWire and DallasTemperature

// web server ports
#define HTTP_PORT 80 // insecure app access
#define HTTPS_PORT 443 // secure app access


/*********************** Fixed defines leave as is ***********************/ 
/** Do not change anything below here unless you know what you are doing **/

//#define DEV_ONLY // leave commented out
#define STATIC_IP_OCTAL "161" // dev only
#define DEBUG_MEM false // leave as false
#define FLUSH_DELAY 0 // for debugging crashes
#define DBG_ON false // esp debug output
#define DOT_MAX 50
#define HOSTNAME_GRP 0
 
#define APP_NAME "ESP_IO_Extender" // max 15 chars
#define APP_VER "1.5"

#define HTTP_CLIENTS 2 // http, ws
#define MAX_STREAMS 0
#define INDEX_PAGE_PATH DATA_DIR "/IO_EXT" HTML_EXT
#define FILE_NAME_LEN 64
#define IN_FILE_NAME_LEN 128
#define JSON_BUFF_LEN (1024 * 4) 
#define MAX_CONFIGS 60 // > number of entries in configs.txt
#define GITHUB_PATH "/s60sc/ESP32-IO_Extender/main"

#define STORAGE LittleFS // One of LittleFS or SD_MMC
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
#define MIN_RAM 8 // min object size stored in ram instead of PSRAM default is 4096
#define MAX_RAM 4096 // max object size stored in ram instead of PSRAM default is 4096
#define TLS_HEAP (64 * 1024) // min free heap for TLS session
#define WARN_HEAP (32 * 1024) // low free heap warning
#define WARN_ALLOC (16 * 1024) // low free max allocatable free heap block
#define MAX_ALERT 1024

#define INCLUDE_FTP_HFS false // ftp.cpp (file upload)
#define INCLUDE_SMTP false    // smtp.cpp (email)
#define INCLUDE_MQTT false    // mqtt.cpp
#define INCLUDE_TGRAM false   // telegram.cpp
#define INCLUDE_CERTS false   // certificates.cpp (https and server certificate checking)
#define INCLUDE_UART true     // uart.cpp (use another esp32 as IO extender)
#define INCLUDE_WEBDAV true   // webDav.cpp (WebDAV protocol)

#define IS_IO_EXTENDER true // must be true for IO_Extender
#define EXTPIN 100

// to determine if newer data files need to be loaded
#define CFG_VER 2

#ifdef CONFIG_IDF_TARGET_ESP32S3 
#define SERVER_STACK_SIZE (1024 * 8)
#define DS18B20_STACK_SIZE (1024 * 2)
#define STICK_STACK_SIZE (1024 * 4)
#else
#define SERVER_STACK_SIZE (1024 * 4)
#define DS18B20_STACK_SIZE (1024)
#define STICK_STACK_SIZE (1024 * 2)
#endif
#define BATT_STACK_SIZE (1024 * 2)
#define EMAIL_STACK_SIZE (1024 * 6)
#define FS_STACK_SIZE (1024 * 4)
#define LOG_STACK_SIZE (1024 * 3)
#define MIC_STACK_SIZE (1024 * 4)
#define MQTT_STACK_SIZE (1024 * 4)
#define PING_STACK_SIZE (1024 * 5)
#define SERVO_STACK_SIZE (1024)
#define SUSTAIN_STACK_SIZE (1024 * 4)
#define TGRAM_STACK_SIZE (1024 * 6)
#define TELEM_STACK_SIZE (1024 * 4)
#define UART_STACK_SIZE (1024 * 2)

// task priorities
#define HTTP_PRI 5
#define STICK_PRI 5
#define TGRAM_PRI 1
#define EMAIL_PRI 1
#define FTP_PRI 1
#define LOG_PRI 1
#define DS18B20_PRI 1
#define SERVO_PRI 1
#define UART_PRI 1
#define BATT_PRI 1
#define IDLEMON_PRI 5


/******************** Function declarations *******************/

// global app specific functions

void doIOExtPing();
void getPeripheralsRequest();
bool getPIRval();
float readTemperature(bool isCelsius);
void setCamPan(int panVal);
void setCamTilt(int tiltVal);
void setLamp(uint8_t lampVal);
void stepperDone();

/******************** Global app declarations *******************/

// status & control fields 
extern const char* appConfig;

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

// sensors 
extern int pirPin; // if usePir is true
extern bool pirVal;
extern int lampPin; // if useLamp is true
// Pan / Tilt Servos 
extern int servoPanPin; // if useServos is true
extern int servoTiltPin;
// ambient / module temperature reading 
extern int ds18b20Pin; // if INCLUDE_DS18B20 true
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
extern float voltLow;
extern int voltInterval;     

// task handling
extern TaskHandle_t DS18B20handle;
extern TaskHandle_t servoHandle;
extern TaskHandle_t uartClientHandle;
