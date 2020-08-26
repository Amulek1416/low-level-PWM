/**
 * @file    PWM.h
 * @date    Aug 25 2020
 * @author  Amulek1416
 * 
 * @brief   Header file for a low-level PWM library.
 *
 * @details This is a low-level PWM library that gives
 *          a large amount of configuration options that
 *          the standard Arduino library doesn't provide.
 * 
 * @warning None of this has been tested due to my current
 *          lack of an oscilloscope. However, it does compile.
 */

#ifndef PWM_H
#define PWM_H

/** @brief To specify a value in units of Hz */
#define Hz(x)   (x)

/** @brief To specify a value in units of kHz */
#define kHz(x)  (x * 1000)

/** @brief To specify a value in units of MHz */
#define MHz(x)  (kHz(x) * 1000)


#include <stdint.h>
#include "board_type.h"

/** @brief Used to define the prescaler of the PWM */
typedef uint16_t prescaler_t;

/** @brief Used to define the desired frequency for the PWM */
typedef uint32_t freq_t;

/**
 *  @brief  This is to help debug and make sure that the 
 *          pin being entered is the correct pin for that 
 *          specific board.
 * 
 * @details Since some boards may not be defined, there are
 *          20 pins available by default.
 */
typedef enum PWM_PIN {
    // TODO: Set the PWM pins for the different boards 
    #if BOARD == _UNO
        _3  = 3,
        _5  = 5,
        _6  = 6,
        _9  = 9,
        _10 = 10,
        _11 = 11
    #else // Default to 20 pins to cover most boards currently undefined 
        _0  = 0,
        _1  = 1,
        _2  = 2,
        _3  = 3,
        _4  = 4,
        _5  = 5,
        _6  = 6,
        _7  = 7,
        _8  = 8,
        _9  = 9,
        _10 = 10,
        _11 = 11,
        _12 = 12,
        _13 = 13,
        _14 = 14,
        _15 = 15,
        _16 = 16,
        _17 = 17,
        _20 = 20
    #endif /*BOARD*/
} PWM_PIN;

/**
 * @brief   Different confirgurations that can be applied 
 *          depending on the timer being used.
 */
typedef enum PWM_ADV_MODE {
    #if BOARD == _UNO
        PWM_OC0A_DISCONNECT     = 0,
        PWM_OC0A_TOG_COMP_MATCH = 1,
        PWM_8bit                = 2,
        PWM_9bit                = 3,
        PWM_10bit               = 4,
        PWM_ICR1                = 5,
        PWM_OCR1A               = 6
    #endif /*BOARD*/
} PWM_ADV_MODE;

/**
 * @brief   Generalized PWM modes that can be easily be set.
 * 
 * @details This can be used along with PWM_ADV_MODE to have 
 *          fine control over the PWM modes.
 */
typedef enum PWM_MODE {
    #if BOARD == _UNO
        PWM_NORMAL              = 0,
        PWM_FAST                = 1,
        PWM_PHASE_CORR          = 2,
        PWM_CLR_TIMER_ON_CMP    = 3,
        PWM_PHASE_FREQ_CORR     = 4,
        PWM_CLEAR_TIMER_ON_COMP = 5
    #endif /*BOARD*/
} PWM_MODE;

/**
 * @brief   This is used to invert and enable/disable the PWM signal.
 * 
 * @details If PWM_ENABLE is selected, it will produce a non-inverted 
 *          PWM signal. If PWM_INVERTED is selected, it will enable the 
 *          PWM as well as invert the PWM signal.
 */
typedef enum PWM_OUTPUT {
    PWM_DISABLE     = 0,
    PWM_ENABLE      = 1,
    PWM_INVERTED    = 2,
} PWM_OUTPUT;

/**
 * @brief   A struct that can be used to help set and manage 
 *          different PWM signals
 */
typedef struct PWM_SIG {
    PWM_PIN pin;
    PWM_MODE mode;
    uint8_t inverted;

    // Since there is no reason both the prescaler and the frequency need
    // to be set at the same time, lets make this a union to save memory.
    // Note that more memory will actually be taken up if the prescaler
    // is used instead, but this just saves and extra 2-4 bytes
    union {  
        prescaler_t prescaler;
        freq_t frequency;
    };
} PWM_SIG;

/** 
 * @brief   Initializes PWM signal based on settings set in a PWM_SIG
 * 
 * @param   PWM     A PWM_SIG type containing all PWM settings
 * 
 * @warning This function is still in development
 */
void PWM_init(PWM_SIG PWM);

/**
 * @brief   Sets the frequency of a PWM signal
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @param   freq    freq_t type. This can be used in combinations with 
 *                  the Hz(), kHz, and MHz() macros to easily define the
 *                  desired units in a more readable way
 * 
 * @warning This function is still in development
 */
void setFreq(PWM_PIN pin, freq_t freq);

/**
 * @brief   Gives a phase-shifted PWM signal
 * 
 * @warning This functions is still in development
 */
void setOffset(PWM_PIN pin/*, precent*/);

/**
 * @brief   Sets general settings for given PWM mode
 * 
 * @note    For more advanced settings, see setAdvancedMode()
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @param   mode    PWM_MODE type. Basic settings for different PWM modes.
 * 
 * @warning This function is still in development
 */
void setMode(PWM_PIN pin, PWM_MODE mode);

/**
 * @brief   Used in combination with setMode() to have finer control 
 *          over PWM settings
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @param   mode    PWM_MODE type. Basic settings for different PWM modes.
 * 
 * @param setting   PWM_ADV_MODE type. This is where finer controls can be 
 *                  set for different PWM modes.
 * 
 * @warning This function is still in development
 */
void setAdvancedMode(PWM_PIN pin, PWM_MODE mode, PWM_ADV_MODE setting);

/**
 * @brief   Sets the duty cycle for a given PWM
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @warning This function is still in development
 */
void setDutyCycle(PWM_PIN pin/*, precent*/); // xD duty

/**
 * @brief   Sets desired output type of PWM
 * 
 * @details The different outputs are enabled, disabled, and inverted. 
 *          See PWM_OUTPUT for more information.
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @warning This function is still in development
 */
void setOutputType(PWM_PIN pin, PWM_OUTPUT type);

#endif /*PWM_H*/