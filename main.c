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

const int CLOCK_SPEED = 32;
//8 for 8MHz; 
//500 for 500kHz; 
//32 for 32kHz;

//global variable flags
int CNFlag = 0;
int TMR2Flag = 0;

int PB0Pressed = 0;
int PB1Pressed = 0;
int PB2Pressed = 0;

//MAIN
int main(void) {
/*
    //Testing code begins idk what this does
    //Clock output on REFO/RB15 - Testing purposes only
    TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; //Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; //Ref oscillator is disabled in sleep mode
    REFOCONbits.ROSEL = 0; //Output base clk showing clock switch
    REFOCONbits.RODIV = 0b0000;
    //end of test code
 */
    NewClk(CLOCK_SPEED); // Initializes clock based on CLOCK_SPEED
    IOinit(); // Initialize IOs and IO Change Interrupt
    while(1) {
        Idle();
    }
    return 0;
    
}
