/**
 * 
 */
#include "../board_type.h"

#if BOARD == _UNO

#include <Arduino.h>
#include "../PWM.h"

void setMode(PWM_PIN pin, PWM_MODE mode){
    // Here we need to set the Waveform Generation Mode bits(WGM).
    // These control the overall mode of the timer and are split
    // between TCCnA and TCCnB
    switch(pin){
        case _3:
        case _11:
            // Use timer2
            switch (mode){
                case PWM_FAST:
                    TCCR2A |= (_BV(WGM21) | _BV(WGM20));
                    break;
                case PWM_PHASE_CORR:
                    TCCR2A |= (_BV(WGM20));  // Set this bit
                    TCCR2A &= ~(_BV(WGM21)); // Clear this bit
                    break;
                case PWM_CLEAR_TIMER_ON_COMP:
                case PWM_PHASE_FREQ_CORR:
                    TCCR2A &= ~(_BV(WGM20)); // Clear this bit
                    TCCR2A |= (_BV(WGM21));  // Set this bit
                    break;
                case PWM_NORMAL:
                default: // Clear all WGM bits
                    TCCR2A &= ~(_BV(WGM21) | _BV(WGM20));
                    TCCR2B &= ~(_BV(WGM22));
                    break;
            } // end timer2
            break;
        case _5:
        case _6:
            // Use timer0
            switch(mode){
                case PWM_FAST:
                    TCCR0A |= (_BV(WGM01) | _BV(WGM00));
                    break;
                case PWM_PHASE_CORR:
                    TCCR0A |= (_BV(WGM00));
                    break;
                case PWM_CLEAR_TIMER_ON_COMP:
                    TCCR0A |= (_BV(WGM01));
                    break;
                case PWM_NORMAL:
                default: // Clear all WGM bits
                    TCCR0A &= ~(_BV(WGM01) | _BV(WGM00));
                    TCCR0B &= ~(_BV(WGM02));
                    break;
            }
            break;
        default:
            // Use timer1
            switch (mode){
                case PWM_FAST:
                    // There are multiple types of PWM_FAST, but we will
                    // use the 8-bit one by default. Any other configuration 
                    // can be set in setAdvancedMode()
                    TCCR1A |= (_BV(WGM10));
                    TCCR1A &= ~(_BV(WGM11));
                    TCCR1B |= (_BV(WGM12));
                    TCCR1B &= ~(_BV(WGM13));
                    break;
                case PWM_PHASE_CORR:
                    // There are multiple types of PWM_PHASE_CORR, but we will
                    // use the 8-bit one by default. Any other configuration 
                    // can be set in setAdvancedMode()
                    TCCR1A |= (_BV(WGM10));
                    TCCR1A &= ~(_BV(WGM11));
                    TCCR1B &= ~(_BV(WGM13) | _BV(WGM12));
                    break;
                case PWM_CLEAR_TIMER_ON_COMP:
                    // There are multiple types of PWM_CLEAR_TIMER_ON_COMP,   
                    // but we will default to the TOP being OCR1A. Any  
                    // other configurations can be set in setAdvancedMode()
                    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));
                    TCCR1B |= (_BV(WGM12) | _BV(WGM13));
                    break;
                case PWM_PHASE_FREQ_CORR:
                    // There are multiple types of PWM_PHASE_FREQ_CORR, but  
                    // we will default to the TOP being OCR1A. Any other 
                    // configurations can be set in setAdvancedMode()
                    TCCR1A |= (_BV(WGM10));
                    TCCR1A &= ~(_BV(WGM11));
                    TCCR1B &= ~(_BV(WGM12));
                    TCCR1B |= (_BV(WGM13));
                    break;
                case PWM_NORMAL:
                default: // Clear all WGM bits
                    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));
                    TCCR1B &= ~(_BV(WGM13) | _BV(WGM12));
                    break;
            } // end timer1
            break;
    } // end pin
}

