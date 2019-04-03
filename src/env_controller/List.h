
#ifndef LIB_LIST
#define LIB_LIST

#ifdef DEBUG
    #define DEBUG_PREFIX "[List Menager] "
#endif

#include "CrossingBarrier.h"


#define LIB_LIST_CMD_TAKE_ACTION 1
#define LIB_LIST_CMD_TOGGLE 2

class CrossingBarrierList{
    public:
        CrossingBarrier *first = NULL;

        bool add(int servo_pin, int n_pos_closed, int n_pos_open, int startup_test_time = 1000){
            CrossingBarrier *new_barrier = new CrossingBarrier;
            if (!new_barrier){
                #ifdef DEBUG
                    Serial.println( (String) DEBUG_PREFIX + "Error: Crossing ");
                #endif
                return false;
            }
            new_barrier->init(servo_pin, n_pos_closed, n_pos_open, startup_test_time);
            if(!first){
                first = new_barrier;
                return true;
            }
            CrossingBarrier *pointer = first;
            while (pointer->next_in_list) pointer = pointer->next_in_list;
            pointer->next_in_list = new_barrier;
            return true;
        }

        bool functionExecutorAll(int command){
            CrossingBarrier *pointer = first;
            if(!pointer) return false;

            functionExecutor(pointer, command);
            while(pointer->next_in_list){
                functionExecutor(pointer, command);
                pointer = pointer->next_in_list;
                
            }
        }

        // bool functionExecutor(int in_list_position, int command){
        //     //TODO: finish performing action for specific 
        // }
        
        bool functionExecutor(CrossingBarrier *pointer, int command){
            switch (command){
                case LIB_LIST_CMD_TAKE_ACTION:
                    pointer->takeAction();
                    return true;
                    break;
                case LIB_LIST_CMD_TOGGLE:
                    pointer->toggle(true);
                    return true;
                    break;
                default:
                    return false;
                    break;
            }
        }
};

#endif