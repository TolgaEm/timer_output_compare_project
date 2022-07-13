/*

Procedure:

1. Select the counter clock (internal, external, prescaler).

2. Write the desired data in the TIMx_ARR and TIMx_CCRx registers.

3. Set the CCxIE and/or CCxDE bits if an interrupt and/or a DMA request is to be
generated.

4. Select the output mode. For example, the user must write OCxM=011, OCxPE=0,
CCxP=0 and CCxE=1 to toggle OCx output pin when CNT matches CCRx, CCRx
preload is not used, OCx is enabled and active high.

5. Enable the counter by setting the CEN bit in the TIMx_CR1 register.

*/


#include "main.h"

void SystemClock_Config(void);
void GPIO_config(void);
void timer_output(uint16_t );

int main(void)
{

	GPIO_config();
	timer_output(5000);

	SystemClock_Config();

  while (1)
  {

  }
}


void GPIO_config(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // PORT A clock enable
	GPIOA->CRL = 0X0B; // PA0 set output as alernate function

}

void timer_output(uint16_t time){

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIM2 clock bus enabled
	TIM2->PSC = 4000 - 1; // set 1ms period
	TIM2->ARR = time - 1; // set boundary value
	TIM2->CCR1 = time - 1; // set compare value
	TIM2->CCMR1 |= 48; // set output compare as a toggle
	TIM2->CCER |= 0X01; // enable output compare
	TIM2->CR1 |= 0X01; //enable counter

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
