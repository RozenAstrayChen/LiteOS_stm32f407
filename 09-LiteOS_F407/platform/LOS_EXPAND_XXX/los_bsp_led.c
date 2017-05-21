#include "los_bsp_led.h"
#include "stm32f4xx_hal.h"

/******************************************************************************
    here include some special hearder file you need
******************************************************************************/



/*****************************************************************************
 Function    : LOS_EvbLedInit
 Description : Init LED device
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedInit(void)
{
    //add you code here.
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN;
		__HAL_RCC_GPIOF_CLK_ENABLE();
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);
  
		HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET); 
	
    return ;
}

/*************************************************************************************************
 *  Function    £ºLOS_EvbLedControl
 *  Discription : Led control function
 *  Input       : (1) index Led's index                                                                  *
 *                (2) cmd   Led on or off  
 *  Output      : None
 *  Return      : None                                                                                *
 *                                                                                 *
**************************************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
    switch (index)
    {
        case LOS_LED1:
        {
            if (cmd == LED_ON)
            {
                //add you code here.
                        /*led1 on */
							HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_SET);
							
            }
            else
            {
                //add you code here.
                        /*led1 off */
							HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
            }
            break;
        }
        case LOS_LED2:
        {
            if (cmd == LED_ON)
            {
                //add you code here.
                        /*led2 on */
							HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_SET);
            }
            else
            {
                //add you code here.
                        /*led2 off */
							HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_RESET);

            }
            break;
        }
        case LOS_LED3:
        {
            if (cmd == LED_ON)
            {
                //add you code here.
                        /*led3 on */
            }
            else
            {
                //add you code here.
                        /*led3 off */
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}


