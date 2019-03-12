#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <PowerFunctions.h>

PowerFunctions pf(5, 0);
int tick = 25;
int predkosc = 0;

class CrossingLight{
  private:
    int pin1;
    int pin2;
    int delay_ticks;
  public:
    int trigger_time;
    int counter;
    bool is_on = false;
    
    void start(int p1, int p2, int d_t){
      pin1 = p1;
      pin2 = p2;
      delay_ticks = d_t;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      delay(1000);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    }
    void Triggered(int t){ trigger_time = t+80; }
    void TakeAction(){
        if(trigger_time>0){
          if(counter<delay_ticks) counter++;
          else{
            if(is_on){
              digitalWrite(pin1, LOW);
              digitalWrite(pin2, HIGH);
              counter = 0;
              is_on = false;
            }
            else{
              digitalWrite(pin1, HIGH);
              digitalWrite(pin2, LOW);
              counter = 0;
              is_on = true;
            }
          }
          trigger_time--;
      }
      else{
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
      }  
    }  
};

class Barrier {
  private:
    Servo servo;
    int step_distance;
    int first_move_delay;
    int first_move_delay_temp;
    int waiting_time;

    int pos_close;
    int pos_open;
    int pos_actual;
    
  public:
    int opening = false;
    int waiting = false;
    int closing = false;
    int triggered = false;
    
    void start(int servo_pin, int p_c, int p_o, int s_d, int d = 0){
      servo.attach(servo_pin);
      pos_close = p_c;
      pos_open = p_o;
      step_distance = s_d;
      first_move_delay = d;
      first_move_delay_temp = first_move_delay;

      servo.write(pos_open);
      pos_actual = pos_open;    
    }
    int getWaitingTime(){ return waiting_time; }
    void Triggered(int t){
      waiting_time = t;
      triggered = true;
      }
    void TakeAction(){
      //jeśli nie jest zamknięty (w pełni) to ustaw zamykanie (jeśli otwierał to przerwij)
      if((!waiting) && (triggered)){
        closing = true;
        opening = false;
        triggered = false;
      }
      //Jesli ustawiono zamykanie to zamykaj szlaban o 1 krok do czasu az osiagnie pozycje zamkniecia.
      if(closing){
        if(first_move_delay_temp>0) first_move_delay_temp--;
        else{
          if(pos_actual - step_distance <= pos_close) pos_actual += step_distance;
          else{
            pos_actual = pos_close;
            closing = false;
            waiting = true;
          }
        }
      }
      //Czekaj w zamkniecu do poki nie skonczy sie odliczanie i odejmij od odliczania jeden.
      else if(waiting){ 
        if(first_move_delay_temp!= first_move_delay) first_move_delay_temp = first_move_delay; //dodatkowo przywraca czas opoznienia rozpoczecia zamykania
        if(waiting_time>0) waiting_time--;
        else{
          waiting = false;
          opening = true;
        }
      }
      //Jesli ustawiono otwieranie to otwieraj szlaban o 1 krok do czasu az osiagnie pozycje otwarcia.
      else if(opening){
        if(pos_actual + step_distance >= pos_open) pos_actual -= step_distance;
        else{
          pos_actual = pos_open;
          opening = false;
        }
      }
      servo.write(pos_actual);
    }
};

class Detection{
  private:
    int trigger_pin;
    int echo_pin;
    bool after_det = false;
    
  public:
    int ticks;
    int last_detection_ticks;
    int distance;
    int return_time;

    void start(int t_p, int e_p){
      trigger_pin = t_p;
      echo_pin = e_p;
      pinMode(trigger_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }
    int getDistance(){
      digitalWrite(trigger_pin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigger_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger_pin, LOW);
      return_time = pulseIn(echo_pin, HIGH);
      distance = return_time/58;
      return distance;
    }
  
};

class SpeedTest{
  private:
    int ticks = 0;
    int result;
  public:
    bool after_test = true;
    void addTick(){
      ticks++;
      after_test = true;
      }
    int finish(){
      if(after_test){
        after_test = false;
        result = ticks;
        ticks = 0;
        return result;
      }
      else{ return false; }
    }
};

class DisplayData{
  public:
    int refresh_every;
    int counter;
    String last_first_line;
    String last_second_line;
    String first_line;
    String second_line;
};

class SemaforController{
  private:
    int ticks = 0;
    int led_red;
    int led_green;
    int auto_control = true;
    int is_red = true;
    int ac_time = 100;
  public:
    void start(int p1, int p2){
      led_red = p1;
      led_green = p2;
      pinMode(led_red, OUTPUT);
      pinMode(led_green, OUTPUT);
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, HIGH);
      delay(1000);
      digitalWrite(led_green, LOW);
    }
    void setAutoControll(int t){ ac_time = t; }
    void TakeAction(){
      if(!auto_control) return;
      ticks--;
      if(is_red){
        if(ticks%5==0){
        pf.single_pwm(BLUE, PWM_BRK);
        pf.single_pwm(BLUE,PWM_FLT);
        }
      }
      if(ticks>0) return;
      
      if(is_red){
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        is_red = false;
        ticks = ac_time;
        pf.single_pwm(BLUE, PWM_REV4);
      }
      else{
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);  
        is_red = true;
        ticks = ac_time;
      }
    }
    
  
  
};

Barrier szlaban1;
CrossingLight swiatlo1;
Detection czujnik;
SpeedTest pomiar;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);
DisplayData ekran;

SemaforController semafor;

void setup() {
  //Serial.begin (9600);
  
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print("Uruchamianie...");
  
  czujnik.start(11, 12);
  
  szlaban1.start(10, 70, 3, 2, 6); //pin | open pos | close pos | move per 50ms | delay (default 0)
  
  swiatlo1.start(33, 35, 12); //pin | ticks delay betwwen change (~500ms)

  semafor.start(3, 4);
  
  lcd.home ();
  lcd.print("Gotowy do pracy");
  lcd.setCursor (7,1);
  lcd.print(":)");
}
int timeeee;
void loop() { //<- pelta wykonywana przez caly czas dzialania Arduino.
  
  delay(20);
  //int distance = czujnik.getDistance();
  int distance = 9;
  if(distance<10){
    szlaban1.Triggered(50);
    swiatlo1.Triggered(50);
    pomiar.addTick();
  }
  else if(pomiar.after_test) predkosc = pomiar.finish();
  
  szlaban1.TakeAction();
  swiatlo1.TakeAction();
  semafor.TakeAction();

  ekran.last_first_line = ekran.first_line;
  ekran.last_second_line = ekran.second_line;
  ekran.first_line = "Odleglosc: " + String(distance);

  if((ekran.first_line != ekran.last_first_line) || (ekran.second_line != ekran.last_second_line)){
    lcd.clear();
    lcd.home ();
    lcd.print(ekran.first_line);
  }
}
