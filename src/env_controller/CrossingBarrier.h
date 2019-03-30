#include <Arduino.h>
#include <Servo.h>

#define OPEN 1
#define OPENING 2
#define CLOSE 3
#define CLOSING 4

class CrossingBarrier{
	private:
		Servo servo;
		int pos_closed, pos_open, pos_actual;
		int smooth_move = 0;
		int status = OPEN;

		bool debug = false;
		String debug_prefix = "[Crossing Barrier] ";

	  public:
		bool init(int servo_pin, int n_pos_closed, int n_pos_open, int startup_test_time = 1000){
			if(servo_pin < 0 || pos_closed < 0 || pos_open < 0){
				return false;
			}
			servo.attach(servo_pin);
			pos_closed = n_pos_closed;
			pos_open = n_pos_open;
			pos_actual = pos_open;

			if(debug){
				Serial.println(debug_prefix + "Barrier initialized!");
			}

			if(startup_test_time < 0){
				servo.write(pos_open);
				return true;
			}

			servo.write(pos_closed);
			delay(startup_test_time/2);
			servo.write(pos_open);
			delay(startup_test_time/2);
		}

        void setDebugMode(bool toggle = true){
            debug = toggle;
        }

		bool toggle(bool toggle, int n_smooth_move = 0){
			smooth_move = n_smooth_move;
			
			if(!toggle){
				if(status == OPEN || status == OPENING){
					return true;
				}
				status = OPENING;
                if(debug){
					Serial.println(debug_prefix + "Barrier starts to open.");
				}
				return true;
			}

			if(status != CLOSING){
                status = CLOSING;
				if(debug){
                    Serial.println(debug_prefix + "Barrier starts to close.");
                }
			}
			return true;
		}

        //TODO: Remake closing and opening to one function
		bool actionClosing(){
			if(smooth_move <= 0){
				pos_actual = pos_closed;
				status = CLOSE;
			}else if(pos_closed > pos_open){
				if(pos_actual + smooth_move <= pos_closed){
					pos_actual += smooth_move;
				}else{
					pos_actual = pos_closed;
					status = CLOSE;
				}
			}else{
				if(pos_actual - smooth_move >= pos_closed){
					pos_actual -= smooth_move;
				}else{
					pos_actual = pos_closed;
					status = CLOSE;
				}
			}
			servo.write(pos_actual);
			return true;
		}

		bool actionOpening(){
			if(smooth_move <= 0){
				pos_actual = pos_open;
				status = OPEN;
			}else if(pos_open > pos_closed){
				if(pos_actual + smooth_move <= pos_open){
					pos_actual += smooth_move;
				}else{
					pos_actual = pos_open;
					status = OPEN;
				}
			}else{
				if(pos_actual - smooth_move >= pos_open){
					pos_actual -= smooth_move;
				}else{
					pos_actual = pos_open;
					status = OPEN;
				}
			}
			servo.write(pos_actual);
			return true;
		}

		bool actionClose(){
			//do nothing while ticker was moved to CrossingController. But I'm not that cruel to delete this ;)
		}

		bool takeAction(){
			switch (status)
			{
				case OPEN:
					return true;
				case OPENING:
					actionOpening();
					break;
				case CLOSE:
					actionClose();
					break;
				case CLOSING:
					actionClosing();
					break;
			}

		}
};