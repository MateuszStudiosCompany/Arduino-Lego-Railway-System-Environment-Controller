#ifndef LIB_JUNCTION
#define LIB_JUNCTION

#include <Arduino.h>

class Junction{
	private:
		int pos_straight, pos_side;
		Servo servo;
		bool lights = false;
		int led_pin_straight = -1;
		int led_pin_side = -1;
		bool state;
	public:

		void init(int pin, int n_pos1, int n_pos2, int n_led_pin_1 = -1, int n_led_pin_2 = -1, int startup_test_time = 1000){
			servo.attach(pin);
			pos_straight = n_pos1;
			pos_side = n_pos2;
			if(n_led_pin_1 != -1){
				led_pin_straight = n_led_pin_1;
				pinMode(led_pin_straight, OUTPUT);
				digitalWrite(led_pin_straight, HIGH);
			}
			if(n_led_pin_2 != -1){
				led_pin_side = n_led_pin_2;
				pinMode(led_pin_side, OUTPUT);
				digitalWrite(led_pin_side, HIGH);
			}
			if(startup_test_time > 0){
				servo.write(pos_straight);
				delay(startup_test_time/4);
				servo.write(pos_side);
				delay(startup_test_time/4);
				servo.write(pos_straight);
				delay(startup_test_time/4);
				servo.write(pos_side);
				delay(startup_test_time/4);
				servo.write(pos_straight);
			}
			if(n_led_pin_1 != -1) digitalWrite(led_pin_straight, LOW);
			if(n_led_pin_2 != -1) digitalWrite(led_pin_side, LOW);

			if(led_pin_straight != -1) digitalWrite(led_pin_straight, LOW);
			if(led_pin_side != -1) digitalWrite(led_pin_side, LOW);
		}

		void turn(){
			if(state) servo.write(pos_straight);
			else servo.write(pos_side);
			
			if(led_pin_straight != -1) digitalWrite(led_pin_straight, state);
			if(led_pin_side != -1) digitalWrite(led_pin_side, !state);
			state = !state;
		}
		void turn(bool new_state){
			if(new_state) servo.write(pos_straight);
			else servo.write(pos_side);

			if(led_pin_straight != -1) digitalWrite(led_pin_straight, new_state);
			if(led_pin_side != -1) digitalWrite(led_pin_side, !new_state);
			state = new_state;
		}
};

#endif