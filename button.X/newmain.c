#include <18F4550.h>
#fuses  HSPLL PLL2 CPUDIV1 USBDIV VREGEN NOMCLR
#use delay(clock = 48000000)
#include <usb_desc_mouse.h>
#include<pic18_usb.h>
#include<usb.c>
#use fast_io(B)

char out_data[4];
void main(){
  setup_adc_ports(NO_ANALOGS);                          // Configure all AN pins as digital
  output_b(0);                                          // PORTB initial state
  set_tris_b(0x3F);                                     // Configure RB0 to RB5 as inputs
  port_b_pullups(TRUE);                                 // Enable PORTB pull-ups
  usb_init_cs();                                        // Initialize USB hardware
  delay_ms(1000);
  while(TRUE){
    usb_task();
    if(usb_enumerated()){                               // If the device has been enumerated by the PC
      while(!input(PIN_B0)){
        out_data[0] = 0;
        out_data[1] = 1;
        out_data[2] = 0;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
      }
      while(!input(PIN_B1)){
        out_data[0] = 0;
        out_data[1] = -1;
        out_data[2] = 0;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
      }
      while(!input(PIN_B2)){
        out_data[0] = 0;
        out_data[1] = 0;
        out_data[2] = 1;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
      }
      while(!input(PIN_B3)){
        out_data[0] = 0;
        out_data[1] = 0;
        out_data[2] = -1;
        out_data[3] = 0;
        usb_put_packet(1, out_data, 4, USB_DTS_TOGGLE);
      }
      while(!input(PIN_B4)){
        out_data[0] = 1;
        out_data[1] = 0;
        out_data[2] = 0;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
      }
      while(!input(PIN_B5)){
        while(!input(PIN_B5));
        out_data[0] = 3;
        out_data[1] = 0;
        out_data[2] = 0;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
      }
        out_data[0] = 0;
        out_data[1] = 0;
        out_data[2] = 0;
        out_data[3] = 0;
        usb_put_packet(1,out_data,4,USB_DTS_TOGGLE);
    }
  }
}