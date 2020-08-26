/**
 * @brief   Header file that handles setting the macro BOARD 
 *          depending on the type of processor being used. 
 * 
 * @author  Amulek1416
 * @date    Aug 25 2020
 * 
 * @warning Not all boards may be included in this list. If you
 *          find that your board isn't included, then please help
 *          contribute to this library for others in the future.
 */

#ifndef BOARD_TYPE_H
#define BOARD_TYPE_H

// LIST OF MOST BOARDS USED WITH ARDUINO IDE 
    // ARDUINO
    #define _MEGA_ADK       0
    #define _BT             1
    #define _DUEMILANOVE    2
    #define _ETHERNET       3
    #define _FIO            4
    #define _GEMMA          5
    #define _LEONARDO       6
    #define _LILYPAD        7
    #define _LILYPAD_USB    8
    #define _MEGA           9
    #define _MEGA_2560      10
    #define _MICRO          11
    #define _MINI           12
    #define _NANO           13
    #define _NG             14
    #define _PRO            15
    #define _ROBOT_CTRL     16
    #define _ROBOT_MOTOR    17
    #define _UNO            18
    #define _YUN            19
    #define _DUE            20
    #define _ZERO           21
    #define _101            22
    #define _ESPLORA        23
    // TEENSY
    #define _TEENSY_2_0     24
    #define _TEENSY_pp_2_0  25
    #define _TEENSY_3_0     26
    #define _TEENSY_3_2     27 // Also for TEENSY 3.1
    #define _TEENSY_LC      28
    #define _TEENSY_3_5     29
    #define _TEENSY_3_6     30



// LOGIC TO DETERMINE WHAT BOARD IS BEING USED
#if defined(TEENSYDUINO) 
    //  --------------- Teensy -----------------
    #if defined(__AVR_ATmega32U4__)
        #define BOARD _TEENSY_2_0
    #elif defined(__AVR_AT90USB1286__)       
        #define BOARD _TEENSY_pp_2_0
    #elif defined(__MK20DX128__)       
        #define BOARD _TEENSY_3_0
    #elif defined(__MK20DX256__)       
        #define BOARD _TEENSY_3_2
    #elif defined(__MKL26Z64__)       
        #define BOARD _TEENSY_LC
    #elif defined(__MK64FX512__)
        #define BOARD _TEENSY_3_5
    #elif defined(__MK66FX1M0__)
        #define BOARD _TEENSY_3_6
    #else
       #error "UNKNOWN BOARD: Check to make sure the drivers are installed.\n\
               \t\tIf proper drivers have been installed, then please update\
               this file to contain your board's information for others in the\
               future.\n"
    #endif

#else 
    // --------------- Arduino ------------------
    #if   defined(ARDUINO_AVR_ADK)       
        #define BOARD _MEGA_ADK
    #elif defined(ARDUINO_AVR_BT)    // Bluetooth
        #define BOARD _BT
    #elif defined(ARDUINO_AVR_DUEMILANOVE)       
        #define BOARD _DUEMILANOVE
    #elif defined(ARDUINO_AVR_ESPLORA)       
        #define BOARD _ESPLORA
    #elif defined(ARDUINO_AVR_ETHERNET)       
        #define BOARD _ETHERNET
    #elif defined(ARDUINO_AVR_FIO)       
        #define BOARD _FIO
    #elif defined(ARDUINO_AVR_GEMMA)
        #define BOARD _GEMMA
    #elif defined(ARDUINO_AVR_LEONARDO)       
        #define BOARD _LEONARDO
    #elif defined(ARDUINO_AVR_LILYPAD)
        #define BOARD _LILYPAD
    #elif defined(ARDUINO_AVR_LILYPAD_USB)
        #define BOARD _LILYPAD_USB
    #elif defined(ARDUINO_AVR_MEGA)       
        #define BOARD _MEGA
    #elif defined(ARDUINO_AVR_MEGA2560)       
        #define BOARD _MEGA_2560
    #elif defined(ARDUINO_AVR_MICRO)       
        #define BOARD _MICRO
    #elif defined(ARDUINO_AVR_MINI)       
        #define BOARD _MINI
    #elif defined(ARDUINO_AVR_NANO)       
        #define BOARD _NANO
    #elif defined(ARDUINO_AVR_NG)       
        #define BOARD _NG
    #elif defined(ARDUINO_AVR_PRO)       
        #define BOARD _PRO
    #elif defined(ARDUINO_AVR_ROBOT_CONTROL)       
        #define BOARD _ROBOT_CTRL
    #elif defined(ARDUINO_AVR_ROBOT_MOTOR)       
        #define BOARD _ROBOT_MOTOR
    #elif defined(ARDUINO_AVR_UNO)       
        #define BOARD _UNO
    #elif defined(ARDUINO_AVR_YUN)       
        #define BOARD _YUN

    // These boards don't come pre-installed in the Arduino IDE:
    #elif defined(ARDUINO_SAM_DUE)       
        #define BOARD _DUE
    #elif defined(ARDUINO_SAMD_ZERO)       
        #define BOARD _ZERO
    #elif defined(ARDUINO_ARC32_TOOLS)       
        #define BOARD _101
    #else
       #error "UNKNOWN BOARD: Check to make sure the drivers are installed.\n\
               \t\tIf proper drivers have been installed, then please update\
               this file to contain your board's information for others in the\
               future.\n"
    #endif

#endif /*TEENSYDUINO*/

#endif /*BOARD_TYPE_H*/