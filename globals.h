// Global declarations
//
// s60sc 2022

#pragma once
// to compile with -Wall -Werror=all -Wextra
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
//#pragma GCC diagnostic ignored "-Wunused-variable"

/******************** User modifiable defines *******************/



#define ALLOW_SPACES false // set set true to allow whitespace in configs.txt key values

//#define USE_LOG_COLORS  // uncomment to colorise log messages (eg if using idf.py, but not arduino)

#define IS_ESP32_C3 // uncomment if ESP32-C3 is being used

/** Do not change anything below here unless you know what you are doing **/

/********************* fixed defines leave as is *******************/ 
 
#define APP_NAME "ESP_IO_Extender" // max 15 chars
#define APP_VER "1.1"

#define DATA_DIR "/data"
#define HTML_EXT ".htm"
#define TEXT_EXT ".txt"
#define JS_EXT ".js"
#define CSS_EXT ".css"
#define ICO_EXT ".ico"
#define SVG_EXT ".svg"
#define INDEX_PAGE_PATH DATA_DIR "/IO_EXT" HTML_EXT
#define CONFIG_FILE_PATH DATA_DIR "/configs" TEXT_EXT
#define FILE_NAME_LEN 64
#define ONEMEG (1024 * 1024)
#define MAX_PWD_LEN 64
#define JSON_BUFF_LEN (1024) 
#define GITHUB_URL "https://raw.githubusercontent.com/s60sc/ESP32-IO_Extender/main"

#define FILLSTAR "****************************************************************"
#define DELIM ':'
#define STORAGE SPIFFS // use of SPIFFS or SD_MMC
#define RAMSIZE (1024 * 8) 
#define CHUNKSIZE (1024 * 4)
#define FLUSH_DELAY 0 // for debugging crashes
#define MAX_CONFIGS 100
//#define INCLUDE_FTP 
//#define INCLUDE_SMTP
//#define INCLUDE_SD
//#define DEV_ONLY // leave commented out
#define STATIC_IP_OCTAL "160" // dev only

#define IS_IO_EXTENDER true // must be true for IO_Extender
#define EXTPIN 100

// which optional web assets to download
#define USE_JQUERY false

/******************** Libraries *******************/

#include "Arduino.h"
#include <driver/i2s.h>
#include "esp_http_server.h"
#include <ESPmDNS.h> 
#include "lwip/sockets.h"
#include <vector>
#include "ping/ping_sock.h"
#include <Preferences.h>
#include <regex>
#include <SD_MMC.h>
#include <SPIFFS.h>
#include <sstream>
#include <Update.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

/******************** Function declarations *******************/

// global app specific functions
void getPeripheralsRequest();
bool getPIRval();
float readDS18B20temp(bool isCelsius);
void setCamPan(int panVal);
void setCamTilt(int tiltVal);
void setLamp(bool lampVal);

// global general utility functions in utils.cpp / utilsSD.cpp / peripherals.cpp
void appDataFiles();    
void buildAppJsonString(bool filter);
void buildJsonString(uint8_t filter);
bool checkDataFiles();
bool checkFreeSpace();
void checkMemory();
void dateFormat(char* inBuff, size_t inBuffLen, bool isFolder);
void deleteFolderOrFile(const char* deleteThis);
void devSetup();
void doRestart(String restartStr);
void emailAlert(const char* _subject, const char* _message);
const char* encode64(const char* inp);
const uint8_t* encode64chunk(const uint8_t* inp, int rem);
bool externalPeripheral(byte pinNum, uint32_t outputData = 0);
void flush_log(bool andClose = false);
void formatHex(const char* inData, size_t inLen);
bool ftpFileOrFolder(const char* fileFolder);
bool getLocalNTP();
void getOldestDir(char* oldestDir);
void getUpTime(char* timeVal);
void goToSleep(int wakeupPin, bool deepSleep);
void listBuff(const uint8_t* b, size_t len); 
bool listDir(const char* fname, char* jsonBuff, size_t jsonBuffLen, const char* extension);
bool loadConfig();
void logPrint(const char *fmtStr, ...);
void logSetup();
void OTAprereq();
void prepPeripherals();
void prepSMTP();
void prepUart();
void processAppWSmsg(const char* wsMsg);
void remote_log_init();
void removeChar(char *s, char c);
void reset_log();
void setPeripheralResponse(const byte pinNum, const uint32_t responseData);
void showProgress();
void startFTPtask();
void startOTAtask();
void startSecTimer(bool startTimer);
bool startStorage();
void startWebServer();
bool startWifi();
void syncToBrowser(const char *val);
bool updateAppStatus(const char* variable, const char* value);
bool updateConfigVect(const char* variable, const char* value);
bool updateStatus(const char* variable, const char* _value);
void urlDecode(char* inVal);
uint32_t usePeripheral(const byte pinNum, const uint32_t receivedData);
esp_err_t webAppSpecificHandler(httpd_req_t *req, const char* variable, const char* value);
void wgetFile(const char* githubURL, const char* filePath, bool restart = false);
void wsAsyncSend(const char* wsData);

