#include <Arduino.h>
#include <Servo.h>

#define CROSSING_MODE_ON_AND_OFF 1
#define CROSSING_MODE_ON_AND_TIME 2

#define OPEN 1
#define OPENING 2
#define CLOSE 3
#define CLOSING 4

class CrossingBarrier{
	private:
		Servo servo;
		int pos_closed, pos_open, pos_actual;
		//TODO: Move tick_timer and time control to main object
		int tick_timer = 0;
		int smooth_move = 0;
		int status = OPEN;
        int open_mode = CROSSING_MODE_ON_AND_TIME;

		bool debug = true;
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
				Serial.println("Barrier initialized!");
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

		bool toggle(bool toggle, int n_open_mode = CROSSING_MODE_ON_AND_TIME, int closed_ticks = 30, int n_smooth_move = 0){
			if (open_mode < 0 || closed_ticks < 0){
				return false;
			}
            open_mode = n_open_mode;
			smooth_move = n_smooth_move;
			
			if(!toggle){
				if(debug){
					Serial.println("Barrier opening caused by program!");
				}
				if(status == OPEN || status == OPENING){
					return true;
				}
				tick_timer = 0;
				status = OPENING;
				return true;
			}

			if(debug){
				Serial.println("Barrier closing caused by program!");
			}
			if(status == CLOSE){
				tick_timer = closed_ticks;
			}
			else if(status != CLOSING){
				tick_timer = closed_ticks;
				status = CLOSING;
			}
			return true;
			
		}

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
			if (tick_timer <= 0 && open_mode != CROSSING_MODE_ON_AND_OFF){
				status = OPENING;
				return true;
			}else if(open_mode != CROSSING_MODE_ON_AND_OFF){
                tick_timer--;
            }
			
		}

		bool takeAction(){
			// Serial.print("STATUS: ");
			// Serial.print(status);
			// Serial.print(" | TICK: ");
			// Serial.println(tick_timer);
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