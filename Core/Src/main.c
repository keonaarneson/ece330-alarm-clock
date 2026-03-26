/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body Final Project SP2025
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "seg7.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM7_Init(void);


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char ramp = 0;
char RED_BRT = 0;
char GREEN_BRT = 0;
char BLUE_BRT = 0;
char RED_STEP = 1;
char GREEN_STEP = 2;
char BLUE_STEP = 3;
char DIM_Enable = 0;
char Music_ON = 0;
int TONE = 0;
int COUNT = 0;
int INDEX = 0;
int Note = 0;
int Save_Note = 0;
int Vibrato_Depth = 1;
int Vibrato_Rate = 40;
int Vibrato_Count = 0;
char Animate_On = 0;
char Message_Length = 0;
char *Message_Pointer;
char *Save_Pointer;
int Delay_msec = 0;
int Delay_counter = 0;


/* HELLO ECE-330L */
char Message[] =
		{SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,
		CHAR_H,CHAR_E,CHAR_L,CHAR_L,CHAR_O,SPACE,CHAR_E,CHAR_C,CHAR_E,DASH,CHAR_3,CHAR_3,CHAR_0,CHAR_L,
		SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE,SPACE};

/* Declare array for Song */
Music Song[100];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM7_Init();
  //MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  /********************************************************************
   * PWR->CR |= ???;  //Enable Real Time Clock (RTC) Register Access  *
   * RCC->BDCR |= ???;  //Set clock source for RTC                    *
   * RCC->BDCR |= ???; //Enable RTC									  *
   ********************************************************************/

  /*** Configure GPIOs ***/
  GPIOD->MODER = 0x55555555; // set all Port D pins to outputs
  GPIOA->MODER |= 0x000000FF; // Port A mode register - make A0 to A3 analog pins
  GPIOE->MODER |= 0x55555555; // Port E mode register - make E0 to E15 outputs
  GPIOC->MODER |= 0x0; // Port C mode register - all inputs
  GPIOE->ODR = 0xFFFF; // Set all Port E pins high

  /*** Configure ADC1 ***/
  RCC->APB2ENR |= 1<<8;  // Turn on ADC1 clock by forcing bit 8 to 1 while keeping other bits unchanged
  ADC1->SMPR2 |= 1; // 15 clock cycles per sample
  ADC1->CR2 |= 1; // Turn on ADC1 by forcing bit 0 to 1 while keeping other bits unchanged

  /*****************************************************************************************************
  These commands are handled as part of the MX_TIM7_Init() function and don't need to be enabled
  RCC->AHB1ENR |= 1<<5; // Enable clock for timer 7
  __enable_irq(); // Enable interrupts
  NVIC_EnableIRQ(TIM7_IRQn); // Enable Timer 7 Interrupt in the NVIC controller
  *******************************************************************************************************/

  TIM7->PSC = 199; //250Khz timer clock prescaler value, 250Khz = 50Mhz / 200
  TIM7->ARR = 1; // Count to 1 then generate interrupt (divide by 2), 125Khz interrupt rate to increment byte counter for 78Hz PWM
  TIM7->DIER |= 1; // Enable timer 7 interrupt
  TIM7->CR1 |= 1; // Enable timer counting

  /* Samsung Homecoming Alarm Song */
  	Song[0].note = F5;
  	Song[0].size = quarter;
    Song[0].tempo = 1400;
    Song[0].space = 10;
    Song[0].end = 0;

    Song[1].note = E5;
    Song[1].size = quarter;
    Song[1].tempo = 1400;
    Song[1].space = 10;
    Song[1].end = 0;

    Song[2].note = F5;
    Song[2].size = _8th;
    Song[2].tempo = 1400;
    Song[2].space = 10;
    Song[2].end = 0;

    Song[3].note = A5;
    Song[3].size = _8th;
    Song[3].tempo = 1400;
    Song[3].space = 10;
    Song[3].end = 0;

    Song[4].note = D5;
    Song[4].size = quarter;
    Song[4].tempo = 1400;
    Song[4].space = 10;
    Song[4].end = 0;

  //

    Song[5].note = F5;
    Song[5].size = quarter;
    Song[5].tempo = 1400;
    Song[5].space = 10;
    Song[5].end = 0;

    Song[6].note = E5;
    Song[6].size = quarter;
    Song[6].tempo = 1400;
    Song[6].space = 10;
    Song[6].end = 0;

    Song[7].note = F5;
    Song[7].size = _8th;
    Song[7].tempo = 1400;
    Song[7].space = 10;
    Song[7].end = 0;

    Song[8].note = A5;
    Song[8].size = _8th;
    Song[8].tempo = 1400;
    Song[8].space = 10;
    Song[8].end = 0;

    Song[9].note = D5;
    Song[9].size = quarter;
    Song[9].tempo = 1400;
    Song[9].space = 10;
    Song[9].end = 0;

    //

    Song[10].note = G5;
    Song[10].size = _8th;
    Song[10].tempo = 1400;
    Song[10].space = 10;
    Song[10].end = 0;

    Song[11].note = F5;
    Song[11].size = _8th;
    Song[11].tempo = 1400;
    Song[11].space = 10;
    Song[11].end = 0;

    Song[12].note = E5;
    Song[12].size = _8th;
    Song[12].tempo = 1400;
    Song[12].space = 100;
    Song[12].end = 0;

    Song[13].note = D5;
    Song[13].size = _8th;
    Song[13].tempo = 1400;
    Song[13].space = 10;
    Song[13].end = 0;

    Song[14].note = C5;
    Song[14].size = _8th;
    Song[14].tempo = 1400;
    Song[14].space = 10;
    Song[14].end = 0;

    Song[15].note = D5;
    Song[15].size = _8th;
    Song[15].tempo = 1400;
    Song[15].space = 10;
    Song[15].end = 0;

    Song[16].note = E5;
    Song[16].size = _8th;
    Song[16].tempo = 1400;
    Song[16].space = 10;
    Song[16].end = 0;

    Song[17].note = C5;
    Song[17].size = _8th;
    Song[17].tempo = 1400;
    Song[17].space = 10;
    Song[17].end = 0;

    //

    Song[18].note = D5;
    Song[18].size = _8th;
    Song[18].tempo = 1400;
    Song[18].space = 10;
    Song[18].end = 0;

    Song[19].note = E5;
    Song[19].size = _8th;
    Song[19].tempo = 1400;
    Song[19].space = 10;
    Song[19].end = 0;

    Song[20].note = F5;
    Song[20].size = _8th;
    Song[20].tempo = 1400;
    Song[20].space = 10;
    Song[20].end = 0;

    Song[21].note = G5;
    Song[21].size = _8th;
    Song[21].tempo = 1400;
    Song[21].space = 10;
    Song[21].end = 0;

    Song[22].note = A5;
    Song[22].size = quarter;
    Song[22].tempo = 1400;
    Song[22].space = 10;
    Song[22].end = 0;

    Song[23].note = rest;
    Song[23].size = quarter;
    Song[23].tempo = 1400;
    Song[23].space = 10;
    Song[23].end = 0;

    //

    Song[24].note = F5;
    Song[24].size = quarter;
    Song[24].tempo = 1400;
    Song[24].space = 10;
    Song[24].end = 0;

    Song[25].note = E5;
    Song[25].size = quarter;
    Song[25].tempo = 1400;
    Song[25].space = 10;
    Song[25].end = 0;

    Song[26].note = F5;
    Song[26].size = _8th;
    Song[26].tempo = 1400;
    Song[26].space = 10;
    Song[26].end = 0;

    Song[27].note = A5;
    Song[27].size = _8th;
    Song[27].tempo = 1400;
    Song[27].space = 10;
    Song[27].end = 0;

    Song[28].note = D5;
    Song[28].size = quarter;
    Song[28].tempo = 1400;
    Song[28].space = 100;
    Song[28].end = 0;

    //

    Song[29].note = F5;
    Song[29].size = quarter;
    Song[29].tempo = 1400;
    Song[29].space = 10;
    Song[29].end = 0;

    Song[30].note = E5;
    Song[30].size = quarter;
    Song[30].tempo = 1400;
    Song[30].space = 10;
    Song[30].end = 0;

    Song[31].note = F5;
    Song[31].size = _8th;
    Song[31].tempo = 1400;
    Song[31].space = 100;
    Song[31].end = 0;

    Song[32].note = A5;
    Song[32].size = _8th;
    Song[32].tempo = 1400;
    Song[32].space = 100;
    Song[32].end = 0;

    Song[33].note = D5;
    Song[33].size = quarter;
    Song[33].tempo = 1400;
    Song[33].space = 100;
    Song[33].end = 0;

    //

    Song[34].note = G5;
    Song[34].size = _8th;
    Song[34].tempo = 1400;
    Song[34].space = 100;
    Song[34].end = 0;

    Song[35].note = F5;
    Song[35].size = _8th;
    Song[35].tempo = 1400;
    Song[35].space = 100;
    Song[35].end = 0;

    Song[36].note = E5;
    Song[36].size = _8th;
    Song[36].tempo = 1400;
    Song[36].space = 10;
    Song[36].end = 0;

    Song[37].note = D5;
    Song[37].size = _8th;
    Song[37].tempo = 1400;
    Song[37].space = 10;
    Song[37].end = 0;

    Song[38].note = C5;
    Song[38].size = _8th;
    Song[38].tempo = 1400;
    Song[38].space = 10;
    Song[38].end = 0;

    Song[39].note = D5;
    Song[39].size = _8th;
    Song[39].tempo = 1400;
    Song[39].space = 10;
    Song[39].end = 0;

    Song[40].note = E5;
    Song[40].size = _8th;
    Song[40].tempo = 1400;
    Song[40].space = 10;
    Song[40].end = 0;

    Song[41].note = C5;
    Song[41].size = _8th;
    Song[41].tempo = 1400;
    Song[41].space = 10;
    Song[41].end = 0;

    //

    Song[42].note = D5;
    Song[42].size = _8th;
    Song[42].tempo = 1400;
    Song[42].space = 10;
    Song[42].end = 0;

    Song[43].note = A4;
    Song[43].size = _8th;
    Song[43].tempo = 1400;
    Song[43].space = 10;
    Song[43].end = 0;

    Song[44].note = F4;
    Song[44].size = _8th;
    Song[44].tempo = 1400;
    Song[44].space = 10;
    Song[44].end = 0;

    Song[45].note = A4;
    Song[45].size = _8th;
    Song[45].tempo = 1400;
    Song[45].space = 10;
    Song[45].end = 0;

    Song[46].note = D4;
    Song[46].size = quarter;
    Song[46].tempo = 1400;
    Song[46].space = 10;
    Song[46].end = 0;

    Song[47].note = rest;
    Song[47].size = quarter;
    Song[47].tempo = 1400;
    Song[47].space = 10;
    Song[47].end = 1;

  Save_Note = Song[0].note;  // Needed for vibrato effect
  INDEX = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Message_Pointer = &Message[0];
  Save_Pointer = &Message[0];
  Message_Length = sizeof(Message)/sizeof(Message[0]);
  Delay_msec = 200;
  Animate_On = 0;

  PWR->CR |= 1 << 8; //Enables access to RTC/RTC backup registers

  RCC->BDCR |= 1 << 9; //LSI oscillator clock used as a RTC clock

  RCC->BDCR |= (1 << 15); //Enable RTC

  /* */
  int analog_value, sel_1=0, sel_2=0, temp;
  int hour_10, hour_1, minute_10, minute_1, second_10, second_1;
  int year_10, year_1, weekday, month_10, month_1, date_10, date_1;
  int Ahour_10, Ahour_1, Aminute_10, Aminute_1, Asecond_10, Asecond_1;
  while (1)
  {
	  if ((GPIOC->IDR & 1) == 1) //checks if clock is in "configure" mode
	  {
		  while ((GPIOC->IDR & 1) == 1) //checks if clock is still in "configure" mode
		  {
			  ADC1->SQR3 = 1; //Select ADC channel 1
			  HAL_Delay(1);
			  ADC1->CR2 |= 1 << 30; // Start a conversion on ADC1
			  HAL_Delay(1);
			  analog_value = ADC1->DR;
			  if (((GPIOC->IDR >> 11) & 1) == 0) //PC11 Button to change display selection
			  {
				  HAL_Delay(50);
				  while(((GPIOC->IDR >> 11) & 1) == 0) //Debounce
				  {
					  HAL_Delay(50);
				  }
				  if (sel_1 < 1)
				  {
					  sel_1++;
				  }
				  else
				  {
					  sel_1 = 0;
				  }
				  GPIOD->ODR = sel_1+1;
			  }
			  if (((GPIOC->IDR >> 10) & 1) == 0) //PC10 Button to change edit selection
			  {
				  HAL_Delay(50);
				  while(((GPIOC->IDR >> 10) & 1) == 0) //Debounce
				  {
					  HAL_Delay(50);
				  }
				  if (sel_2 < 3)
				  {
					  sel_2++;
				  }
				  else
				  {
					  sel_2 = 0;
				  }
			  }
			  if (sel_1 == 0)
			  {
				  Seven_Segment_Digit(6,0,0);
				  switch (sel_2) //Cases for setting the TIME
				  {
				  case 0:
					  second_1 = (analog_value * 0x3B / 0xFFF)%10;
					  second_10 = (analog_value * 0x3B / 0xFFF)/10;
					  Seven_Segment_Digit(0,second_1,0);
					  Seven_Segment_Digit(1,second_10,0);
					  break;
				  case 1:
					  minute_1 = (analog_value * 0x3B / 0xFFF)%10;
					  minute_10 = (analog_value * 0x3B / 0xFFF)/10;
					  Seven_Segment_Digit(2,minute_1,0);
					  Seven_Segment_Digit(3,minute_10,0);
					  break;
				  case 2:
					  hour_1 = ((analog_value * 0x17 / 0xFFF)%10);
					  hour_10 = ((analog_value * 0x17 / 0xFFF)/10);
					  Seven_Segment_Digit(4,hour_1,0);
					  Seven_Segment_Digit(5,hour_10,0);
					  break;
				  }
			  }
			  else
			  {
				  switch (sel_2)//Cases for setting the DATE
				  {
				  case 0:
					  date_1 = (analog_value * 0x1F/0xFFF)%10;
					  date_10 = (analog_value * 0x1F/0xFFF)/10;
					  Seven_Segment_Digit(0,date_1,0);
					  Seven_Segment_Digit(1,date_10,0);
					  break;
				  case 1:
					  month_1 = (analog_value * 0xC/0xFFF)%10;
					  month_10 = (analog_value * 0xC/0xFFF)/10;
					  Seven_Segment_Digit(2,month_1,0);
					  Seven_Segment_Digit(3,month_10,0);
					  break;
				  case 3:
					  weekday = ((analog_value * 0x6/0xFFF)%10)+1;
					  Seven_Segment_Digit(7,weekday,0);
					  break;
				  case 2:
					  year_1 = (analog_value * 0x63/0xFFF)%10;
					  year_10 = (analog_value * 0x63/0xFFF)/10;
					  Seven_Segment_Digit(4,year_1,0);
					  Seven_Segment_Digit(5,year_10,0);
					  break;
				  }
			  }
		  }
		  RTC->WPR = 0xCA; //Unlocks write protection
		  RTC->WPR = 0x53; //Unlocks write protection
		  RTC->ISR |= 1<<7; //Enter initialization mode
		  while(!(RTC->ISR & (1 << 6)));
		  RTC->TR = second_1 + (second_10 << 4) + (minute_1 << 8) + (minute_10 << 12) + (hour_1 << 16) + (hour_10 << 20);
		  RTC->DR = date_1 + (date_10 << 4) + (month_1 << 8) + (month_10 << 12) + (weekday << 13) + (year_1 << 16) + (year_10 << 20);
		  RTC->ISR &= ~(1 << 7); //Exit initialization mode
		  RTC->WPR = 0x00;
	  }
    /* USER CODE BEGIN 3 */
	  if (((GPIOC->IDR >> 1) & 1) == 1)
	  {
		  while (((GPIOC->IDR >> 1) & 1) == 1)
		  {
			  ADC1->SQR3 = 1; //Select ADC channel 1
			  HAL_Delay(1);
			  ADC1->CR2 |= 1 << 30; // Start a conversion on ADC1
			  HAL_Delay(1);
			  analog_value = ADC1->DR;
			  if (((GPIOC->IDR >> 10) & 1) == 0) //PC10 Button to change edit selection
			  {
				  HAL_Delay(50);
				  while(((GPIOC->IDR >> 10) & 1) == 0) //Debounce
				  {
					  HAL_Delay(50);
				  }
				  if (sel_2 < 3)
				  {
					  sel_2++;
				  }
				  else
				  {
					  sel_2 = 0;
				  }
			  }
			  switch (sel_2)
			  {
			  case 0:
				  Asecond_1 = (analog_value * 0x3B / 0xFFF)%10;
				  Asecond_10 = (analog_value * 0x3B / 0xFFF)/10;
				  Seven_Segment_Digit(0,Asecond_1,0);
				  Seven_Segment_Digit(1,Asecond_10,0);
				  break;
			  case 1:
				  Aminute_1 = (analog_value * 0x3B / 0xFFF)%10;
				  Aminute_10 = (analog_value * 0x3B / 0xFFF)/10;
				  Seven_Segment_Digit(2,Aminute_1,0);
				  Seven_Segment_Digit(3,Aminute_10,0);
				  break;
			  case 2:
				  Ahour_1 = ((analog_value * 0x17 / 0xFFF)%10);
				  Ahour_10 = ((analog_value * 0x17 / 0xFFF)/10);
				  Seven_Segment_Digit(4,Ahour_1,0);
				  Seven_Segment_Digit(5,Ahour_10,0);
				  break;
			  }
		  }
		  RTC->WPR = 0xCA; //Unlocks write protection
		  RTC->WPR = 0x53; //Unlocks write protection
		  RTC->ISR |= 1<<7; //Enter initialization mode
		  while(!(RTC->ISR & (1 << 6)));
		  RTC->CR &= ~(1<<8); //Disable alarm A
		  RTC->CR &= ~(1<<12); //Disable alarm A interrupt
		  while((RTC->ISR & 1) == 0);
		  RTC->ALRMAR = Asecond_1 + (Asecond_10 << 4) + (Aminute_1 << 8) + (Aminute_10 << 12) + (Ahour_1 << 16) + (Ahour_10 << 20) + (1 << 31);
		  RTC->CR |= (1<<8); //Enable alarm A
		  RTC->CR |= (1<<12); //Enable alarm A interrupt
		  RTC->ISR &= ~(1 << 7); //Exit initialization mode
		  RTC->WPR = 0x00;
	  }


	  if (((GPIOC->IDR >> 11) & 1) == 0) //PC11 Button to change display selection
	  {
		  HAL_Delay(50);
		  while(((GPIOC->IDR >> 11) & 1) == 0) //Debounce
		  {
			  HAL_Delay(50);
		  }
		  if (sel_1 < 1)
		  {
			  sel_1++;
		  }
		  else
		  {
	  		sel_1 = 0;
		  }
		  GPIOD->ODR = sel_1+1;
	  }
	  switch (sel_1) //Displays the selected mode
	  {
	  case 0:
		  Seven_Segment(RTC->TR);
		  break;
	  case 1:
		  temp = (RTC->DR);
		  temp = (temp & (0x7 << 13)) << 15; //Set segment 7 to the day of the week
		  temp = temp | (RTC->DR & ~(0x7 << 13)); //Add in the rest of the data
		  Seven_Segment(temp);
		  break;
	  }

	  if (((RTC->ISR >> 8) & 1) == 1)
	  {
		  Music_ON = 1;
		  RTC->ISR &= ~(1 << 8);
	  }
	  if (((GPIOC->IDR >> 10) & 1) == 0)
	  {
		  Music_ON = 0;
	  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}






static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65535;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

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
