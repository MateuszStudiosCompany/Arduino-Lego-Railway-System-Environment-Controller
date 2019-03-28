#include <Arduino.h>
#include "CrossingController.h"

RailwayCrossingController crossing;



void setup(){
    //crossing.addLight(5, 4);
    //crossing.addLight(5, 4, 1, 6, 0);
    crossing.addLight(5, 4, 0, 6, 0);
    crossing.toggle(true);
    Serial.begin(115200);
    Serial.println("hello");
}

void loop(){
    crossing.takeAction();
    delay(100);
}