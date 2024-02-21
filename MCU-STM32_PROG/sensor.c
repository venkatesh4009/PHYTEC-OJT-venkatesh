#include "main.h"
#include "stm32f4xx_hal.h"

#define KY020_PIN GPIO_PIN_0
#define KY020_PORT GPIOB
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1) {
    uint8_t ky020State = HAL_GPIO_ReadPin(KY020_PORT, KY020_PIN);

    if (ky020State == GPIO_PIN_RESET) {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // Turn on LED when tilted
    } else {
      HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // Turn off LED when level/upright
    }
  }
}

void SystemClock_Config(void) {
  // Your clock configuration code here
}

static void MX_GPIO_Init(void) {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Configure the KY-020 pin as input with pull-up
  GPIO_InitStruct.Pin = KY020_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KY020_PORT, &GPIO_InitStruct);

  // Configure the LED pin as output
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void Error_Handler(void) {
  while (1) {
    // An error occurred, stay in this loop
  }
}
