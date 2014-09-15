#include "stm32f4_discovery.h"

void pwm_init(uint16_t freq,TIM_TypeDef *tim,GPIO_TypeDef *port,uint16_t pin,uint8_t pin_source)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  uint16_t PrescalerValue = 0;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM3 clock enable */
  int tim_af;
  if (tim == TIM2)  {RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);tim_af = GPIO_AF_TIM2;}
  if (tim == TIM3)  {RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);tim_af = GPIO_AF_TIM3;}
  if (tim == TIM4)  {RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);tim_af = GPIO_AF_TIM4;}

  /* GPIOC and GPIOB clock enable */
  uint32_t rcc_port;
  if (port == GPIOA) rcc_port = RCC_AHB1Periph_GPIOA;
  if (port == GPIOB) rcc_port = RCC_AHB1Periph_GPIOB;
  if (port == GPIOC) rcc_port = RCC_AHB1Periph_GPIOC;
  if (port == GPIOD) rcc_port = RCC_AHB1Periph_GPIOD;
  RCC_AHB1PeriphClockCmd(rcc_port, ENABLE);
  
  /* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
  GPIO_InitStructure.GPIO_Pin =  pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(port, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */ 
  GPIO_PinAFConfig(port, pin_source, tim_af); 

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / (1000*3*freq)) ;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 1000;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  if (pin == GPIO_Pin_6)
  {
    TIM_OC1Init(tim, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);
  }
  if (pin == GPIO_Pin_7)
  {
    TIM_OC2Init(tim, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  }

  TIM_ARRPreloadConfig(tim, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(tim, ENABLE);
}
void change_dc(int dc,TIM_TypeDef *tim,GPIO_TypeDef *port,uint16_t pin,uint8_t pin_source)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  TIM_Cmd(tim, DISABLE);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = dc;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  if (pin == GPIO_Pin_6)
  {
    TIM_OC1Init(tim, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);
  }
  if (pin == GPIO_Pin_7)
  {
    TIM_OC2Init(tim, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  }
  TIM_Cmd(tim, ENABLE);

}