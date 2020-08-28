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

// Logic to determine if the board being used is supported
#if BOARD == _UNO
    #define BOARD_SUPPORTED
#else
    #warning "BOARD_UNSUPPORTED: This may cause undesired operation!"
    #define BOARD_UNSUPPORTED
#endif /*BOARD*/

/** @brief Used to define the prescaler of the PWM */
typedef uint16_t prescaler_t;

/** 
 * @brief   Enum of all possible PWM signal frequencies
 * 
 * @details Since PWM frequencies are usually set by changing 
 *          a few bits, this limits the number of possible
 *          frequencies. This enum helps to set a PWM frequency
 *          to one available to the specified board. All values 
 *          are given in Hz with the second underscore signifying 
 *          a decimal point. 
 */
typedef enum PWM_FREQUENCY {
        _0Hz,
    // All of these boards have the same available frequencies
    #if (BOARD == _UNO)         || \
        (BOARD == _NANO)        || \
        (BOARD == _MEGA)        || \
        (BOARD == _MEGA_2560)   || \
        (BOARD == _MEGA_ADK)    || \
        (BOARD == _LILYPAD)     || \
        (BOARD == _LILYPAD_USB)
        _62500_0Hz,
        _31372_55Hz,
        _7812_5Hz,
        _3921_16Hz,
        _980_39Hz,
        _976_56Hz,
        _490_2Hz,
        _245_1Hz,
        _244_14Hz,
        _122_55Hz,
        _61_04Hz,
        _30_64Hz
    // end UNO, NANO, MEGA, MEGA_ADK, MEGA_2560, LILLYPAD, LILLYPAD_USB
    #else // There are a large amount of available frequencies available
        _null_Hz
    #endif /*BOARD*/
} PWM_FREQUENCY;


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
    PWM_TOGG_COMP   = 1,
    PWM_ENABLE      = 2,
    PWM_INVERTED    = 3,
} PWM_OUTPUT;

typedef enum PWM_LOG {
    NO_PWM_ERROR,
    UNDEFINED_PWM_VALUE,
    INVALID_PWM_FREQ,
    INVALID_PWM_PIN,
    INVALID_PWM_DUTY_CYCLE_VALUE
} PWM_ERROR;

/**
 * @brief   A struct that can be used to help set and manage 
 *          different PWM signals
 */
typedef struct {
    union {
        PWM_FREQUENCY frequency;
        uint32_t open_frequency;
    };
    PWM_PIN pin;
    PWM_MODE mode;
    PWM_ADV_MODE advMode;
    PWM_OUTPUT output;
    uint16_t dutyCycle;
    uint8_t offset;
} PWM_SIG;

/** 
 * @brief   Initializes PWM signal based on settings set in a PWM_SIG
 * 
 * @param   PWM     A PWM_SIG type containing all PWM settings
 * 
 * @warning This function is still in development
 */
void PWM_init(PWM_SIG *pwm);

/**
 * @brief   Sets the frequency of a PWM signal
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @param   freq    PWM_FREQUENCY type that takes in a specific frequency
 * 
 * @warning Not all PWM pins can support the frequencies given in PWM_FREQUENCY.
 *          To see what pins can produce what frequencies, see the board's
 *          documentaion. There is no guarentee that this function will return
 *          any errors if a pin doesn't support that frequency.
 * 
 * @warning Not all pins can be set to different frequencies. This depends on
 *          what timer each pin is connected to. See your board's documentaion
 *          for more information on what pins can have different frequencies.
 */
PWM_LOG setFreq(PWM_PIN pin, PWM_FREQUENCY freq);

/**
 * @brief   Similar to setFreq(), but can take in an unspecified number
 * 
 * @details This function exists to be flexible with any boards that may
 *          potentially have an almost unlimited range of frequencies.
 * 
 * @param   pin     PWM_PIN type. This type is used to help debug and 
 *                  ensure the programmer is using the correct pin for 
 *                  the specfied board.
 * 
 * @param   freq    uint32_t type. This can be used in combinations with 
 *                  the Hz(), kHz, and MHz() macros to easily define the
 *                  desired units in a more readable way.
 * 
 * @warning This function is not compatible with all boards.
 */
void setOpenFrequency(PWM_PIN pin, uint32_t freq);

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
 * @param   percent uint16_t type. This will take a percentage (0-100)
 *                  and set it as the duty cycle.
 * 
 * @warning This function is still in development
 */
PWM_LOG setDutyCycle(PWM_PIN pin, uint16_t percent); // it says duty :D

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