/*
 * File:   main.c
 * Author: Rushi V
 *
 * Created on September 26, 2020, 9:17 PM
 */

// MPLAB header libraries
#include <xc.h>

#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "config.h"
#include "IOs.h"
#include "TimeDelay.h"
#include "ChangeClk.h"


//Preprocessor directives - Configuration bits for MCU start up
//test this side
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
int CNFlag = 0;
int TMR2Flag = 0;

//MAIN
void main(void) {
     
    // Change Clock
     NewClk(32); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
     
   // Initialize IOs for low-power wake-up
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    
    IOinit();
    while(1) {
        IOcheck();
    }
    return 0;
    
    
    return;
}
