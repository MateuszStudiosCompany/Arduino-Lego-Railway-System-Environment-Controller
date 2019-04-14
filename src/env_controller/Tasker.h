#ifndef LIB_TASKER
#define LIB_TASKER

#ifdef DEBUG
	#define DEBUG_PREFIX "[Tsker] "
#endif

#include <ArduinoJson.h>
#include "List.h"
#include "Junction.h"
#include "Semaphore.h"
#include "AppConfig.h"

class Tasker{
	private:
		//CrossingBarrierList crossing_barrier;
		RailwayCrossingController crossing;
		Junction junction;
		Semaphore semaphore;
	public:
		void tempInit(){
			crossing.addBarrier(IO_CROSSING_SERVO, 70, 3);
			crossing.addLight(IO_CROSSING_LED_1, IO_CROSSING_LED_2, 0, 6, 0);
			junction.init(IO_JUNCTION_SERVO, 180, 140, IO_JUNCTION_LED_1, IO_JUNCTION_LED_2);
			semaphore.init(IO_SEMAPHORE_LED_1, IO_SEMAPHORE_LED_2);

		}
		void performCommand(StaticJsonDocument<JSON_BUFFER> command){
			String command_name = command["command"];
			#ifdef DEBUG
				Serial.print( (String) DEBUG_PREFIX + "Found new command from server " + command_name + ": ");
			#endif
				

			if(command_name == "addCrossingBarrier"){
				// #ifdef DEBUG
				// 	Serial.println("Creating new CrossingBarrier");
				// #endif
				// int servo_pin = command["servo_pin"];
				// int pos_closed = command["pos_closed"];
				// int pos_open = command["pos_open"];
				// int startup_time = command["startup_time"];
				// crossing.addBarrier(servo_pin, pos_closed, pos_open, startup_time);
			}else if(command_name == "SET_SEMAPHORE"){

			}else if(command_name == "toggleCrossing"){
				bool toggle = command["toggle"];
				crossing.toggle(toggle);
				#ifdef DEBUG
					Serial.println("Crossing toggle to " + (String) toggle + ".");
				#endif
			}else if(command_name == "setJunction"){
				//FIX: Pins are inversed thaths why i reverse given state
				bool state = command["is_straight"];
				junction.turn(!state);
				#ifdef DEBUG
					if(!state) Serial.println("Junction change direction to toggle to straight");
					else Serial.println("Junction change direction to toggle to side");
				#endif
			}else if(command_name == "setSemaphore"){
				bool state = command["is_green"];
				semaphore.toggle(!state);
				#ifdef DEBUG
					if(!state) Serial.println("Semafor changed to green");
					else Serial.println("Semafor changed to red");
				#endif
			}
		}

		void takeAction(){
			crossing.takeAction();
		}

};

#endif
