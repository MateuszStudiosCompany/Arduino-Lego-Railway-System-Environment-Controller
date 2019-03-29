#include <Arduino.h>
#include <Servo.h>

class CrossingBarrier{
    private:
        Servo servo;
        int pos_closed, pos_open;
        bool mode;
    public:
        bool init(int servo_pin, int pos_closed, int pos_open, int startup_test_time = 1000){
            if(servo_pin < 0 || pos_closed < 0 || pos_open < 0){
                return false;
            }
            servo.attach(servo_pin);

            if(startup_test_time < 0){
                return true;
            }

            servo.write(pos_closed);
            delay(startup_test_time/2);
            servo.write(pos_open);
            delay(startup_test_time/2);
        }

        bool 
};