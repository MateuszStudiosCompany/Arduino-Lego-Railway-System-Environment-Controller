#include<Arduino.h>
#include "CrossingLight.h"
#include "CrossingBarrier.h"

#define CROSSING_MODE_ON_AND_OFF 1
#define CROSSING_MODE_ON_AND_TIME 2

class RailwayCrossingController{
	private:
		int i = 0;

		CrossingLight crossing_lights[32];
		int crossing_lights_registered = 0;
		CrossingBarrier crossing_barriers[32];
		int barriers_registered = 0;
		
		int tick_timer;
		int mode;
		bool enable;
		bool debug = true;
		String debug_prefix = "[Crossing Controller] ";
	public:
		bool toggle(bool toggle, int ticks = 0){
			
			// if(ticks <= 0){
			// 	tick_timer = ticks;
			// 	mode = CROSSING_MODE_ON_AND_TIME;
			// }else{
			// 	mode = CROSSING_MODE_ON_AND_OFF;
			// }
			
			enable = toggle;
			for(i = 0; i < crossing_lights_registered; i++){
				//TODO: Make toggle for specific time
				crossing_lights[crossing_lights_registered-1].toggle(toggle);
			}
			for(i = 0; i < barriers_registered; i++){
				crossing_barriers[barriers_registered - 1].toggle(toggle, 1, 20, 10);
			}
			return true;
		}

		bool addLight(int pin_1, int pin_2 = -1, int mode = 0, int change_after_ticks = 12, int startup_test_time = 1000){
			if(debug){
				Serial.println("Light added to controller!");
			}
			crossing_lights[crossing_lights_registered].init(pin_1, pin_2, mode, change_after_ticks);
			crossing_lights_registered++;
		}
		bool addBarrier(int servo_pin, int n_pos_closed, int n_pos_open, int startup_test_time = 1000)
		{
			if(debug){
				Serial.println("Barrier added to controller!");
			}
			crossing_barriers[barriers_registered].init(servo_pin, n_pos_closed, n_pos_open, startup_test_time);
			barriers_registered++;
		}

		void takeAction(){
			// if(!enable){
			// 	return;
			// }
			if(crossing_lights_registered > 0){
				for(i = 0; i < crossing_lights_registered; i++){
					crossing_lights[crossing_lights_registered - 1].takeAction();
				}
			}
			if(barriers_registered > 0){
				for(i = 0; i < barriers_registered; i++){
					crossing_barriers[barriers_registered - 1].takeAction();
				}
			}
		}
		
};