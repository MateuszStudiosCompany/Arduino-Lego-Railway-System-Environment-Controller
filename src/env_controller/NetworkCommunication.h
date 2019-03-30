#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// #define NET_COMM_MODE_AP
// #define NET_COMM_MODE_STA
// #define NET_COMM_MODE_AP_STA

class NetworkCommunication{
	private:
		//int mode = 1;

		WiFiClient socket;
		String ip;

		bool debug = true;
		String debug_prefix = "[Network Manger] ";
		
	public:
		bool init(String ssid, String password, bool use_https, String host = "", int custom_port = -1){
			
			WiFi.mode(WIFI_STA);
			WiFi.begin(ssid, password);
			if(debug){
				Serial.print(debug_prefix + "Connecting to " + ssid);
				if(password == ""){
					Serial.print(" without password");
				}else{
					Serial.print(" with password");
				}
			}
			while (WiFi.status() != WL_CONNECTED) {
				delay(1000);
				if(debug){
					Serial.print(".");
				}
			}
			ip = WiFi.localIP().toString();
			if(debug){
				Serial.println();
				Serial.println("Connected to network with adress: " + ip);
			}

			if(host == ""){
				return true;
			}
			int port;
			if(use_https){
				port = 433;
			}else if(custom_port <= 0){
				port = 80;
			}else{
				port = custom_port;
			}
			this->startConnection(host, port);
			
		}

	bool startConnection(String host, int port){
		if(!socket.connect(host, port)){
			if(debug){
				Serial.println(debug_prefix + "Fatal Error: Cannot connect to " + host + ":" + String (port));
			}
			return false;
		}
		if(debug){
				Serial.println(debug_prefix + "Connected to " + host + ":" + String (port));
			}
	}

	bool sendRequest(String url, String params[][2]){
		// String all_params = "";
		// for(int i = 0; i < (sizeof(params) / sizeof(String)); i++){
		// 	all_params +=params[i]
		// }

		Serial.println("GET " + url + " HTTP/1.1");
		Serial.println("User-Agent: ArduinoLegoRailwaySystem/EnvironmentController/4.0");
	}
};
