/*
 * ChibiOS/DCMotor is a small library to easily interface L293D
 * in order control DC Motors with ChibiOS/RT.
 *
 * This library is compatible STM32
 * 
 * File : example.c
 * Contain : use of ChibiOS/DCMotor to control a simple vehicle
 *
 * BSD licensed
 *
 * Author: Tarek Bouchkati   <tarekbouchkati@gmail.com>
 */
 
#include "ch.h"
#include "hal.h"
#include "dc_motor.h"



static DCMotor rightMotor = {
	{GPIOA, 4},   // Right motor IN1 : PA4
	{GPIOA, 5},   // Right motor IN2 : PA5
	{GPIOA, 2},   // Right motor EN  : PA2
	&PWMD2,       // Right motor EN PWM Driver : TIM2
	2             // Right motor EN PWM Channel : CH3
}
static DCMotor leftMotor = {
	{GPIOA, 6},   // Left motor IN1 : PA6
	{GPIOA, 7},   // Left motor IN2 : PA7
	{GPIOA, 3},   // Left motor EN  : PA3
	&PWMD2,       // Left motor EN PWM Driver : TIM2
	3             // Left motor EN PWM Channel : CH4
};



void main(void){
	
	halInit();
	chSysInit();  
	
	// dcmotors config
	DCMotorConfig(&rightMotor);
	DCMotorConfig(&leftMotor);
	// end config
	
	
	// vehicle stop
	DCMotorStop(&rightMotor);
	DCMotorStop(&leftMotor);
	chThdSleepMilliseconds(1000);

	// vehicle forward
	DCMotorForward(&rightMotor, 100);
	DCMotorForward(&leftMotor, 100);
	chThdSleepMilliseconds(1000);
	
	// vehicle free
	DCMotorFree(&rightMotor);
	DCMotorFree(&leftMotor);
	chThdSleepMilliseconds(1000);
	
	// vehicle backward
	DCMotorBackward(&rightMotor, speedPercent);
	DCMotorBackward(&leftMotor, speedPercent);
	chThdSleepMilliseconds(1000);
	
	// vehicle tirn right
	DCMotorStop(&rightMotor);
	DCMotorForward(&leftMotor, speedPercent);
	chThdSleepMilliseconds(1000);
	
	//vehicle turn left
	DCMotorForward(&rightMotor, speedPercent);
	chThdSleepMilliseconds(1000);
	DCMotorStop(&leftMotor);
	
	// vehicle spin right
	DCMotorBackward(&rightMotor, speedPercent);
	DCMotorForward(&leftMotor, speedPercent);
	chThdSleepMilliseconds(1000);
	
	// vehicle spin left
	DCMotorForward(&rightMotor, speedPercent);
	DCMotorBackward(&leftMotor, speedPercent);
	chThdSleepMilliseconds(1000);
	
	// vehicle stop
	DCMotorStop(&rightMotor);
	DCMotorStop(&leftMotor);
	
	while(TRUE);
}
