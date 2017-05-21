#ifndef _LOS_BSP_LED_H
#define _LOS_BSP_LED_H

#define LED_ON      (1)
#define LED_OFF     (0)
#define LOS_LED1    (0)
#define LOS_LED2    (1)
#define LOS_LED3    (2)
#define LOS_LED4    (3)
#define LOS_LEDX    (4)
#define LED1_PIN  	GPIO_PIN_9
#define LED1_PORT  	GPIOF
#define LED2_PIN  	GPIO_PIN_10
#define LED2_PORT  	GPIOF


void LOS_EvbLedInit(void);
void LOS_EvbLedControl(int index, int cmd);
#endif
