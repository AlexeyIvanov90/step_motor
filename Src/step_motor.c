/*
 * step_motor.c
 *
 *  Created on: Sep 14, 2023
 *      Author: Alexey
 */

#include "step_motor.h"


static uint16_t arr_speed_nema_17[100]=
	{1000,869,769,689,625,571,526,487,454,425,
	400,377,357,338,322,307,294,281,270,259,
	250,240,232,224,217,210,204,198,192,186,
	181,176,172,168,163,160,156,152,149,145,
	142,139,136,134,131,129,126,124,122,120,
	118,116,114,112,110,108,106,104,102,100,
	98,96,94,92,90,88,87,86,85,84,
	83,82,81,80,79,78,77,76,75,74,
	73,72,72,71,71,70,70,69,69,68,
	68,67,67,66,66,65,65,64,64,63};


void motor_init(motor* mt, TIM_HandleTypeDef* timer, uint32_t channel){
	mt->timer = timer;
	mt->channel = channel;
	motor_stop(mt);
	HAL_TIM_PWM_Start_IT(timer, channel);
}


void nema_17_init(motor* mt, TIM_HandleTypeDef* timer, uint32_t channel){
	motor_init(mt, timer, channel);

	mt->acceleration = 10;
	mt->current_speed = 0;
	mt->arr_speed = arr_speed_nema_17;
}

static int new_speed = 0;
static int count_it = 0;

void change_speed(motor* mt, uint32_t speed){
	while(1){
		for(int i = 0; i < mt->acceleration; i++)
			HAL_Delay(10);

		if(speed==mt->current_speed)
			break;

		if(speed > mt->current_speed)
			mt->current_speed++;
		else
			mt->current_speed--;

		__HAL_TIM_SET_AUTORELOAD(mt->timer, mt->arr_speed[mt->current_speed]);
	}
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM4) {
    	if(new_speed)
    		count_it++;
    }
}


void motor_stop(motor* mt){
	  __HAL_TIM_SET_COMPARE(mt->timer, mt->channel , 0);
}


void motor_move(motor* mt){
	  __HAL_TIM_SET_COMPARE(mt->timer, mt->channel , 1);
}


