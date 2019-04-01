#include <Arduino.h>
#include <ArduinoJson.h>
#include "CrossingController.h"
#include "Networking.h"
#include "AppConfig.h"

// #ifdef CFG_DEMO_MODE
//     RailwayCrossingController crossing;
//     Networking network;
//     int i = 0;
//     int toggle = true;
//     int main_tick = 0;
// #else
//     #define CFG_DEMO_MODE false;
// #endif

Networking network;
Tasker tasker;

void setup(){
   
    network.init();
    tasker.init();

    // if(CFG_DEBUG_MODE){
    //     Serial.begin(115200);
    //     crossing.setDebugMode();
    //     //network.setDebugMode();
    // }
    // if(CFG_DEMO_MODE){
    //     crossing.addLight(5, 4, 0, 6);
    //     //crossing.addLight(5, 4, 1, 6, 0);
    //     //crossing.addLight(5, 4, 0, 6, 0);
    //     crossing.addBarrier(2, 70, 3);
    //     // crossing.addBarrier(11, 3, 70);
    // }
    //Note: You can delete setup code above if you don't want to use demo

}

int command_amount, task_ammount;

void loop(){

    delay(1);
    if (main_tick++ >= 2048) main_tick = 0;

    String response_json = doRequest("getCommands", "");
    
    StaticJsonDocument<JSON_BUFFER> response;
    DeserializationError json_parse_error = deserializeJson(response, response_json);
    if(json_parse_error){
        Serial.println("Error!");
        return;
    }

    //Perform all commands from server
    command_amount = response["command_amount"];
    for(int i = 0; i < task_amount; i++){
        tasker.performCommand(response["commands"][i]);
    }

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