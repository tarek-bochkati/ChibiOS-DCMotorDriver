/*
 * ChibiOS/DCMotor is a small library to easily interface L293D
 * in order control DC Motors with ChibiOS/RT.
 *
 * This library is compatible STM32
 *
 * BSD licensed
 *
 * Author: Tarek Bouchkati   <tarekbouchkati@gmail.com>
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "hal.h"
#include "ch.h"

//  GPIO_PIN structure definition
typedef struct GPIO_PIN_t{
	ioportid_t port;
	ioportmask_t pin;
} GPIO_PIN;

typedef struct DCMotor_t{
	// The GPIO pin on which the DCMotor IN1 is connected
	GPIO_PIN IN1;
	// The GPIO pin on which the DCMotor IN2 is connected
	GPIO_PIN IN2;
	// The GPIO pin on which the DCMotor EN is connected
	GPIO_PIN EN;
	// The PWM driver to use with EN
	PWMDriver *pwm_driver;
	// The PWM channel to use with EN
	pwmchannel_t pwm_channel;
} DCMotor;


/*===========================================================================*/
/**
 *  DCMotor Functions
 */
/*===========================================================================*/

//init
void DCMotorConfig(DCMotor *dcmotor);
//commands
void DCMotorStop(DCMotor *dcmotor);
void DCMotorFree(DCMotor *dcmotor);
void DCMotorForward(DCMotor *dcmotor, int speedPercent);
void DCMotorBackward(DCMotor *dcmotor, int speedPercent);

#endif // DC_MOTOR_H
