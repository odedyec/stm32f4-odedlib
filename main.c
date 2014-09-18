

#include "LED_handler.h"
#include "button_handler.h"
#include "pwm_handler.h"
#include "uart_handler.h"
#include "adc_handler.h"
    
int cnt = 0;
int dc_servo = 0;
int change_servo_dc(int dc)
{
  dc -= 5;
  if(dc < 75)
    return 125;
  return dc;
}
void EXTI0_IRQHandler(void);
void USART1_IRQHandler(void);
void Delay(__IO uint32_t nCount);

int main(void)
{
  int ConvertedValue = 0; //Converted value readed from ADC
  char st[25];int i;
  for (i=0;i<25;st[i++]=0);
  led_init(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  button_init();
  adc_configure();
  pwm_init(5,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
  pwm_init(50,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
  change_dc(500,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
  change_dc(750,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
  init_USART1(9600); // initialize USART1 @ 9600 baud
  flush_string(received_string,MAX_STRLEN);
  USART_puts(USART1, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
  int found=0;
  while (1)
  {
    ConvertedValue = adc_convert()/1024;
    found = search_start_string();
    sprintf(st,"cnt:%d |found:%d|value: %d\r\n",cnt,found,ConvertedValue);
    while(send_flag);
    //USART_puts(USART1, st);
    //Delay(0x3FFFFF);Delay(0x3FFFFF);
    if(cnt >15) cnt = 0;
    set_patterns(ConvertedValue+1);
    /*
    while(cnt == 0)
    {
      led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
      USART_puts(USART1, "wow\r\n");
    }
    change_dc(250,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);
    
    while(cnt == 1)
    {
      led_on(GPIO_Pin_12);Delay(0x3FFFFF); led_on(GPIO_Pin_13);Delay(0x3FFFFF);led_on(GPIO_Pin_14);Delay(0x3FFFFF);led_on(GPIO_Pin_15);Delay(0x3FFFFF);
      led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);Delay(0x3FFFFF);
    }
    cnt = 0;
    change_dc(5,TIM3,GPIOC,GPIO_Pin_7 ,GPIO_PinSource7);*/
  }
}


void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
    dc_servo = change_servo_dc(dc_servo);
    change_dc(dc_servo,TIM3,GPIOC,GPIO_Pin_6 ,GPIO_PinSource6);
    cnt = 0;   
  }
}
void USART1_IRQHandler(void){

	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
                cnt += 1;
                
		static uint8_t cont = 0; // this counter is used to determine the string length
                if(flushed) cont = 0;
                flushed = 0;
		char t = USART1->DR; // the character from the USART1 data register is saved in t

		/* check if the received character is not the LF character (used to determine end of string)
		 * or the if the maximum string length has been been reached
		 */
		if( (t != 'n') && (cont < MAX_STRLEN) ){
			received_string[cont] = t;
			cont++;
		}
		else{ // otherwise reset the character counter and print the received string
			cont = 0;
                        //while(send_flag);
			//USART_puts(USART1, received_string);
		}
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

