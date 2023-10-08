/*
 * step_motor.h
 *
 *  Created on: Sep 14, 2023
 *      Author: Alexey
 */
#include "stm32f4xx_hal.h"

#ifndef INC_STEP_MOTOR_H_
#define INC_STEP_MOTOR_H_

typedef struct {
	TIM_HandleTypeDef* timer;//номер таймера
	uint32_t channel;//канал таймера
	uint16_t current_speed;//текущая скорость
	uint16_t acceleration;//скорость изменения
	uint16_t* arr_speed;//массив скоростей
}motor;

void nema_17_init(motor* mt, TIM_HandleTypeDef* timer, uint32_t channel);
void change_speed(motor* mt, uint32_t speed);
void motor_stop(motor* mt);
void motor_start(motor* mt);
void motor_move(motor* mt, uint64_t rotation, uint8_t speed);
#endif /* INC_STEP_MOTOR_H_ */
