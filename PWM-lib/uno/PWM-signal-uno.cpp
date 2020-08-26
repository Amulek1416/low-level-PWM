/**
 * 
 */
#include "../board_type.h"

#if BOARD == _UNO

#include "../PWM.h"
#include <Arduino.h>

void PWM_init(PWM_SIG PWM){ 
    pinMode(PWM.pin, OUTPUT);
}


void setFreq(PWM_PIN pin, freq_t freq){
    // prescaler = base_clk / (freq*256)
    // frequency = base_clock / prescaler / 256
}

void setOffset(PWM_PIN pin/*, precent*/){

}

void setDutyCycle(PWM_PIN pin/*, precent*/){ // it says duty xD

}


#endif /*BOARD*/