#pragma config OSC = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#include <stdlib.h>
#include <pic18f4520.h>
#include "setting_hardaware/uart.h"
#include <stdio.h>
#include <string.h>

char str[20];



void delay(int num)
{
    int i = 0;
    while(i<num)
        i++;
    return;
}


void __interrupt(high_priority) HI_ISR()
{
//    if(INTCONbits.INT0IF==1 && INTCON3bits.INT1IF==1)
//    {
//        INTCONbits.INT0IE=0;
//        INTCON3bits.INT1IE=0;
//        UART_Write_Text("FAQ!\n");
//        INTCONbits.INT0IF=0;
//        INTCONbits.INT0IE=1;
//        INTCON3bits.INT1IF=0;
//        INTCON3bits.INT1IE=1;
//    }
//    else 
    if(INTCONbits.INT0IF==1)
    {
         if(LATD==0b00000001)
         {
            LATD=0b00000000;
         }else
        {
            LATD=0b00000001;
        }
        
        INTCONbits.INT0IE=0;
        UART_Write_Text("L\n");
        UART_Write_Text("pause\n");
        INTCONbits.INT0IF=0;
        INTCONbits.INT0IE=1;
        
        
        
    }else if(INTCON3bits.INT1IF==1)
    {
         if(LATD==0b00000001)
         {
            LATD=0b00000000;
         }else
        {
            LATD=0b00000001;
        }
        INTCON3bits.INT1IE=0;
        UART_Write_Text("R\n");
        UART_Write_Text("pause\n");
        INTCON3bits.INT1IF=0;
        INTCON3bits.INT1IE=1;
    }else if(INTCON3bits.INT2IF==1)
    {
         if(LATD==0b00000001)
         {
            LATD=0b00000000;
         }else
        {
            LATD=0b00000001;
        }
        INTCON3bits.INT2IE=0;
        UART_Write_Text("G\n");
        UART_Write_Text("pause\n");
        INTCON3bits.INT2IF=0;
        INTCON3bits.INT2IE=1;
    }
//    else if(INTCON3bits.INT3IF==1)
//    {
//         if(LATD==0b00000001)
//         {
//            LATD=0b00000000;
//         }else
//        {
//            LATD=0b00000001;
//        }
//        INTCON3bits.INT3IE=0;
//        UART_Write_Text("A\n");
//        UART_Write_Text("pause\n");
//        INTCON3bits.INT3IF=0;
//        INTCON3bits.INT3IE=1;
//    }               
    delay(1000);

    
    return;
}
void Mode3(){
    ClearBuffer();
    //UART_Write_Text("Hi ");
    //UART_Write_Text("mode3\r\n");
    TRISBbits.RB0 = 1;              //set RA0 as input port
    TRISBbits.RB1  = 1;
    TRISBbits.RB2  = 1;
    TRISBbits.RB3  = 1;
    
    TRISD = 0x0;                       //set RD0~RD3 as output
    LATD = 0x0;                        //initialize RD0~RD3 output 0(no light)
    INTCONbits.GIE = 1;             //set global interrupt bit
    RCONbits.IPEN=1;
    INTCONbits.INT0IE=1;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT2IE=1;
   // INTCON3bits.INT3IE=1;
    INTCON2bits.RBPU=1;
    INTCONbits.PEIE = 1;            //Enable peripheral interrupt
    
    
    while(1);
    
}


void main(void) 
{
    UART_Initialize();
    VR_Initialize();
    while(1)
    {
        ClearBuffer();
        strcpy(str , GetString() );
        if(str[0]=='H' && str[1]=='e' && str[2] == 'l' && str[3] == 'l' && str[4] == 'o')
        {
            Mode3();
            ClearBuffer();
        }
    }
    return;
}