/******************** Global utility declarations *******************/

extern String AP_SSID;
extern char AP_Pass[];
extern char AP_ip[];
extern char AP_sn[];
extern char AP_gw[];

extern char hostName[]; //Host name for ddns
extern char ST_SSID[]; //Router ssid
extern char ST_Pass[]; //Router passd

extern char ST_ip[]; //Leave blank for dhcp
extern char ST_sn[];
extern char ST_gw[];
extern char ST_ns1[];
extern char ST_ns2[];

extern char Auth_Name[]; 
extern char Auth_Pass[];

extern int responseTimeoutSecs; // time to wait for FTP or SMTP response
extern bool allowAP; // set to true to allow AP to startup if cannot reconnect to STA (router)
extern int wifiTimeoutSecs; // how often to check wifi status
extern uint8_t percentLoaded;
extern int refreshVal;
extern bool configLoaded;

extern char timezone[];
extern char* jsonBuff; 
extern bool dbgVerbose;
extern bool logMode;
extern bool timeSynchronized;
extern bool monitorOpen; 
extern const char* defaultPage_html;
extern const char* otaPage_html;
extern SemaphoreHandle_t wsSendMutex;
// SD storage
extern int sdMinCardFreeSpace; // Minimum amount of card free Megabytes before freeSpaceMode action is enabled
extern int sdFreeSpaceMode; // 0 - No Check, 1 - Delete oldest dir, 2 - Upload to ftp and then delete folder on SD 
extern bool sdFormatIfMountFailed ; // Auto format the sd card if mount failed. Set to false to not auto format.

// peripheral stored values
extern bool useIOextender; // true to use IO Extender, otherwise false
extern float currentVoltage; 
extern float dsTemp;
extern bool pirVal;

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
// microphone cannot be used on IO Extender
extern bool micUse; // true to use external I2S microphone 

// sensors 
extern int pirPin; // if usePir is true
extern int lampPin; // if useLamp is true
// Pan / Tilt Servos 
extern int servoPanPin; // if useServos is true
extern int servoTiltPin;
// ambient / module temperature reading 
extern int ds18b20Pin; // if INCLUDE_DS18B20 uncommented
// batt monitoring 
extern int voltPin; // if INCLUDE_VOLTAGE uncommented

// microphone recording
extern int micSckPin; // I2S SCK
extern int micWsPin;  // I2S WS
extern int micSdPin;  // I2S SD

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
extern TaskHandle_t getDS18Handle;
extern TaskHandle_t uartClientHandle;

/*********************** Log formatting ************************/

#ifdef USE_LOG_COLORS
#define LOG_COLOR_ERR  "\033[0;31m" // red
#define LOG_COLOR_WRN  "\033[0;33m" // yellow
#define LOG_COLOR_DBG  "\033[0;36m" // cyan
#define LOG_NO_COLOR   "\033[0m"
#else
#define LOG_COLOR_ERR
#define LOG_COLOR_WRN
#define LOG_COLOR_DBG
#define LOG_NO_COLOR
#endif 

#define INF_FORMAT(format) "[%s %s] " format "\n", esp_log_system_timestamp(), __FUNCTION__
#define LOG_INF(format, ...) logPrint(INF_FORMAT(format), ##__VA_ARGS__)
#define WRN_FORMAT(format) LOG_COLOR_WRN "[%s WARN %s] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), __FUNCTION__
#define LOG_WRN(format, ...) logPrint(WRN_FORMAT(format), ##__VA_ARGS__)
#define ERR_FORMAT(format) LOG_COLOR_ERR "[%s ERROR @ %s:%u] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), pathToFileName(__FILE__), __LINE__
#define LOG_ERR(format, ...) logPrint(ERR_FORMAT(format), ##__VA_ARGS__)
#define DBG_FORMAT(format) LOG_COLOR_DBG "[%s DEBUG @ %s:%u] " format LOG_NO_COLOR "\n", esp_log_system_timestamp(), pathToFileName(__FILE__), __LINE__
#define LOG_DBG(format, ...) if (dbgVerbose) logPrint(DBG_FORMAT(format), ##__VA_ARGS__)
#define LOG_PRT(buff, bufflen) log_print_buf((const uint8_t*)buff, bufflen)
