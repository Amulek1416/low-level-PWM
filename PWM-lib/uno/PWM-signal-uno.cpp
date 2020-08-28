/**
 * 
 */
#include "../board_type.h"

#if BOARD == _UNO

#include "../PWM.h"
#include <Arduino.h>
#include <stdint.h>

void PWM_init(PWM_SIG *PWM){ 
    pinMode(PWM->pin, OUTPUT);
}

// The following link contains the information about the frequencies:
//      http://arduinoinfo.mywikis.net/wiki/Arduino-PWM-Frequency
PWM_LOG setFreq(PWM_PIN pin, PWM_FREQUENCY freq){
    PWM_LOG eFlag = NO_PWM_ERROR;
    switch (pin){
        case _3:
        case _11:
            // timer 2
            TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
            switch(freq){
                case _31372_55Hz:
                    TCCR2B |= (_BV(CS20));
                    break;
                case _3921_16Hz:
                    TCCR2B |= (_BV(CS21));
                    break;
                case _980_39Hz:
                    TCCR2B |= (_BV(CS21) | _BV(CS20));
                    break;
                case _490_2Hz:
                    TCCR2B |= (_BV(CS22));
                    break;
                case _245_1Hz:
                    TCCR2B |= (_BV(CS22) | _BV(CS20));
                    break;
                case _122_55Hz:
                    TCCR2B |= (_BV(CS22) | _BV(CS21));
                    break;
                case _30_64Hz:
                    TCCR2B |= (_BV(CS22) | _BV(CS21) | _BV(CS20));
                    break;
                default:
                    eFlag = INVALID_PWM_FREQ;
                    break;
            } // end freq
            break;
        case _9:
        case _10:
        // timer 1
            TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
            switch(freq){
                case _31372_55Hz:
                    TCCR1B |= (_BV(CS10));
                    break;
                case _3921_16Hz:
                    TCCR1B |= (_BV(CS11));
                    break;
                case _490_2Hz:
                    TCCR1B |= (_BV(CS11) | _BV(CS10));
                    break;
                case _122_55Hz:
                    TCCR1B |= (_BV(CS12));
                    break;
                case _30_64Hz:
                    TCCR1B |= (_BV(CS12) | _BV(CS10));
                    break;
                default:
                    eFlag = INVALID_PWM_FREQ;
                    break;
            } // end freq
            break;
        case _5:
        case _6:
            // timer 0
            TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));
            switch(freq){
                case _62500_0Hz:
                    TCCR0B |= (_BV(CS00));
                    break;
                case _7812_5Hz:
                    TCCR0B |= (_BV(CS01));
                    break;
                case _976_56Hz:
                    TCCR0B |= (_BV(CS01) | _BV(CS00));
                    break;
                case _244_14Hz:
                    TCCR0B |= (_BV(CS02));
                    break;
                case _61_04Hz:
                    TCCR0B |= (_BV(CS02) | _BV(CS00));
                    break;
                default:
                    eFlag = INVALID_PWM_FREQ;
                    break;
            } // end freq
            break;
        default:
            eFlag = INVALID_PWM_PIN;
            break;
    }
    return eFlag;
}

void setOffset(PWM_PIN pin/*, precent*/){

}

PWM_LOG setDutyCycle(PWM_PIN pin, uint16_t percent){ // it says duty xD
    PWM_LOG eFlag = 
        (percent <= 100) ? 
        NO_PWM_ERROR : 
        INVALID_PWM_DUTY_CYCLE_VALUE;
    // This is because the PWM for pins 9 and 10 use a 16-bit timer
    uint16_t dutyCycle16 = 0;
    uint8_t dutyCycle8 = 0;

    if((pin == _9) || (pin == _10))
        dutyCycle16 = (percent * 0xFFFF) / 100;
    else
        dutyCycle8 = (percent * 0xFF) / 100;

    switch(pin){
        case _3:
            OCR2B = dutyCycle8;
            break;
        case _5:
            OCR0B = dutyCycle8;
            break;
        case _6:
            OCR0A = dutyCycle8;
            break;
        case _9:
            OCR1A = dutyCycle16;
            break;
        case _10:
            OCR1B = dutyCycle16;
            break;
        case _11:
            OCR2A = dutyCycle8;
            break;
        default:
            eFlag = INVALID_PWM_PIN;
            break;
    }
}


#endif /*BOARD*/