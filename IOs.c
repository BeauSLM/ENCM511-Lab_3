/* 
 * File:   IOs.c
 * Author: MichaelDonCorleone
 *
 * Created on October 27, 2021, 3:12 PM
 */
#include <xc.h>
#include <p24F16KA101.h>
#include "IOs.h"

extern int CNFlag;
extern int TMR2Flag;
extern void Delay_ms(unsigned int);

void IOinit() {
    TRISBbits.TRISB8 = 0; //SET GPIO RB8 as a digital output.
	
    TRISAbits.TRISA2 = 1; //SET GPIO RA2 as a digital input.
    TRISAbits.TRISA4 = 1; //SET GPIO RA4 as a digital input.
    TRISBbits.TRISB4 = 1; //SET GPIO RB4 as a digital input.
	
    CNPU2bits.CN30PUE = 1; //Enables Pull up resistor on RA2/ CN30
    CNPU1bits.CN0PUE = 1; //Enables Pull up resistor on RA4/ CN0
    CNPU1bits.CN1PUE = 1; //Enables Pull resistor on RB4 / CN1
	
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
	
    IPC4bits.CNIP = 4; //sets priority for Input Change Notification
	IFS1bits.CNIF = 0; //Clear the CNI flag
    IEC1bits.CNIE = 1; //Input Change Notification Interrupts Enabled
    CNEN1bits.CN1IE = 1; //Enable input change Notif on RB4
    CNEN1bits.CN0IE = 1; //Enable input change Notif on RA4
    CNEN2bits.CN30IE = 1; //Enable input change Notif on RA2
    LATBbits.LATB8 = 0; //Turn off LED on start up.
}

void LED_Cycle(unsigned int time_ms) {
    LATBbits.LATB8 = 1;
    Delay_ms(time_ms);
    LATBbits.LATB8 = 0;
    Delay_ms(time_ms);
}

void IOcheck() {
    if(CNFlag == 1 || TMR2Flag == 1) {
        if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1) {
            CNFlag = 0; // Set our CN Global Flag to False after we handle the interrupt
            LATBbits.LATB8 = 0; //turn LED off in case no button is pressed
        } else if((PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1)) {
            //Just button on RA2 GPIO is pressed - shorted
            CNFlag = 0; // Set our CN Global Flag to False after we handle the interrupt
            LED_Cycle(1000);
        } else if((PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1)) {
            CNFlag = 0; // Set our CN Global Flag to False after we handle the interrupt
            LED_Cycle(2000);
            //Just button on RA4 GPIO is pressed - shorted
        } else if((PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0)) {
            CNFlag = 0; // Set our CN Global Flag to False after we handle the interrupt
            LED_Cycle(3000);
            //Just button on RB4 GPIO is pressed - shorted
        } else {
            CNFlag = 0; // Set our CN Global Flag to False after we handle the interrupt
            LATBbits.LATB8 = 1; //turn LED on if multiple buttons are pressed
        }
    }
}