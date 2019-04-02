#include <"Arduino.h">

#include "CrossingBarrier.h"

class CrossingList{
    public:
        CrossingBarrier *first = NULL;

        bool add(int servo_pin, int n_pos_closed, int n_pos_open, int startup_test_time = 1000){
            CrossingBarrier *new_barrier;
            new_barrier.init(int servo_pin, int n_pos_closed, int n_pos_open, int startup_test_time = 1000);

            if(!first){
                first = new_barrier;
                return true;
            }
            CrossingBarrier *pointer = first;
            while (pointer->next_in_list) pointer = pointer->next_in_list;
            pointer->next_in_list = new_barrier;
            return true;
        }

        //TODO: Add perfom action for specific object
        bool takeAction(){
            CrossingBarrier *pointer = first;
            if(!pointer)
                return false;
            pointer->takeAction();
            while(pointer->next){
                pointer = pointer->next;
                pointer->takeAction();
            }
        }
};