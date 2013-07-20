ChibiOS-DCMotorDriver
=====================

ChibiOS/DCMotor is a small library compatible STM32 which allows it to easily interface standard DC motors to L293D (Push-Pull Four Channel Drivers with Diodes) to ChibiOS/RT easily.

Tested with ST L293D and STM32VL discovery.

### License ###

This library stands under the GPLv3 license. You can use, modify and share this code in any situations. The only restriction is that you always have to keep the original license header.

### HowTo use ###

To use this small library, just add the dc_motor.c and dc_motor.h files to your project.

First, you have to create an instance of the DCMotor struct. The DCMotor contains the following informations:


        typedef struct DCMotor_t {
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

You should know that GPIO_PIN is declared as following :

        typedef struct GPIO_PIN_t{
                ioportid_t port;
                ioportmask_t pin;
        } GPIO_PIN;

This instance will be passed to every function which controlls the dcmotor.
