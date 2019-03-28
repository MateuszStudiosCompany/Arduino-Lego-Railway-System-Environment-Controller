#include<Arduino.h>
#include "CrossingLight.h"

#define CROSSING_MODE_IN_AND_OUT 1
#define CROSSING_MODE_IN_AND_TIME 2

class RailwayCrossingController{
	private:
		int i = 0;
		CrossingLight crossing_lights[32];
		int crossing_lights_registered = 0;
		int barriers_registered = 0;
		bool enable;
	public:
		bool toggle(bool toggle){
			enable = toggle;
			for(i = 0; i < crossing_lights_registered; i++){
				crossing_lights[crossing_lights_registered-1].toggle(toggle);
			}
			return true;
		}

		bool addLight(int pin_1, int pin_2 = -1, int mode = 0, int change_after_ticks = 12, int startup_test_time = 1000){
			crossing_lights[crossing_lights_registered].init(pin_1, pin_2, mode, change_after_ticks);
			crossing_lights_registered++;
		}

		void takeAction(){
			if(!enable){
				return;
			}
			if(crossing_lights_registered > 0){
				for(i = 0; i < crossing_lights_registered; i++){
					crossing_lights[crossing_lights_registered-1].takeAction();
				}
			}
		}
		
};