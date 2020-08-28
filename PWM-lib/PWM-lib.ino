/**
 * @file    PWM-lib.ino
 * @date    Aug 26 2020
 * @author  Amulek1416
 * 
 * @brief   File for testing and debugging components 
 *          of the library. If everything in this file
 *          works on the board, then the board has been
 *          fully supported.
 * 
 * @warning This is still a working progress. Once the 
 *          first board (Arduino Uno) is fully implemented, 
 *          there will be more testing functions created. 
 *          Right now this is just used to make sure it 
 *          compiles and there are no syntax errors.
 */

#define NUM_PWM 1

#define FREQ_TEST
#define DUTY_CYCLE_TEST
// #define OUTPUT_TEST
// #define OFFSET_TEST
// #define MODE_TEST
// #define ADV_MODE_TEST

#include "PWM.h"

PWM_SIG _pwm[NUM_PWM];

void initialize_signals(void);

void handle_error(PWM_LOG error);
void print_PWM_testID(uint8_t ID);
void print_testResults(uint16_t numPassed, uint16_t numTests, String testString);

uint8_t freq_test(void);
uint8_t dutyCycle_test(void);
uint8_t output_test(void);
uint8_t offset_test(void);
uint8_t mode_test(void);
uint8_t advMode_test(void);

void setup(){
    uint16_t numPassed = 0;
    uint16_t numTests = 0;
    Serial.begin(115200);
    // Variables to contain all of the passed tests.
    initialize_signals();

    #ifdef FREQ_TEST
        numPassed += freq_test();
        numTests++;
    #endif

    #ifdef DUTY_CYCLE_TEST
        numPassed += dutyCycle_test();
        numTests++;
    #endif

    #ifdef OUTPUT_TEST
        numPassed += output_test();
        numTests++;
    #endif

    #ifdef OFFSET_TEST
        numPassed += offset_test();
        numTests++;
    #endif

    #ifdef MODE_TEST
        numPassed += mode_test();
        numTests++;
    #endif

    #ifdef ADV_MODE_TEST
        numPassed += advMode_test();
        numTests++;
    #endif

    print_testResults(numPassed, NUM_PWM*numTests, "FINAL RESULTS");
}

void loop(){ return; }

void initialize_signals(void){
    _pwm[0].pin = _11;
    _pwm[0].frequency = _31372_55Hz;
    _pwm[0].dutyCycle = 50;
    _pwm[0].mode = PWM_FAST;
    _pwm[0].advMode = PWM_OCR1A;
    _pwm[0].output = PWM_ENABLE;

    for(uint8_t i = 0; i < NUM_PWM; i++){
        pinMode((uint8_t) _pwm[i].pin, OUTPUT);
    }
}

void handle_error(PWM_LOG error){
    Serial.print("ERROR: ");
    switch(error){
        case UNDEFINED_PWM_VALUE:
            Serial.print("Undefined Value!");
            break;
        case INVALID_PWM_FREQ:
            Serial.print("Invalid PWM Frequency!");
            break;
        case INVALID_PWM_PIN:
            Serial.print("Invalid PWM Pin!");
            break;
        case INVALID_PWM_DUTY_CYCLE_VALUE:
            Serial.print("Duty Cycle Value Is Over 100\%");
            break;
        default:
            Serial.print("UNKNOWN ERROR!");
    }
    Serial.print("\n");
}

void print_PWM_testID(uint8_t ID){
    Serial.print("\tTesting PWM [");
    Serial.print(ID);
    Serial.print("]...");
}

void print_testResults(uint16_t numPassed, uint16_t numTests, String testString){
    Serial.print(testString.c_str());
    Serial.print(": ");
    Serial.print(numPassed);
    Serial.print("/");
    Serial.print(numTests);
    Serial.print("\n");
}

#ifdef FREQ_TEST
uint8_t freq_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n");
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setFreq(_pwm[i].pin, _pwm[i].frequency);
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
}
#endif

#ifdef DUTY_CYCLE_TEST
uint8_t dutyCycle_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n");
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setDutyCycle(_pwm[i].pin, _pwm[i].dutyCycle);
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
    return numPassed;
}
#endif

#ifdef OUTPUT_TEST
uint8_t output_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n");
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setOutputType(_pwm[i].pin, _pwm[i].output);
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
    return numPassed;
}
#endif

#ifdef OFFSET_TEST
uint8_t offset_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n");
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setDutyCycle(_pwm[i].pin, _pwm[i].offset);
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
    return numPassed;
}
#endif

#ifdef MODE_TEST
uint8_t mode_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n")
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setMode(_pwm[i].pin, _pwm[i].mode);
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
    return numPassed;
}
#endif

#ifdef ADV_MODE_TEST
uint8_t advMode_test(void){
    uint8_t numPassed = 0;
    Serial.print("Starting Frequency Test:\n");
    for(uint8_t i = 0; i < NUM_PWM; i++){
        print_PWM_testID(i);

        PWM_LOG log = setAdvancedMode(
                        _pwm[i].pin, 
                        _pwm[i].mode, 
                        _pwm[i].advMode
                      );
        if(log != NO_PWM_ERROR){
            handle_error(log);
        } else {
            Serial.print("Passed!\n");
            numPassed++;
        }
    }
    print_testResults(numPassed, NUM_PWM, "RESULTS");
    return numPassed;
}
#endif