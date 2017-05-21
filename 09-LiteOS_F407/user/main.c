#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"
#include "los_inspect_entry.h"
#include "los_demo_entry.h"

#include <string.h>

#include "stm32f4xx_hal.h"	
  
  /**
    * @brief  This function is executed in case of error occurrence.
    * @param  None
    * @retval None
    */
  static void Error_Handler(void)
  {
    /* Turn LED2 on */
    //BSP_LED_On(LED2);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET);
    while(1)
    {
    }
  }
  
  /**
    * @brief  System Clock Configuration
    *         The system Clock is configured as follow : 
    *            System Clock source            = PLL (HSI)
    *            SYSCLK(Hz)                     = 100000000
    *            HCLK(Hz)                       = 100000000
    *            AHB Prescaler                  = 1
    *            APB1 Prescaler                 = 2
    *            APB2 Prescaler                 = 1
    *            HSI Frequency(Hz)              = 16000000
    *            PLL_M                          = 16
    *            PLL_N                          = 400
    *            PLL_P                          = 4
    *            PLL_Q                          = 7
    *            VDD(V)                         = 3.3
    *            Main regulator output voltage  = Scale2 mode
    *            Flash Latency(WS)              = 3
    * @param  None
    * @retval None
    */
  static void SystemClock_Config(void)
  {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
  
    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* The voltage scaling allows optimizing the power consumption when the device is 
       clocked below the maximum system frequency, to update the voltage scaling value 
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    
    /* Enable HSI Oscillator and activate PLL with HSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 0x10;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
    
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
      Error_Handler();
    }
  }
extern void LOS_EvbSetup(void);

static UINT32 g_uwboadTaskID;
LITE_OS_SEC_TEXT VOID LOS_BoadExampleTskfunc(VOID)
{
    while (1)
    {
        LOS_EvbLedControl(LOS_LED2, LED_ON);
        LOS_EvbUartWriteStr("Board Test\n");
        LOS_TaskDelay(500);
        LOS_EvbLedControl(LOS_LED2, LED_OFF);
        LOS_TaskDelay(500);
    }
}
void LOS_BoadExampleEntry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_BoadExampleTskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    stTaskInitParam.pcName = "BoardDemo";
    stTaskInitParam.usTaskPrio = 10;
    uwRet = LOS_TaskCreate(&g_uwboadTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
        return;
    }
    return;
}
\
 /*****************************************************************************
  Function    : main
  Description : Main function entry
  Input       : None
  Output      : None
  Return      : None
   *****************************************************************************/
  LITE_OS_SEC_TEXT_INIT
  int main(void)
  {
      UINT32 uwRet;
      /*
          add you hardware init code here
          for example flash, i2c , system clock ....
      */
      HAL_Init();
			
      SystemClock_Config();
  
      /*Init LiteOS kernel */
      uwRet = LOS_KernelInit();
      if (uwRet != LOS_OK) {
          return LOS_NOK;
      }
			
      /* Enable LiteOS system tick interrupt */
      LOS_EnableTick();
			
      /*
          Notice: add your code here
          here you can create task for your function 
          do some hw init that need after systemtick init
       */
			
      LOS_EvbSetup();//init the device on the dev baord
			//Example_Interrupt();
			
			LOS_EvbLedControl(1,0);//led 2 off
			LOS_EvbLedControl(0,0);//led 1 off

			
			
      LOS_Demo_Entry();
      LOS_Inspect_Entry();
      LOS_BoadExampleEntry();

      /* Kernel start to run */
      LOS_Start();
      for (;;);
      /* Replace the dots (...) with your own code. */
  }