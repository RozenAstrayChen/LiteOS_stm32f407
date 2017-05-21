#ifndef _LOS_BSP_KEY_H
#define _LOS_BSP_KEY_H

#define LOS_KEY_PRESS   0

#define USER_KEY        0

#define LOS_GPIO_ERR    0xFF;
/**
	* @brief Button Type
	*/
	typedef enum 
{  
  BUTTON_USER = 0,
  /* Alias */
  BUTTON_KEY  = BUTTON_USER
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;


/**
  * @brief Key push-button
  */
//KEY1
#define USER_BUTTON1_PIN                         GPIO_PIN_0
#define USER_BUTTON1_GPIO_PORT                   GPIOA
#define USER_BUTTON1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_BUTTON1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE() 
#define USER_BUTTON1_EXTI_LINE                   GPIO_PIN_0
#define USER_BUTTON1_EXTI_IRQn                   EXTI0_IRQn
//KEY2
#define USER_BUTTON2_PIN                         GPIO_PIN_4
#define USER_BUTTON2_GPIO_PORT                   GPIOE
#define USER_BUTTON2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOE_CLK_ENABLE()
#define USER_BUTTON2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOE_CLK_DISABLE() 
#define USER_BUTTON2_EXTI_LINE                   GPIO_PIN_4
#define USER_BUTTON2_EXTI_IRQn                   EXTI4_IRQn

extern void LOS_EvbKeyInit(void);
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void EXTI0_IRQHandler(void);
unsigned int LOS_EvbGetKeyVal(int KeyNum);

#endif

