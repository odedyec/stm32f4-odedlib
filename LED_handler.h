#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
/* Private typedef -----------------------------------------------------------*/
void led_init(int num)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = num;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void led_on(int num)
{
  GPIO_SetBits(GPIOD,num);
}
void led_off(int num)
{
  GPIO_ResetBits(GPIOD,num);
}
void set_patterns(int patt_id)
{
  led_off(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15);
  if (patt_id == 1)  led_on(GPIO_Pin_12);
  if (patt_id == 2)  led_on(GPIO_Pin_13);
  if (patt_id == 3)  led_on(GPIO_Pin_14);
  if (patt_id == 4)  led_on(GPIO_Pin_15);
  if (patt_id == 5)  led_on(GPIO_Pin_12 | GPIO_Pin_13);
  if (patt_id == 6)  led_on(GPIO_Pin_12 | GPIO_Pin_14);
  if (patt_id == 7)  led_on(GPIO_Pin_12 | GPIO_Pin_15);
  if (patt_id == 8)  led_on(GPIO_Pin_13 | GPIO_Pin_14);
  if (patt_id == 9)  led_on(GPIO_Pin_13 | GPIO_Pin_15);
  if (patt_id == 10)  led_on(GPIO_Pin_14 | GPIO_Pin_15);
  if (patt_id == 11)  led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
  if (patt_id == 12)  led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
  if (patt_id == 13)  led_on(GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
  if (patt_id == 14)  led_on(GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  if (patt_id == 15)  led_on(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  
}