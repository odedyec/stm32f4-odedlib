

#include "LED_handler.h"
#include "button_handler.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
    
int cnt=0;    
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
    cnt += 1;
 
   
  }
}
    
    
int main(void)
{
  
  led_init(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  button_init();
  while (1)
  {
    while(cnt == 0)
    {
      led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
    }
    while(cnt == 1)
    {
      led_on(GPIO_Pin_12);Delay(0x3FFFFF); led_on(GPIO_Pin_13);Delay(0x3FFFFF);led_on(GPIO_Pin_14);Delay(0x3FFFFF);led_on(GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
    }
    cnt = 0;
  }
}

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

