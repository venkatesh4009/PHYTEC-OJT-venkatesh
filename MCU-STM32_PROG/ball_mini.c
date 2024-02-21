#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

UART_HandleTypeDef huart1;

// Define the GPIO pin for the buzzer
#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_GPIO_PIN GPIO_PIN_5

#define ONBOARD_LED_PIN GPIO_PIN_5 // LD2
#define ONBOARD_LED_PORT GPIOA
#define BALL_SENSOR_PIN GPIO_PIN_0 // Replace with the appropriate pin
#define BALL_SENSOR_PORT GPIOB
GPIO_PinState ballSensorState = GPIO_PIN_RESET;
GPIO_PinState buzzerState = GPIO_PIN_RESET;
GPIO_PinState onboardLEDState = GPIO_PIN_RESET;

// Function prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void UART_Init(void);
void Error_Handler(void);

int main(void)
{
  // Initialize HAL Library
  HAL_Init();

  // Configure the system clock
  SystemClock_Config();

  // Initialize peripherals (GPIO and UART in this case)
  MX_GPIO_Init();
  UART_Init();

  // Main loop
  while (1)
  {
    ballSensorState = HAL_GPIO_ReadPin(BALL_SENSOR_PORT, BALL_SENSOR_PIN);

    // Check the state of the buzzer pin
    buzzerState = HAL_GPIO_ReadPin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);

    // Check the state of the onboard LED pin
    onboardLEDState = HAL_GPIO_ReadPin(ONBOARD_LED_PORT, ONBOARD_LED_PIN);

    // Print the values to Minicom
    char buffer[50];
    sprintf(buffer, "Ball Sensor: %d, Buzzer: %d, LED: %d\n", ballSensorState, buzzerState, onboardLEDState);
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

    // Add a delay here to avoid printing too quickly
    HAL_Delay(1000);
  }
}

void UART_Init(void)
{
  // Initialize UART1 for communication
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

// The rest of your code (SystemClock_Config, GPIO initialization, and Error_Handler) remains the same.
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
}

// Error handler function (customize it for your application)
void Error_Handler(void)
{
  while (1)
  {
    // An error occurred, stay in this loop
  }
}
