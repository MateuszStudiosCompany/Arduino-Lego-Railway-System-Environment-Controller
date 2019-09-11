#include <Arduino.h>
#include <ArduinoJson.h>
#include "CrossingController.h"
#include "Networking.h"
#include "AppConfig.h"
#include "Tasker.h"

#ifdef DEBUG
    #define DEBUG_PREFIX "[Enviroment Controller] "
#endif

// #ifdef CFG_DEMO_MODE
//     RailwayCrossingController crossing;
//     Networking network;
//     int i = 0;
//     int toggle = true;
//     int main_tick = 0;
// #else
//     #define CFG_DEMO_MODE false;
// #endif

RailwayCrossingController crossing;
Networking network;
Tasker tasker;

void setup(){
   
    Serial.begin(115200);
    delay(1000);
    Serial.println("Serial is enabled!");
    tasker.tempInit();
    network.init();

}
int main_tick;
int command_amount, task_amount;

bool toggle = false;

void loop(){
    
    if (main_tick++ >= 2048) main_tick = 0;

    #ifdef DEBUG
        Serial.println((String) DEBUG_PREFIX + "Starting new tick");
    #endif
    String response_json = doRequest("GET_COMMANDS", ""); 
    StaticJsonDocument<JSON_BUFFER> response;
    DeserializationError json_parse_error = deserializeJson(response, response_json);
    #ifdef DEBUG
        if(json_parse_error) Serial.println((String) DEBUG_PREFIX + "Response is not json or buffer is to small.");
        else Serial.println((String) DEBUG_PREFIX + "Recived good json:\n" + response_json);
    #endif
    
    if(json_parse_error) return;
    
    command_amount = response[HOSTNAME]["command_amount"];
    for(int i = 0; i < command_amount; i++){
        tasker.performCommand(response[HOSTNAME]["commands"][i]);
    }

    tasker.takeAction();
    // if(main_tick % 30 == 0){
    //     //crossing.toggle(true, 20);
    //     crossing.toggle(toggle);
    //     toggle = !toggle;
    // }
    // crossing.takeAction();

    delay(30);

    //Then performAction for all tasks on controller


    //task_amount = tasker.task_ammount;
    



    //delay(1); // -> delayMicroseconds(1000)
    // if(CFG_DEMO_MODE){
    //     if(i == 30){
    //         //crossing.toggle(true, 20);
    //         crossing.toggle(toggle);
    //         toggle = !toggle;
    //         i = 0;
    //     }
    //     ++i;
    //     crossing.takeAction();
    //     delay(60);
    // }
    //Note: You can delete loop code above if you don't want to use demo
    
    //=============[ Put Your Loop Here ]==============




    //=================================================
}