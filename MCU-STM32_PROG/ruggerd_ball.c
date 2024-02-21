#include "main.h"
#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart1; // UART1 handle

// Define GPIO pins for LED and tilt switch
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA
#define TILT_PIN GPIO_PIN_0
#define TILT_PORT GPIOB

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void); // Function to initialize UART1

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init(); // Initialize UART1

  while (1) {
    // Read the tilt switch state
    uint8_t tiltState = HAL_GPIO_ReadPin(TILT_PORT, TILT_PIN);

    // Check if the tilt switch is tilted
    if (tiltState == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // Turn on LED
    } else {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off LED
    }

    // Send a string over UART1
    char str[] = "Hello, UART1!\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
  }
}

void SystemClock_Config(void) {
  // ... (same as before)
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  RCC_OscInitStruct.PLL.PLLM = 16;
	  RCC_OscInitStruct.PLL.PLLN = 336;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
	    Error_Handler();
	  }

	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
	                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
	    Error_Handler();
	  }
}

static void MX_GPIO_Init(void) {
  // ... (same as before)
	__HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  // Configure LED pin as output
	  GPIO_InitStruct.Pin = LED_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	  // Configure tilt switch pin as input
	  GPIO_InitStruct.Pin = TILT_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(TILT_PORT, &GPIO_InitStruct);
}

static void MX_USART1_UART_Init(void) {
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600; // Set your desired baud rate
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart1) != HAL_OK) {
    Error_Handler();
  }
}

void Error_Handler(void) {
  while (1) {
    // An error occurred, stay in this loop
  }
}
