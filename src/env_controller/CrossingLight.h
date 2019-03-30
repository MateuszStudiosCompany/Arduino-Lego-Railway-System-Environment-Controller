#include <Arduino.h>

class CrossingLight{
	private:
		int pin1;
		int pin2 = -1;
		int mode;
		int change_after_ticks;
		int tick_timer = 0;
		bool enable = false;
		bool status = false;

		bool debug = false;
	public:
		bool init(int n_pin1, int n_pin2 = -1, int n_mode = 0, int n_change_after_ticks = 12, int startup_test_time = 1000){
			if(n_pin1 < 0 || change_after_ticks < 0){
				return false;
			}
			if(n_pin2 > 0){
				pin2 = n_pin2;
				pinMode(pin2, OUTPUT);
			}
			pin1 = n_pin1;
			pinMode(pin1, OUTPUT);
			change_after_ticks = n_change_after_ticks;
            mode = n_mode;
			tick_timer = change_after_ticks;

			if(startup_test_time < 0){
				return true;
			}
			digitalWrite(pin1, HIGH);
			if(pin2 > 0){
				digitalWrite(pin2, HIGH);
			}
			delay(startup_test_time);
			digitalWrite(pin1, LOW);
			if(pin2 > 0){
				digitalWrite(pin2, LOW);
			}
			
			return true;
		}

		
		bool toggle(bool toggle){
			enable = toggle;
			if(!enable){
				digitalWrite(pin1, LOW);
				if(pin2 > 0){
				digitalWrite(pin2, LOW);
			}
			}
			return true;
		}

		void debug(bool toggle = true){
            debug = toggle;
        }

		void takeAction(){
			if(!enable){
				return;
			}
			if(tick_timer != change_after_ticks){
				tick_timer++;
				return;
			}
			switch (mode){
				case 1:
					this->modeBlink();
					break;
				default:
					this->modeLeftRight();
					break;
			}
			status = !status;
			tick_timer = 0;
			return;

		}

		void modeLeftRight(){
			digitalWrite(pin1, status);
			if(pin2 > 0){
				digitalWrite(pin2, !status);
			}

		}

		void modeBlink(){
			digitalWrite(pin1, status);
			if(pin2 > 0){
				digitalWrite(pin2, status);
			}
		}

        bool changeMode(int n_mode){
            mode = n_mode;
        }

};