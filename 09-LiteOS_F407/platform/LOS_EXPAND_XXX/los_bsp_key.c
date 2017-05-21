#include "los_bsp_key.h"

/******************************************************************************
    here include some special hearder file you need
******************************************************************************/
#include "stm32f4xx_hal.h"
#include "los_demo_debug.h"



/*****************************************************************************
 Function    : LOS_EvbKeyInit
 Description : Init GIOP Key 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbKeyInit(void)
{
  //add you code here.
	BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
		
  return ;
}
/** COPY FROM stm32f411re_nucleo
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_KEY
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	USER_BUTTON1_GPIO_CLK_ENABLE();
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = USER_BUTTON1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(USER_BUTTON1_GPIO_PORT, &GPIO_InitStruct);
  }else if(ButtonMode == BUTTON_MODE_EXTI){
  
	//config exti
	GPIO_InitStruct.Pin = USER_BUTTON1_PIN;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
  HAL_GPIO_Init(USER_BUTTON1_GPIO_PORT, &GPIO_InitStruct);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(USER_BUTTON1_EXTI_IRQn, 0x02, 0x00);
  HAL_NVIC_EnableIRQ(USER_BUTTON1_EXTI_IRQn);
  }
}

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = 0xFFFFFFFF;
    
    //add you code here.
     if(KeyNum > LOS_KEY_PRESS)
    {
        return LOS_GPIO_ERR;
    }
    
    KeyVal = HAL_GPIO_ReadPin(USER_BUTTON1_GPIO_PORT, USER_BUTTON1_PIN);
    return KeyVal;
}

/*****************************************************************************
 Function    : EXTIxxx_IRQHandler
 Description : EXT xxx IRQ Handler detail,change the function name 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
//void EXTI0_IRQHandler(void)
//{
    //add you code here.
	//HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
  //HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  //{
  /* EXTI line interrupt detected */
  //if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
  //{
  //  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
  //  HAL_GPIO_EXTI_Callback(GPIO_PIN_0);
  //}
//}

    
//    return;
//}
/* USER CODE BEGIN 4 */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
	//switch(GPIO_Pin)
	//{
		//case GPIO_PIN_0:
		//	dprintf("\r\nEXTI test \r\n");
	//		GPIOF->BSRR = ((uint16_t)0x0400);
		//break;
		//case GPIO_PIN_13:LED1_Toggle();break;
		//case GPIO_PIN_14:LED2_Toggle();break;
		//case GPIO_PIN_15:LED3_Toggle();break;
		//default:break;
	//}
//}
/* USER CODE END 4 */



