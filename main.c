

#include "LED_handler.h"
#include "button_handler.h"
#include "pwm_handler.h"

void Delay(__IO uint32_t nCount);
    
int cnt = 0;
int dc_servo = 0;
int change_servo_dc(int dc)
{
  dc -= 5;
  if(dc < 75)
    return 125;
  return dc;
}
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
    dc_servo = change_servo_dc(dc_servo);
    change_dc(dc_servo,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
    cnt += 1;   
  }
}
int main(void)
{
  
  led_init(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  button_init();
  pwm_init(5,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
  pwm_init(50,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
  change_dc(500,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
  change_dc(750,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
  while (1)
  {
    
    while(cnt == 0)
    {
      led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
    }
    change_dc(250,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
    
    while(cnt == 1)
    {
      led_on(GPIO_Pin_12);Delay(0x3FFFFF); led_on(GPIO_Pin_13);Delay(0x3FFFFF);led_on(GPIO_Pin_14);Delay(0x3FFFFF);led_on(GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
    }
    cnt = 0;
    change_dc(5,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
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

