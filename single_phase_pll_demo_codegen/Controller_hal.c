/*
 * Hardware configuration file for: STM32G4x
 * Generated with                 : PLECS 4.9.5
 * Generated on                   : Sat Nov 22 19:39:07 2025
 */

/* HAL Includes */
#include "plx_hal.h"
#include "FreeRTOSConfig.h"
#include "plx_dispatcher.h"
#include "plx_gpio.h"
#include "pil.h"
#include "Controller.h"
#include "plx_adc.h"
#include "plx_dac.h"
#include "plx_timer.h"

/* HAL Declarations */
__STATIC_INLINE void SystemClock_Config(void)
{
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {
      0
   };
   RCC_OscInitTypeDef RCC_OscInitStruct = {
      0
   };
   RCC_PeriphCLKInitTypeDef PeriphClkInit = {
      0
   };
   // enable voltage range 1 boost mode for frequency above 150 Mhz
   __HAL_RCC_PWR_CLK_ENABLE();
   HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
   __HAL_RCC_PWR_CLK_DISABLE();
   // activate PLL with HSI as source
   RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
   RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLM            = RCC_PLLM_DIV4;
   RCC_OscInitStruct.PLL.PLLN            = 85;
   RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
   RCC_OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
   if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      PLX_ASSERT(0);
   }

   // select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
   RCC_ClkInitStruct.ClockType           =
      (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
       RCC_CLOCKTYPE_PCLK1 |
       RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource        = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider       = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider      = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider      = RCC_HCLK_DIV1;
   if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
   {
      PLX_ASSERT(0);
   }

   // initialize the peripherals clocks
   PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC12|
                                        RCC_PERIPHCLK_ADC345|
                                        RCC_PERIPHCLK_FDCAN;
   PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_PLL;
   PeriphClkInit.Adc345ClockSelection = RCC_ADC345CLKSOURCE_PLL;
   PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
   PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
   {
      PLX_ASSERT(0);
   }

}

PIL_Obj_t PilObj;
PIL_Handle_t PilHandle = 0;
const uint16_t RegAdcChannelLookup[1][1] = {
   {4}
};
const uint16_t RegAdcLookup[1] = {
   0
};
extern PLX_ADC_Handle_t AdcHandles[];
float PLXHAL_ADC_getRegIn(uint16_t aHandle, uint16_t aChannel)
{
   return PLX_ADC_getIn(AdcHandles[RegAdcLookup[aHandle]],
                        RegAdcChannelLookup[aHandle][aChannel]);
}
const uint16_t DacLookup[1] = {
   0
};
extern PLX_DAC_Handle_t DacHandles[];
void PLXHAL_DAC_setChannelOut(uint16_t aHandle, uint16_t aChannel,
                              float aValue, float aMinValue, float aMaxValue)
{
   if(aValue < aMinValue)
   {
      aValue = aMinValue;
   }
   else if(aValue > aMaxValue)
   {
      aValue = aMaxValue;
   }
   PLX_DAC_setOut(DacHandles[DacLookup[aHandle]], aChannel, aValue);
}

PLX_ADC_Handle_t AdcHandles[1];
PLX_ADC_Obj_t AdcObj[1];
const uint16_t InjAdcChannelLookup[1][0] = {
   {}
};
float PLXHAL_ADC_getInjIn(uint16_t aHandle, uint16_t aChannel)
{
   return PLX_ADC_getIn(AdcHandles[aHandle],
                        InjAdcChannelLookup[aHandle][aChannel]);
}
PLX_DAC_Handle_t DacHandles[1];
PLX_DAC_Obj_t DacObj[1];
void PLXHAL_DAC_setOut(uint16_t aHandle, uint16_t aChannel, float aValue)
{
   PLX_DAC_setOut(DacHandles[aHandle], aChannel, aValue);
}
PLX_TIM_Handle_t TimerHandles[1];
PLX_TIM_Obj_t TimerObj[1];
void TIM3_IRQHandler(void)
{
   if (PLX_TIM_processInt(TimerHandles[0]))
   {
      DISPR_dispatch();
   }
}


