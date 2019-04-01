#include <Arduino.h>
#include "Secrets.h"

#define CFG_DEBUG_MODE				true
#define CFG_DEMO_MODE				true	// Comment this line to disable demo mode!

// Network config
#define HOSTNAME 				    "webtrain1"
#define DEFAULT_SERVER_IP 	    	"10.0.0.201"
#define DEFAULT_SERVER_API_PATH     "train_api"
#define APMODE

#define HTTP_TIMEOUT 		    	300
#define JSON_BUFFER  		    	600

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