/*
 * AT90USB1287.c
 *
 * Created: 31.10.2015 15:29:18
 *  Author: medlem
 */ 

//read the values from joystick
//read the values from touch
//pwm the values from joystick on PB or PD
//spi the values over canbus
//uart to rs232 for debug
//oled control from atmega162 over can
//oled control from atmega162 over parallel if extsel


//#define F_CPU 16000000 //defined in toolchain

#include <avr/io.h>
#include <util/delay.h>
//#include "can.h"
//#include "mcp2515defines.h"

#include "uart.h"
//#include "pwm.h"
#include "board.h"
//#include "adc.h"
#include "joy.h"
#include "display/oled.h"
#include "display/menu.h"
#include "display/gui.h"
#include "touch.h"
#include <stdlib.h>

int main(void){
	board_init();
	uart_init();
	oled_init();
	
	touch_init(30, 30, 30, 30); //TOUCH DOES NOT WORK WITH JTAG CONNECTED!!!!!!!!!!!!!!!!! NOT WORKING WITH ADC
	//WORKING ON ADC AND TOUCH FIX!
	//adc_init();
	//pwm_init();
	//can_init(MODE_NORMAL);
	uint8_t selected=1;
	menu_item_t *menu=menu_get();
	uint8_t ls, rs, lb, rb;
	//can_message_t* msg13 = malloc(sizeof(can_message_t));
	//can_message_t* msg77 = malloc(sizeof(can_message_t));
	//can_message_t receive;
	gui_drawMenu(menu,selected);
	while(1){
		touch_measure(&ls, &rs, &lb, &rb);
		//printf("ls:%4i,rs:%4i,lb:%4i,rb:%4i\n",ls,rs,lb,rb);
		
		//MAP 0-255 to 1- num child menus
		uint8_t mapValue=255/menu->num_childMenus;
		ls=255-ls;
		uint8_t touchSelected=ls/mapValue;
		
		if (touchSelected!=selected && touchSelected>=1){
			selected=touchSelected;
			gui_drawMenu(menu,selected);
		}
		printf("selected: %i\n", selected);
		if (rb){
			if((selected<=menu->childMenus[selected-1]->num_childMenus) && (menu->childMenus[selected-1]->num_childMenus>0)){
				menu=menu->childMenus[selected-1];
				selected=1;
				gui_drawMenu(menu,selected);
			}
		}
		else if(lb){
			if (menu->parent!=NULL){
				menu=menu->parent;
				selected=1;
				gui_drawMenu(menu,selected);
			}
			
		}
/*
		pwm_set(1,255-ls);
		pwm_set(2,rs);
		msg13->id=13;
		msg13->length=4;
		msg13->data[0]=pos.x>>8;
		msg13->data[1]=pos.x;
		msg13->data[2]=pos.y>>8;
		msg13->data[3]=pos.y;
		
		msg77->id=77;
		msg77->length=4;
		msg77->data[0]=255-ls;
		msg77->data[1]=rs;
		msg77->data[2]=lb;
		msg77->data[3]=rb;
		
		printf("sending:  ");
		can_print(*msg13);
		can_messageSend(msg13,MCP_TXB1CTRL);* /
		
		/ *if (!(SPI_PIN & SPI_CS_MCP2515)){
			can_message_t receive = can_dataReceive();
			switch (receive.id){
				case 20: ;
					for (uint8_t i = 0 ;i<8;i++){
						//oled_put(receive->data[i]); or something like this
					}
				case 46:
					//message that contains confidential information
					break;
				default:
					break;	
			}
		}*/
		LED_PORT ^= (1 << LED1);
		gui_update();
	}
}