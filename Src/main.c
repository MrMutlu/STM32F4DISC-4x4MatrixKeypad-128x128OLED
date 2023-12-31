/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "u8g2/u8g2.h"
#include  "stdbool.h"
#include <string.h>
#include  <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
GPIO_TypeDef* ROW_1_Port = GPIOC;
GPIO_TypeDef* ROW_2_Port = GPIOC;
GPIO_TypeDef* ROW_3_Port = GPIOC;
GPIO_TypeDef* ROW_4_Port = GPIOC;
GPIO_TypeDef* COL_1_Port = GPIOA;
GPIO_TypeDef* COL_2_Port = GPIOA;
GPIO_TypeDef* COL_3_Port = GPIOA;
GPIO_TypeDef* COL_4_Port = GPIOA;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
char numBuffer[4];
char numABuffer[4];
char numBBuffer[4];
char numCBuffer[4];
char numDBuffer[4];
uint8_t bufferIndex = 0;

uint8_t buttonPressed = 0;
uint8_t button2Pressed = 0;

extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
bool firstTime = false;
static u8g2_t u8g2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void processKeyPress(char key) {
    // Clear the buffer and set common settings
    u8g2_SetFontMode(&u8g2, 0);  // Transparent
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tr);

    switch (key) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            if (bufferIndex < 4) {
                numBuffer[bufferIndex++] = key;
                numBuffer[bufferIndex] = '\0';  // Null-terminate the string
                u8g2_ClearBuffer(&u8g2);
                u8g2_SendBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 60, 60, numBuffer);
                u8g2_SendBuffer(&u8g2);
            }
            break;
        case '*':
            bufferIndex = 0;
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2, 60, 60, "DELETED! ");
            u8g2_SendBuffer(&u8g2);
            break;
        case '#':
            if (bufferIndex > 0) {
                // Decrement bufferIndex to point to the last entered digit
                --bufferIndex;
                numBuffer[bufferIndex] = '\0';  // Set the last digit to null character
                u8g2_ClearBuffer(&u8g2);
                u8g2_SendBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 60, 60, numBuffer);  // Redraw the buffer without the last digit
                u8g2_SendBuffer(&u8g2);
            }
            break;
        case 'A':
        	if(bufferIndex == 4){

        	    for (int i = 0; i < 4; ++i) {
        	        numABuffer[i] = numBuffer[i];
        	    }
                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 5, 60, "A SAVED ");
                u8g2_SendBuffer(&u8g2);
                bufferIndex = 0;
                memset(numBuffer, 0, sizeof(numBuffer));
        		numABuffer[4] = '\0';

        	}
            break;
        case 'B':
        	if(bufferIndex == 4){

        	    for (int i = 0; i < 4; ++i) {
        	        numBBuffer[i] = numBuffer[i];
        	    }

                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 5, 50, "B SAVED ");
                u8g2_SendBuffer(&u8g2);
                bufferIndex = 0;
                memset(numBuffer, 0, sizeof(numBuffer));
        		numBBuffer[4] = '\0';

        	}
            break;
        case 'C':
        	if(bufferIndex == 4){

        	    for (int i = 0; i < 4; ++i) {
        	        numCBuffer[i] = numBuffer[i];
        	    }

                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 5, 50, "C SAVED ");
                u8g2_SendBuffer(&u8g2);
                bufferIndex = 0;
                memset(numBuffer, 0, sizeof(numBuffer));
        		numCBuffer[4] = '\0';


        	}
            break;
        case 'D':
        	if(bufferIndex == 4){

        	    for (int i = 0; i < 4; ++i) {
        	        numDBuffer[i] = numBuffer[i];
        	    }

                u8g2_ClearBuffer(&u8g2);
                u8g2_DrawUTF8(&u8g2, 5, 50, "D SAVED ");
                u8g2_SendBuffer(&u8g2);
                bufferIndex = 0;
                memset(numBuffer, 0, sizeof(numBuffer));
        		numDBuffer[4] = '\0';

        	}
            break;
        default:
            // Handle other key presses or invalid keys
            break;

    }
    if(bufferIndex == 4){
    u8g2_ClearBuffer(&u8g2);
    u8g2_DrawUTF8(&u8g2, 32, 40, numBuffer);
    u8g2_DrawUTF8(&u8g2, 8, 50, "PRESS * TO DELETE ALL ");
    u8g2_DrawUTF8(&u8g2, 8, 60, "OR PRESS A/B/C/D ");
    u8g2_DrawUTF8(&u8g2, 8, 70, "OR # TO DELETE ");
    u8g2_DrawUTF8(&u8g2, 8, 80, "LAST NUMBER ");
    u8g2_SendBuffer(&u8g2);

    }

}

