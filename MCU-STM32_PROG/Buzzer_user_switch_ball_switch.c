#include "main.h"
#include "stm32f4xx_hal.h"

// Define the GPIO pin for the buzzer
#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_GPIO_PIN GPIO_PIN_5

// Define the GPIO pin for the onboard LED (LD2 on the STM32F446RE board)
#define ONBOARD_LED_PIN GPIO_PIN_5 // LD2
#define ONBOARD_LED_PORT GPIOA

// Define the GPIO pin for the user switch (USER button)
#define USER_SWITCH_PIN GPIO_PIN_13 // USER button
#define USER_SWITCH_PORT GPIOC

// Function prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  // Initialize HAL Library
  HAL_Init();

  // Configure the system clock
  SystemClock_Config()

  // Initialize peripherals (GPIO in this case)
  MX_GPIO_Init();

  // Main loop
  while (1)
  {
    // Check the state of the BALL switch sensor (replace with your sensor input logic)
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)
    {
      // BALL switch sensor is activated (tilted)
      // Turn on the buzzer
      HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_SET);

      // Turn on the onboard LED
      HAL_GPIO_WritePin(ONBOARD_LED_PORT, ONBOARD_LED_PIN, GPIO_PIN_SET);
    }
    else
    {
      // BALL switch sensor is not activated (level)
      // Turn off the buzzer
      HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_RESET);

      // Turn off the onboard LED
      HAL_GPIO_WritePin(ONBOARD_LED_PORT, ONBOARD_LED_PIN, GPIO_PIN_RESET);
    }

    // Check the state of the user switch (USER button)
    if (HAL_GPIO_ReadPin(USER_SWITCH_PORT, USER_SWITCH_PIN) == GPIO_PIN_RESET)
    {
      // USER button is pressed
    	  HAL_GPIO_WritePin(USER_SWITCH_PORT, USER_SWITCH_PIN , GPIO_PIN_RESET);

    	      // Turn off the onboard LED
    	  HAL_GPIO_WritePin(ONBOARD_LED_PORT, ONBOARD_LED_PIN, GPIO_PIN_RESET);
      // You can add additional functionality here
    }
  }
}

// System Clock Configuration
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

// GPIO Initialization
static void MX_GPIO_Init(void)
{
  // GPIO Ports Clock Enable
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Configure the GPIO pin for the buzzer as an output
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = BUZZER_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);

  // Configure the GPIO pin for the BALL switch sensor as an input (replace with your sensor's configuration)
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configure the GPIO pin for the onboard LED (LD2) as an output
  GPIO_InitStruct.Pin = ONBOARD_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ONBOARD_LED_PORT, &GPIO_InitStruct);

  // Configure the GPIO pin for the user switch (USER button) as an input
  GPIO_InitStruct.Pin = USER_SWITCH_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP; // Enable the internal pull-up resistor
  HAL_GPIO_Init(USER_SWITCH_PORT, &GPIO_InitStruct);
}

// Error handler function (customize it for your application)
void Error_Handler(void)
{
  while (1)
  {
    // An error occurred, stay in this loop
  }
}
