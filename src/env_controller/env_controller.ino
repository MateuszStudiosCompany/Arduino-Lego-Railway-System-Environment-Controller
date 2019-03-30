#include <Arduino.h>
#include "CrossingController.h"

RailwayCrossingController crossing;

int i = 0;
int toggle = true;


void setup(){
    Serial.begin(115200);
    pinMode(2, INPUT_PULLUP);
    //crossing.addLight(5, 4);
    //crossing.addLight(5, 4, 1, 6, 0);
    //crossing.addLight(5, 4, 0, 6, 0);
    crossing.addBarrier(11, 70, 3);
    // crossing.addBarrier(11, 3, 70);
}

void loop(){
    // if (Serial.available() > 0){
    //     Serial.println("VVVVVVVVV");
    //     char recv = Serial.read();
    //     if (recv == 'A'){
    //         Serial.println("A");
    //         crossing.toggle(true);
    //     }else if (recv == 'B'){
    //         Serial.println("B");
    //         crossing.toggle(false);
    //     }
    // }
    
    if(i == 60){
        Serial.print("i = ");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print("crossing.toggle(");
        Serial.print(toggle);
        Serial.println(")");

        //crossing.toggle(toggle);
        crossing.toggle(true);
        toggle = !toggle;
        i = 0;
    }
    ++i;
    crossing.takeAction();
    delay(100);
}