bool Controller_checkOverrun()
{
   return HAL_NVIC_GetPendingIRQ(TIM3_IRQn);
}

extern PIL_Handle_t PilHandle;
DISPR_TaskObj_t TaskObj[1];
extern void Controller_step();
extern void Controller_enableTasksInterrupt();
extern void Controller_syncTimers();
extern bool Controller_checkOverrun();
static bool Tasks(uint16_t aTaskId)
{
   bool overrun = false;
   Controller_step();

   overrun = Controller_checkOverrun();
   return overrun;
}



/* Interrupt Enable Code */
void Controller_enableTasksInterrupt(void)
{
   HAL_NVIC_SetPriority(TIM3_IRQn,
                        configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY, 0);
   HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

/* Timer Synchronization Code */
void Controller_syncTimers(void)
{
   LL_TIM_EnableCounter(TIM3);
}

/* Background tasks */
void Controller_background(void)
{

}
/* HAL Initialization Code */
static bool HalInitialized = false;
void Controller_initHal()
{
   if(HalInitialized == true)
   {
      return;
   }
   HalInitialized = true;
   // Pre init code
   SystemClock_Config();
   SystemCoreClockUpdate();

   PLX_ASSERT(SystemCoreClock == 170000000L);
   PLX_ASSERT( HAL_RCC_GetPCLK1Freq() == 170000000L);

   {
      // early system configuration
      PLX_GPIO_sinit();
   }
   {
      PLX_ADC_sinit(3.300000);
      int i;
      for(i=0; i < 1; i++)
      {
         AdcHandles[i] = PLX_ADC_init(&AdcObj[i], sizeof(AdcObj[i]));
      }
   }

   {

      PLX_ADC_setup(AdcHandles[0], PLX_ADC1);

      LL_ADC_InitTypeDef adcInitStruct = {
         0
      };
      LL_ADC_REG_InitTypeDef adcRegInitStruct = {
         0
      };
      LL_ADC_INJ_InitTypeDef adcInjInitStruct = {
         0
      };

      adcInitStruct.Resolution = LL_ADC_RESOLUTION_12B;
      adcInitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
      adcInitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
      LL_ADC_Init(ADC1, &adcInitStruct);

      adcRegInitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
      adcRegInitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
      adcRegInitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
      adcRegInitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
      adcRegInitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
      adcRegInitStruct.Overrun = LL_ADC_REG_OVR_DATA_OVERWRITTEN;
      LL_ADC_REG_Init(ADC1, &adcRegInitStruct);

      LL_ADC_SetGainCompensation(ADC1, 0);

      LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE); // LL_ADC_OVS_GRP_INJECTED

      adcInjInitStruct.TriggerSource = LL_ADC_INJ_TRIG_SOFTWARE;
      adcInjInitStruct.SequencerLength = LL_ADC_INJ_SEQ_SCAN_DISABLE;
      adcInjInitStruct.SequencerDiscont = LL_ADC_INJ_SEQ_DISCONT_DISABLE;
      adcInjInitStruct.TrigAuto = LL_ADC_INJ_TRIG_INDEPENDENT;
      LL_ADC_INJ_Init(ADC1, &adcInjInitStruct);
      LL_ADC_INJ_SetQueueMode(ADC1, LL_ADC_INJ_QUEUE_DISABLE);

      LL_ADC_DisableDeepPowerDown(ADC1);
      LL_ADC_EnableInternalRegulator(ADC1);
      {
         uint32_t wait_loop_index;
         wait_loop_index =
            ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US *
              (SystemCoreClock / (100000 * 2))) / 10);
         while(wait_loop_index != 0)
         {
            wait_loop_index--;
         }
      }

      {
         LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1,
                                      LL_ADC_CHANNEL_1);
         LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1,
                                       LL_ADC_SAMPLINGTIME_2CYCLES_5);
         LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_1,
                                     LL_ADC_SINGLE_ENDED);

         PLX_ADC_addChannel(AdcHandles[0], 1.000000, 0.000000);

      }
   }
   {
      PLX_DAC_sinit(3.300000);
      int i;
      for(i=0; i < 1; i++)
      {
         DacHandles[i] = PLX_DAC_init(&DacObj[i], sizeof(DacObj[i]));
      }
   }

   {

      PLX_DAC_setup(DacHandles[0], PLX_DAC1);

      {

         LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_1,
                                LL_DAC_SIGNED_FORMAT_DISABLE);

         LL_DAC_InitTypeDef initStruct = {
            0
         };
         initStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
         initStruct.TriggerSource2 = LL_DAC_TRIG_SOFTWARE;

         initStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
         initStruct.OutputConnection = LL_DAC_OUTPUT_CONNECT_GPIO;
         initStruct.OutputMode = LL_DAC_OUTPUT_MODE_NORMAL;

         LL_DAC_Init(DAC1, LL_DAC_CHANNEL_1, &initStruct);
         LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);
         LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_1);

         PLX_DAC_configureChannel(DacHandles[0], 0, PLX_DAC_DC, 0.500000,
                                  0.000000);

      }

      PLX_DAC_activate(DacHandles[0]);

   }

   {
      PLX_TIM_sinit();
      int i;
      for(i=0; i < 1; i++)
      {
         TimerHandles[i] = PLX_TIM_init(&TimerObj[i], sizeof(TimerObj[i]));
      }
   }

   {

      LL_TIM_InitTypeDef initStruct = {
         0
      };
      initStruct.Prescaler =  4-1;
      initStruct.Autoreload = 42500-1;
      initStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
      initStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
      initStruct.RepetitionCounter = 0;

      PLX_TIM_setup(TimerHandles[0], PLX_TIM3, &initStruct, 0, 1000.000000);

      TIM_TypeDef* handle = PLX_TIM_getStmLLHandle(TimerHandles[0]);
      LL_TIM_SetSlaveMode(handle, LL_TIM_SLAVEMODE_DISABLED);
      LL_TIM_SetTriggerInput(handle, LL_TIM_TS_ITR0);
      LL_TIM_SetTriggerOutput(handle, LL_TIM_TRGO_UPDATE);
      LL_TIM_SetTriggerOutput2(handle, LL_TIM_TRGO2_RESET);
      LL_TIM_DisableMasterSlaveMode(handle);

   }
   DISPR_sinit();
   DISPR_configure((uint32_t)(170000), PilHandle, &TaskObj[0],
                   sizeof(TaskObj)/sizeof(DISPR_TaskObj_t));
   DISPR_registerIdleTask(&Controller_background);
   DISPR_registerSyncCallback(&Controller_syncTimers);
   DISPR_registerEnableInterrupt(&Controller_enableTasksInterrupt);
   DISPR_setPowerupDelay(1);
   {
      // Task 0 at 1.000000e+03 Hz
      DISPR_registerTask(0, &Tasks, 170000L);
   }

   // Post init code (for modules that depend on other modules)

   {
      // late system configuration
      {
         LL_GPIO_InitTypeDef gpioInit = {
            0
         };
         gpioInit.Pin = LL_GPIO_PIN_0;
         gpioInit.Mode = LL_GPIO_MODE_ANALOG;
         gpioInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
         gpioInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
         gpioInit.Pull = LL_GPIO_PULL_NO;
         gpioInit.Alternate = LL_GPIO_AF_0;
         PLX_GPIO_setGpioConfig(PLX_PORTA, &gpioInit);
      }

      {
         LL_GPIO_InitTypeDef gpioInit = {
            0
         };
         gpioInit.Pin = LL_GPIO_PIN_4;
         gpioInit.Mode = LL_GPIO_MODE_ANALOG;
         gpioInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
         gpioInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
         gpioInit.Pull = LL_GPIO_PULL_NO;
         gpioInit.Alternate = LL_GPIO_AF_0;
         PLX_GPIO_setGpioConfig(PLX_PORTA, &gpioInit);
      }

   }
   PLX_ADC_start(AdcHandles[0]);

   PLX_TIM_start(TimerHandles[0], 0);
}