void showKeyPress(char key) {
    // Clear the buffer and set common settings
    u8g2_SetFontMode(&u8g2, 0);  // Transparent
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tr);

    switch (key) {

        case 'A':
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2, 56, 50, numABuffer);
            u8g2_SendBuffer(&u8g2);
            break;
        case 'B':
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2, 56, 50, numBBuffer);
            u8g2_SendBuffer(&u8g2);
            break;
        case 'C':
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2, 56, 50, numCBuffer);
            u8g2_SendBuffer(&u8g2);
            break;
        case 'D':
            u8g2_ClearBuffer(&u8g2);
            u8g2_DrawUTF8(&u8g2, 56, 50, numDBuffer);
            u8g2_SendBuffer(&u8g2);
            break;
        default:
            break;
    }
}


char keypad_scan(void)
{
  char keys[4][4] = {{'1', '2', '3', 'A'},
                     {'4', '5', '6', 'B'},
                     {'7', '8', '9', 'C'},
                     {'*', '0', '#', 'D'}};

  for(int i = 0; i < 4; i++)
  {
    // Set current column as output and low
    switch(i)
    {
      case 0:
        HAL_GPIO_WritePin(COL_1_Port, COL_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(COL_2_Port, COL_2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(COL_3_Port, COL_3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(COL_4_Port, COL_4_Pin, GPIO_PIN_SET);
        break;

      case 1:
        HAL_GPIO_WritePin(COL_1_Port, COL_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(COL_2_Port, COL_2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(COL_3_Port, COL_3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(COL_4_Port, COL_4_Pin, GPIO_PIN_SET);
        break;

	  case 2:
		HAL_GPIO_WritePin(COL_1_Port, COL_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(COL_2_Port, COL_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(COL_3_Port, COL_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(COL_4_Port, COL_4_Pin, GPIO_PIN_SET);
		break;

	  case 3:
		HAL_GPIO_WritePin(COL_1_Port, COL_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(COL_2_Port, COL_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(COL_3_Port, COL_3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(COL_4_Port, COL_4_Pin, GPIO_PIN_RESET);
		break;
}
// Read current rows
if(HAL_GPIO_ReadPin(ROW_1_Port, ROW_1_Pin) == GPIO_PIN_RESET)
  return keys[0][i];
if(HAL_GPIO_ReadPin(ROW_2_Port, ROW_2_Pin) == GPIO_PIN_RESET)
  return keys[1][i];
if(HAL_GPIO_ReadPin(ROW_3_Port, ROW_3_Pin) == GPIO_PIN_RESET)
  return keys[2][i];
if(HAL_GPIO_ReadPin(ROW_4_Port, ROW_4_Pin) == GPIO_PIN_RESET)
  return keys[3][i];
}
  HAL_Delay(50);

return 0; // No key pressed
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char key_pressed = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	u8g2_Setup_ssd1327_ea_w128128_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi, u8x8_stm32_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
    u8g2_SetFontMode(&u8g2, 0);  // Transparent
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tr);
    u8g2_DrawUTF8(&u8g2, 8, 30, "Choose 4 numbers");
    u8g2_DrawUTF8(&u8g2, 8, 60, "Click White Button");
    u8g2_DrawUTF8(&u8g2, 8, 90, "To Start!");
    u8g2_SendBuffer(&u8g2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

      key_pressed = keypad_scan();

	    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15)) {
	        // Button is pressed

	        if (!buttonPressed) {
	            buttonPressed = 1;  // Set the flag
	            processKeyPress(key_pressed);
	        }
	    } else {
	        buttonPressed = 0;  // Reset the flag when the button is released
	    }

	    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13)) {
	        // Button is pressed

	        if (!button2Pressed) {
	            button2Pressed = 1;  // Set the flag

	            showKeyPress(key_pressed);
	        	}
	    } else {
	        button2Pressed = 0;  // Reset the flag when the button is released
	    }
	    HAL_Delay(10);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, COL_2_Pin|COL_1_Pin|COL_4_Pin|COL_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, OLED_RST_Pin|OLED_CS_Pin|OLED_DC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : ROW_2_Pin ROW_1_Pin ROW_4_Pin ROW_3_Pin */
  GPIO_InitStruct.Pin = ROW_2_Pin|ROW_1_Pin|ROW_4_Pin|ROW_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : COL_2_Pin COL_1_Pin COL_4_Pin COL_3_Pin */
  GPIO_InitStruct.Pin = COL_2_Pin|COL_1_Pin|COL_4_Pin|COL_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE13 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : OLED_RST_Pin OLED_CS_Pin OLED_DC_Pin */
  GPIO_InitStruct.Pin = OLED_RST_Pin|OLED_CS_Pin|OLED_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
