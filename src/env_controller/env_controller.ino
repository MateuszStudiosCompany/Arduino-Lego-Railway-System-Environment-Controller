#include <Arduino.h>
#include "CrossingController.h"
#include "NetworkCommunication.h"
#include "Config.h"

#ifdef CFG_DEMO_MODE
    RailwayCrossingController crossing;
    NetworkCommunication network;
    int i = 0;
    int toggle = true;
#else
    #define CFG_DEMO_MODE false;
#endif

void setup(){
    if(CFG_DEBUG_MODE){
        Serial.begin(115200);
        network.init(CFG_WIFI_SSID, CFG_WIFI_PASS, CFG_WIFI_USE_HTTPS, "10.0.0.201", 81);

        crossing.setDebugMode();
        //network.setDebugMode();
    }
    if(CFG_DEMO_MODE){
        crossing.addLight(5, 4, 0, 6);
        //crossing.addLight(5, 4, 1, 6, 0);
        //crossing.addLight(5, 4, 0, 6, 0);
        crossing.addBarrier(2, 70, 3);
        // crossing.addBarrier(11, 3, 70);
    }
    //Note: You can delete setup code above if you don't want to use demo
    //=============[ Put Your Setup Here ]=============




    //=================================================
}

void loop(){
    if(CFG_DEMO_MODE){
        if(i == 30){
            //crossing.toggle(true, 20);
            crossing.toggle(toggle);
            toggle = !toggle;
            i = 0;
        }
        ++i;
        crossing.takeAction();
        delay(60);
    }
    //Note: You can delete loop code above if you don't want to use demo
    //=============[ Put Your Loop Here ]==============




    //=================================================
}