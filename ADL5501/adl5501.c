#include "adl5501.h"
#include "adc_hal.h"

#define  TEST_COUNT  16       //ad读取次数 

uint32_t s_adl_data[TEST_COUNT];
static float s_adlv;

void adl_init()
{
   //ADC
    MX_ADC_Init();
}
float adlval_get()
{
  volatile float adl=0;
  HAL_ADC_Start(&hadc);
  for(int i=0;i<TEST_COUNT;i++)
  {
     HAL_ADC_PollForConversion(&hadc, 10);
  
    /* Check if the continous conversion of regular channel is finished */
    if ((HAL_ADC_GetState(&hadc) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
    {
      /*##-6- Get the converted value of regular channel  ########################*/
      s_adl_data[i] = HAL_ADC_GetValue(&hadc);
    }
  }
  HAL_ADC_Stop(&hadc);
  
  for(int i=0;i<TEST_COUNT;i++)
  {
    adl=adl+(float)s_adl_data[i];
  }
  adl=adl/TEST_COUNT;
  adl=adl/4096*3.3;
  return adl;
}
/*校准函数*/
void adl_Calibration()
{  
   s_adlv=adlval_get();
   __NOP();
}
