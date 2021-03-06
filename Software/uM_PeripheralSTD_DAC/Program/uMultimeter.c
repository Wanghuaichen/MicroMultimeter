/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "drivers\stm32f3_dac.h"
#include "algorithms\algorithm_mathUnit.h"

#include "uMultimeter.h"
/*====================================================================================================*/
/*====================================================================================================*/
void UM_Init( void )
{
  SystemInit();
  HAL_InitTick();

  UM_GPIO_Config();
  UM_DAC_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void UM_Loop( void )
{
  float data = 0.0f;
  float rad = 0.0f;
  int32_t theta = 0;

  while(1) {
    theta += 2;
    if(theta == 360) theta = 0;
    rad = toRad(theta);

    data = 0.0f;
    for(uint8_t i = 1; i < 10; i = i + 2)
      data += (1.0f/i) * sinf(i * rad);

    data += 1.0f;   // [-1, 1] -> [0, 2]

    DAC_SetData(DAC_Channel_1, data * 2048);
    DAC_SetData(DAC_Channel_2, (2.0 - data) * 2048);

    LED_G_Toggle();
//    delay_ms(10);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
