/* 
 * File:   TimeDelay.c
 * Author: MichaelDonCorleone
 *
 * Created on October 27, 2021, 3:12 PM
 */
void Delay_ms(unsigned int time_ms) {
    //Configuring T2CON register
    T2CONbits.T32 = 0; //Operate as 16 bit timer
    T2CONbits.TCS = 0; // Set internal clock usage

    //Prescaler settings of T2CON register
    T2CONbits.TCKPS0 = 1; //
    T2CONbits.TCKPS1 = 1; // These two lines set prescaling to 8x

    //Interrupt Configuration for Timer 2
    //IPC1bits.T2IP = 3; //Set Priority level = 3
    IEC0bits.T2IE = 1; //Timer 2 interrupt enabled
    IFS0bits.T2IF = 0; //Clear Timer 2 Flag



    PR2 = ((time_ms / 1000) * 15625)/4; //Number of clock cycles that need to elapse
    T2CONbits.TON = 1; //Timer 2 Starts here
    TMR2Flag = 1; //Timer 2 Global variable is enabled
    Idle();
    return;
}

 void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void)
 {
    TMR2Flag = 0; //Reset the timer Flag to 
                  //indicate an input interrupted the LED Flashing
    IFS1bits.CNIF = 0; //Clear interrupt Register Flag
    CNFlag = 1; // Set our CN Global Flag to True/1
 }

 
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void) {
    IFS0bits.T2IF = 0; //Clear timer 2 interrupt flag
    T2CONbits.TON = 0; //Stop timer
    TMR2 = 0; //Reset the TMR2 register after the interrupt occurs.
    //TMR2Flag = 1; //Timer complete
} 
