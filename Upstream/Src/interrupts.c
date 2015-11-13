/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @date    03/02/2015 20:27:00
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  *
  * Modifications by Robert Fisk
  */

/* Includes ------------------------------------------------------------------*/
#include <interrupts.h>
#include <upstream_spi.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "board_config.h"
#include "led.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/* External variables --------------------------------------------------------*/

extern PCD_HandleTypeDef    hpcd_USB_OTG_FS;
extern DMA_HandleTypeDef    spiTxDmaHandle;
extern DMA_HandleTypeDef    spiRxDmaHandle;


/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

void SysTick_Handler(void)
{
  HAL_IncTick();
  LED_DoBlinks();
}

/////////////////////////
//All interrupts in this section must be at the same priority.
//They interact with each other, and calls are not thread-safe
//when different interrupt priorities are used.
/////////////////////////
void OTG_FS_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

void DMA2_Stream2_IRQHandler(void)
{
//    INT_ACTIVE_ON;
    HAL_DMA_IRQHandler(&spiRxDmaHandle);
//    INT_ACTIVE_OFF;
}

void DMA2_Stream3_IRQHandler(void)
{
//    INT_ACTIVE_ON;
    HAL_DMA_IRQHandler(&spiTxDmaHandle);
//    INT_ACTIVE_OFF;
}

void EXTI3_IRQHandler(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(DOWNSTREAM_TX_OK_PIN);
    Upstream_TxOkInterrupt();
}
/////////////////////////
/////////////////////////



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
