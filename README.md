# LitOS_stm32f407
- 更新 5/22
	- los_bsp_adapter
	- los_bsp_led
	- los_bsp_uart
	- los_bsp_key
	- main
	- EXTI 尚未配置
	- LwIP尚未移植

## 使用說明
專案結構:

|Name|Description|
|--|--|
|kernel|kernel file |
|cmsis|LiteOS provides the cmsis interface|
|config|config file|
|cpu|init Cortex-m4|
|example|This directory is stored in the kernel function test with the relevant use case code|
|user|main|
|project|my project|
|platform|bsp code|

## 測試API
__main.c__
````
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
```

## 參考資源
1. [LiteOS kernel](https://github.com/LITEOS/LiteOS_Kernel)
2. [HuaweiLiteOSKernelDevGuide](https://github.com/LITEOS/LiteOS_Kernel/blob/master/doc/HuaweiLiteOSKernelDevGuide.md)
3. [Huawei LiteOS端云方案Demo程序--资源下载](http://developer.huawei.com/ict/forum/forum.php?mod=viewthread&tid=1944)
4. [Hackathon深圳站—赛前资源获取](http://mp.weixin.qq.com/s/7gG--6mBXYKnQs-65CPD3A)
