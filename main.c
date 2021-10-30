/*
 * File:   main.c
 * Author: Rushi V
 *
 * Created on September 26, 2020, 9:17 PM
 */

// MPLAB header libraries
#include <xc.h>

#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "config.h"
#include "IOs.h"
#include "TimeDelay.h"
#include "ChangeClk.h"
#include "UART2.h"


//Preprocessor directives - Configuration bits for MCU start up
//test this side
int CNFlag = 0;
int TMR2Flag = 0;

//MAIN
int main(void) {
/*
    //Testing code begins
    //Clock output on REFO/RB15 - Testing purposes only
    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; //Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; //Ref oscillator is disabled in sleep mode
    REFOCONbits.ROSEL = 0; //Output base clk showing clock switch
    REFOCONbits.RODIV = 0b0000;
    //end of test code
    // Change Clock
     NewClk(32); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
*/
   // Initialize IOs for low-power wake-up
    IOinit();
    while(1) {
        Idle();
    }
    return 0;
    
}
