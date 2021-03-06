/*
 * game.h
 *
 * Created: 19.11.2015 21:48:35
 *  Author: laurittr
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>
#include "can.h"

void game_start(void);
void game_end(can_message_t endMsg);
void highscoreSwap(uint16_t* a, uint16_t* b);
void game_sram(void);
void game_startAT(void);
void game_highscore(void);
void game_AT(void);


#endif /* GAME_H_ */