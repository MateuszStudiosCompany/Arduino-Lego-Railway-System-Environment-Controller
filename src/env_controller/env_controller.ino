#include <Arduino.h>
#include "CrossingController.h"

RailwayCrossingController crossing;

int i = 0;
int toggle = true;


void setup(){
    Serial.begin(115200);
    pinMode(2, INPUT_PULLUP);
    crossing.addLight(5, 4, 0, 6);
    //crossing.addLight(5, 4, 1, 6, 0);
    //crossing.addLight(5, 4, 0, 6, 0);
    crossing.addBarrier(2, 70, 3);
    // crossing.addBarrier(11, 3, 70);
    crossing.setDebugMode();
}

void loop(){
    
    if(i == 30){
        // Serial.print("i = ");
        // Serial.print(i);
        // Serial.print(" | ");
        // Serial.print("crossing.toggle(");
        // Serial.print(toggle);
        // Serial.println(")");
        //crossing.toggle(toggle);
        //crossing.toggle(toggle, 20);
        //crossing.toggle(true, 20);
        crossing.toggle(toggle);
        toggle = !toggle;
        i = 0;
    }
    ++i;
    crossing.takeAction();
    delay(60);
    
}