#ifndef LIB_SEMAPHORE
#define LIB_SEMAPHORE

#include <Arduino.h>

class Semaphore{
	private:
		int pin_green, pin_red;
		bool state;
	public:

		void init(int n_pin_green, int n_pin_red, int startup_test_time = 1000){

            pin_green = n_pin_green;
            pin_red = n_pin_red;
			pinMode(pin_green, OUTPUT);
            pinMode(pin_red, OUTPUT);
            
			if(startup_test_time > 0){
				digitalWrite(pin_green, HIGH);
				digitalWrite(pin_red, HIGH);
				delay(startup_test_time);
				digitalWrite(pin_red, LOW);
			}
		}

		void toggle(){
			digitalWrite(pin_green, state);
			digitalWrite(pin_red, !state);
			state = !state;
		}
		void toggle(bool new_state){
			digitalWrite(pin_green, new_state);
			digitalWrite(pin_red, !new_state);
			state = new_state;
		}
};

#endif