#include "Secrets.h"

/*
ledy przejazdu - D0 i D1
Serwa przejazdu - D2

ledy zwrotnica - D6 i D7
Serwo zwrotnica - D8

Semafor (TODO) - D3 i D4

*/

#define IO_CROSSING_LED_1           16  //D0
#define IO_CROSSING_LED_2           5   //D1
#define IO_CROSSING_SERVO           4   //D2

#define IO_JUNCTION_LED_1           12  //D6
#define IO_JUNCTION_LED_2           13  //D7
#define IO_JUNCTION_SERVO           15  //D8

#define IO_SEMAPHORE_LED_1          0   //D3
#define IO_SEMAPHORE_LED_2          2   //D4

#define CFG_DEBUG_MODE				true
#define CFG_DEMO_MODE				true	// Comment this line to disable demo mode!
#define DEVICE_TYPE                 "envcontroller" 

#define DEBUG

// Network config
#define HOSTNAME 				    "envcontroller1"
#define DEFAULT_SERVER_IP 	    	"10.0.0.123"
//#define DEFAULT_SERVER_IP 	    	"10.0.0.50"
#define DEFAULT_SERVER_API_PATH     "Web-Lego-Railway-System-Server"
#define APMODE

#define HTTP_TIMEOUT 		    	300
#define JSON_BUFFER  		    	600
#define DEBUG_HTTP

// DO NOT CHANGE THIS
#ifndef CONFIG_LOADED
#define CONFIG_LOADED
String SERVER_IP = DEFAULT_SERVER_IP;
String SERVER_API_PATH = DEFAULT_SERVER_API_PATH;
String CLIENT_SSID = DEFAULT_CLIENT_SSID;
String CLIENT_PASS = DEFAULT_CLIENT_PASS;
#endif

#ifndef FILE
#define FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif
