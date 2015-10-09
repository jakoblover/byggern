/*
 * can.h
 *
 * Created: 02.10.2015 12:00:15
 *  Author: shahrukk
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>

typedef struct can_message_t can_message_t;
struct can_message_t{
	uint16_t id; //16bit enough for standard
	uint8_t length; //4bit
	uint8_t data[8];
};

void can_init(uint8_t operationMode);
void can_messageSend(can_message_t* msg,uint8_t bufferSelect);
//can_error();
//uint8_t can_transmitComplete();
can_message_t can_dataReceive(uint8_t bufferSelect, can_message_t *recieve);
//can_intVect();



#endif /* CAN_H_ */