
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>

// Define GPIO pins for LED and tilt switch
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA
#define TILT_PIN GPIO_PIN_0
#define TILT_PORT GPIOB

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void WE10_Init(char *SSID, char *PASSWD);
void MX_USART2_UART_Init(void);


void MX_USART1_UART_Init(void);
void uart1_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x00000010;
	GPIOA->MODER &= ~0x003C0000;
	GPIOA->MODER |= 0x00280000;
	GPIOA->AFR[1] &= ~0x0FF0;
	GPIOA->AFR[1] |= 0x0770 ; /* alt8 for UART4 */
	USART1->BRR = 0x0683; /* 9600 baud @ 16 MHz */
	USART1->CR1 = 0x000C;/* enable Tx, Rx, 8-bit data */
	USART1->CR2 = 0x0000; /* 1 stop bit*/
	USART1->CR3 = 0x0000; /* no flow control */
	USART1->CR1 |= 0x2000; /*enable UART4 */

}



void uart1_write(int ch) {
while (!(USART1->SR & 0x0080)) {} // wait until Tx buffer empty
USART1->DR = (ch & 0xFF);
}

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init(); // Initialize UART1
  MX_USART2_UART_Init(); // Initialize UART2
  uart1_init();
  //WE10_Init("Realme 5.0GHz","12345678");

  while (1) {
    // Read the tilt switch state
    uint8_t tiltState = HAL_GPIO_ReadPin(TILT_PORT, TILT_PIN);
uint8_t i;
    char buffer[20];
        sprintf(buffer, "Tilt State: %s\r\n", tiltState == GPIO_PIN_SET ? "Tilted" : "Not Tilted");
        for(i=0;buffer[i]!='\0';i++)
        {
        	uart1_write(buffer[i]);
        }
        //HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100); // Print to UART1
        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100); // Print to UART2


    // Check if the tilt switch is tilted
    if (tiltState == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // Turn on LED
      HAL_Delay(1000);
    } else {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off LED
      HAL_Delay(1000);
    }
  }
}
/*void WE10_Init(char *SSID, char *PASSWD)
{
  char buffer[128];
  // ... your initialization code for the WE10 module
  sprintf (&buffer[0], "CMD+RESET\r\n");
  	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 1000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);

  	HAL_UART_Receive(&huart1, (uint8_t*)buffer, strlen(buffer), 1000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);


  	/*********  CMD+WIFIMODE=1  **********/
  	//memset(&buffer[0],0x00,strlen(buffer));
  /*	sprintf (&buffer[0], "CMD+WIFIMODE=1\r\n");
  	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 1000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);

  	HAL_UART_Receive(&huart1, (uint8_t*)buffer, strlen(buffer), 1000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);


  	/********* CMD+CONTOAP=SSID,PASSWD **********/
  	//memset(&buffer[0],0x00,strlen(buffer));
  	/*sprintf (&buffer[0], "CMD+CONTOAP= %s,%s\r\n",SSID, PASSWD);
  	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 10000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 10000);
  	//memset(&buffer[0],0x00,strlen(buffer));
  	HAL_Delay(2000);
  	HAL_UART_Receive(&huart1, (uint8_t*)buffer, strlen(buffer), 10000);
  	HAL_Delay(500);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 10000);

  	/********* CMD?WIFI**********/
  	//memset(&buffer[0],0x00,strlen(buffer));
  	/*sprintf (&buffer[0], "CMD?WIFI\r\n");
  	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 10000);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 10000);
  //	memset(&buffer[0],0x00,strlen(buffer));
  //	HAL_Delay(500);
  	HAL_UART_Receive(&huart1, (uint8_t*)buffer, strlen(buffer), 10000);
  	HAL_Delay(500);
  	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 10000);

}*/

void MX_USART1_UART_Init(void)
{
  // Initialize UART1 here
	/* USER CODE BEGIN USART1_Init 0 */

	  /* USER CODE END USART1_Init 0 */

	  /* USER CODE BEGIN USART1_Init 1 */

	  /* USER CODE END USART1_Init 1 */
	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = 9600 ;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

// Add your UART initialization code for UART2
void MX_USART2_UART_Init(void)
{
  // Initialize UART2 here
	 /* USER CODE BEGIN USART2_Init 0 */

	  /* USER CODE END USART2_Init 0 */

	  /* USER CODE BEGIN USART2_Init 1 */

	  /* USER CODE END USART2_Init 1 */
	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN USART2_Init 2 */

	  /* USER CODE END USART2_Init 2 */
}


void SystemClock_Config(void) {
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

void Error_Handler(void) {
  while (1) {
    // An error occurred, stay in this loop
  }
}
