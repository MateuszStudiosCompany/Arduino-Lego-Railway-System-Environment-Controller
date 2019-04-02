#include <Arduino.h>
#include <Servo.h>

#define CR_BR_OPEN 1
#define CR_BR_OPENING 2
#define CR_BR_CLOSE 3
#define CR_BR_CLOSING 4

class CrossingBarrier{
	private:
		Servo servo;
		int pos_closed, pos_open, pos_actual;
		int smooth_move = 0;
		int status = CR_BR_OPEN;

		bool debug = false;
		String debug_prefix = "[Crossing Barrier] ";

	  public:
		CrossingBarrier *next_in_list = NULL;

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
				if(status == CR_BR_OPEN || status == CR_BR_OPENING){
					return true;
				}
				status = CR_BR_OPENING;
                if(debug){
					Serial.println(debug_prefix + "Barrier starts to open.");
				}
				return true;
			}

			if(status != CR_BR_CLOSING){
                status = CR_BR_CLOSING;
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
				status = CR_BR_CLOSE;
			}else if(pos_closed > pos_open){
				if(pos_actual + smooth_move <= pos_closed){
					pos_actual += smooth_move;
				}else{
					pos_actual = pos_closed;
					status = CR_BR_CLOSE;
				}
			}else{
				if(pos_actual - smooth_move >= pos_closed){
					pos_actual -= smooth_move;
				}else{
					pos_actual = pos_closed;
					status = CR_BR_CLOSE;
				}
			}
			servo.write(pos_actual);
			return true;
		}

		bool actionOpening(){
			if(smooth_move <= 0){
				pos_actual = pos_open;
				status = CR_BR_OPEN;
			}else if(pos_open > pos_closed){
				if(pos_actual + smooth_move <= pos_open){
					pos_actual += smooth_move;
				}else{
					pos_actual = pos_open;
					status = CR_BR_OPEN;
				}
			}else{
				if(pos_actual - smooth_move >= pos_open){
					pos_actual -= smooth_move;
				}else{
					pos_actual = pos_open;
					status = CR_BR_OPEN;
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
				case CR_BR_OPEN:
					return true;
				case CR_BR_OPENING:
					actionOpening();
					break;
				case CR_BR_CLOSE:
					actionClose();
					break;
				case CR_BR_CLOSING:
					actionClosing();
					break;
			}

		}
};