void setAdvancedMode(PWM_PIN pin, PWM_MODE mode, PWM_ADV_MODE setting) {
    setMode(pin, mode); // Most of the work is already done in the normal function
    switch(pin){
    case _3:
    case _11:
        // Use timer2
        switch(setting){
            case PWM_OC0A_TOG_COMP_MATCH:
                TCCR2B |= (_BV(WGM22));
                break;
            case PWM_OC0A_DISCONNECT:
            default:
                TCCR2B &= ~(_BV(WGM22));
                break;
        } // end timer2
        break;
    case _5:
    case _6:
        // Use timer0
        switch(setting){
            case PWM_OC0A_TOG_COMP_MATCH:
                TCCR0B |= (_BV(WGM02));
                break;
            case PWM_OC0A_DISCONNECT:
            default:
                TCCR0B &= ~(_BV(WGM02));
                break;
        }// end timer0
        break;
    default:
        // Use timer1
        switch(setting){
            case PWM_8bit:
                break; // This is all done by default in setMode()
            case PWM_9bit:
                TCCR1A &= ~(_BV(WGM10));
                TCCR1A |= (_BV(WGM11));
                break;
            case PWM_10bit:
                TCCR1A |= (_BV(WGM11) | _BV(BGM10));
                break;
            case PWM_ICR1:
                switch(mode){
                    case PWM_FAST:
                        TCCR1A &= ~(_BV(WGM10));
                        TCCR1A |= (_BV(WGM11));
                        TCCR1B |= (_BV(WGM13) | _BV(WGM12));
                        break;
                    case PWM_PHASE_CORR:
                        TCCR1A &= ~(_BV(WGM10));
                        TCCR1A |= (_BV(WGM11));
                        TCCR1B |= (_BV(WGM13));
                        break;
                    case PWM_CLEAR_TIMER_ON_COMP:
                        TCCR1B &= ~(_BV(WGM12));
                        break;
                    case PWM_PHASE_FREQ_CORR:
                        TCCR1A &= ~(_BV(WGM10));
                        break;
                    default:
                        break;
                } // end mode
                break;
            case PWM_OCR1A:
                switch(mode){
                    case PWM_FAST:
                        TCCR1A |= (_BV(WGM11) | _BV(WGM10));
                        TCCR1B |= (_BV(WGM13) | _BV(WGM12));
                        break;
                    case PWM_PHASE_CORR:
                        TCCR1A |= (_BV(WGM11));
                        TCCR1B |= (_BV(WGM13));
                        break;
                    case PWM_CLEAR_TIMER_ON_COMP:
                    case PWM_PHASE_FREQ_CORR:
                    default:
                        break;
                } // end mode
                break;
            default:
                break;
        } // end timer1
        break;
    } // end pin
}

void setOutputType(PWM_PIN pin, PWM_OUTPUT type){
    switch(pin)
    {
        case _3:
        case _11:
            // Use timer2
            switch(type){
                case PWM_TOGG_COMP:
                    TCCR2A |= (_BV(COM2A0));
                    TCCR2A &= ~(_BV(COM2A1));
                    break;
                case PWM_ENABLE:
                    TCCR2A &= ~(_BV(COM2A0));
                    TCCR2A |= (_BV(COM2A1));
                    break;
                case PWM_INVERTED:
                    TCCR2A |= (_BV(COM2A1) | _BV(COM2A2));
                    break;
                case PWM_DISABLE:
                default:
                    TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A2));
                    break;
            } // end type
            break;
        case _5:
        case _6:
            // Use timer0
            switch(type){
                case PWM_TOGG_COMP:
                    TCCR0A |= (_BV(COM0A0));
                    TCCR0A &= ~(_BV(COM0A1));
                    break;
                case PWM_ENABLE:
                    TCCR0A &= ~(_BV(COM0A0));
                    TCCR0A |= (_BV(COM0A1));
                    break;
                case PWM_INVERTED:
                    TCCR0A |= (_BV(COM0A1) | _BV(COM0A2));
                    break;
                case PWM_DISABLE:
                default:
                    TCCR0A &= ~(_BV(COM0A1) | _BV(COM0A2));
                    break;
            } // end type
            break;
        default:
            // Use timer1
            switch(type){
                case PWM_TOGG_COMP:
                    TCCR1A |= (_BV(COM1A0));
                    TCCR1A &= ~(_BV(COM1A1));
                    break;
                case PWM_ENABLE:
                    TCCR1A &= ~(_BV(COM1A0));
                    TCCR1A |= (_BV(COM1A1));
                    break;
                case PWM_INVERTED:
                    TCCR1A |= (_BV(COM1A1) | _BV(COM1A2));
                    break;
                case PWM_DISABLE:
                default:
                    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A2));
                    break;
            } // end type
            break;
    }
}

#endif /*BOARD*/