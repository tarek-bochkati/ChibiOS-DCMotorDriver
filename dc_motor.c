/*
 * ChibiOS/DCMotor is a small library to easily interface L293D
 * in order control DC Motors with ChibiOS/RT.
 *
 * This library is compatible STM32
 *
 * Licensed : GPLv3
 *
 * Author: Tarek Bouchkati   <tarekbouchkati@gmail.com>
 */

#include "hal.h"
#include "ch.h"
#include "dc_motor.h"


static PWMConfig pwm_cfg = { //model to copy on each initialization
	// 1MHz PWM clock frequency
	1000000,
	// PWM period 10 milliseconds
	10000,
	// no callback
	NULL,
	// PWM channels array
	{    // All disabled
	{PWM_OUTPUT_DISABLED, NULL},    // Channel 0
	{PWM_OUTPUT_DISABLED, NULL},    // Channel 1
	{PWM_OUTPUT_DISABLED, NULL},    // Channel 2
	{PWM_OUTPUT_DISABLED, NULL}     // Channel 3
	}, // channel configuration set dynamically in DCMotorInit()
	0
};

static int getWidthFromSpeedPercent(int speedPercent) {
	int p = speedPercent > 100 ? 100 : (speedPercent < 0 ? 0 : speedPercent);
	return pwm_cfg.period * p / 100;
}

/*===========================================================================*/
/**
 *  MOTOR 1 Functions
 */
/*===========================================================================*/

void DCMotorConfig(DCMotor *dcmotor) {
	//PWMConfig pwm_cfg = _pwmcfg_model_;
	/* create the channel configuration */
	PWMChannelConfig chcfg = {PWM_OUTPUT_ACTIVE_HIGH, NULL};
	pwm_cfg.channels[dcmotor->pwm_channel] = chcfg;
	/* configure PAL */
	palSetPadMode(dcmotor->IN1.port, dcmotor->IN1.pin, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(dcmotor->IN2.port, dcmotor->IN2.pin, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(dcmotor->EN.port, dcmotor->EN.pin, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	
	/* start the PWM unit */
	pwmStart(dcmotor->pwm_driver, &pwm_cfg);
}


void DCMotorStop(DCMotor *dcmotor) {
	palClearPad(dcmotor->IN1.port, dcmotor->IN1.pin);
	palClearPad(dcmotor->IN2.port, dcmotor->IN2.pin);
	// set EN PWM HI part as FULL
	pwmEnableChannel( dcmotor->pwm_driver,
	                  dcmotor->pwm_channel,
	                  PWM_PERCENTAGE_TO_WIDTH(dcmotor->pwm_driver,
	                  getWidthFromSpeedPercent(100))
	                 );
}


void DCMotorFree(DCMotor *dcmotor) {
	palClearPad(dcmotor->IN1.port, dcmotor->IN1.pin);
	palClearPad(dcmotor->IN2.port, dcmotor->IN2.pin);
	pwmEnableChannel( dcmotor->pwm_driver,
	                  dcmotor->pwm_channel,
	                  PWM_PERCENTAGE_TO_WIDTH(dcmotor->pwm_driver, 0)
	                 );
}


void DCMotorForward(DCMotor *dcmotor, int speedPercent) {
	palClearPad(dcmotor->IN1.port, dcmotor->IN1.pin);
	palSetPad(dcmotor->IN2.port, dcmotor->IN2.pin);
	// set speed
	pwmEnableChannel( dcmotor->pwm_driver,
	                  dcmotor->pwm_channel,
	                  PWM_PERCENTAGE_TO_WIDTH(dcmotor->pwm_driver,
	                  getWidthFromSpeedPercent(speedPercent))
	                 );
}


void DCMotorBackward(DCMotor *dcmotor, int speedPercent) {
	palSetPad(dcmotor->IN1.port, dcmotor->IN1.pin);
	palClearPad(dcmotor->IN2.port, dcmotor->IN2.pin);
	// set speed
	pwmEnableChannel( dcmotor->pwm_driver,
	                  dcmotor->pwm_channel,
	                  PWM_PERCENTAGE_TO_WIDTH( dcmotor->pwm_driver,
	                                           getWidthFromSpeedPercent(speedPercent)
	                                          )
	                 );
}
