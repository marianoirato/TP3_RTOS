/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  *Aclaraciones
  *Led 1= B0
  *Led 2= B1
  *Led 3= B10
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <app_cfg.h>
#include <cpu_core.h>
#include <os.h>
#include <DIO.H>
#include <string.h>
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EXT_INT_MAX_NBR 16u
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define seno360 361
#define seno180 181
#define seno90 91
#define seno45 46
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

static void StartupTask (void *p_arg);//IO y Serial
static void SenoTsk (void *p_arg);//Generacion seno mediante R2R
static void PrimerSecuencia (void *p_arg);//Led secuencia 1
static void SegundaSecuencia (void *p_arg);//Led secuencia 2
static void TercerSecuencia (void *p_arg);//Led secuencia 3

static OS_STK StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE];//IO y Serial
static OS_STK SenoTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE];//Generacion seno mediante R2R
static OS_STK PrimerSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE];//Led secuencia 1
static OS_STK SegundaSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE];//Led secuencia 2
static OS_STK TercerSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE];//Led secuencia 3

void UsbPrintf (CPU_CHAR  *p_fmt, ...);

void PinReset();
void SuspendAllTasks();
void SuspendAllTasksExceptOne(int);
int GetButton();
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
enum LED{
	LED1,
	LED2,
	LED3
};

enum BOTON{
	BOTON1,
	BOTON2,
	BOTON3,
	BOTON4,
	BOTON5,
	DEFAULT
};

enum TASKS{
	INIT = 1,
	SENO,
	SEC1,
	SEC2,
	SEC3
};

int salida[8] = {0};
int frecuencia = 0;
int valorFrecuencia[5] = {1, 10, 20, 30, 40};
int valorFrecuenciaHz[5] = {213, 21, 10, 7, 5};

int senoArreglo45[seno45]={
		0x80, 0x91, 0xa3, 0xb3, 0xc3, 0xd1, 0xde, 0xe9, 0xf2, 0xf9, 0xfd, 0xff, 0xfe, 0xfb, 0xf6, 0xee,
		0xe4, 0xd8, 0xca, 0xbb, 0xab, 0x9a, 0x88, 0x77, 0x65, 0x54, 0x44, 0x35, 0x27, 0x1b, 0x11, 0x09,
		0x04, 0x01, 0x00, 0x02, 0x06, 0x0d, 0x16, 0x21,	0x2e, 0x3c, 0x4c, 0x5c, 0x6e, 0x7f,
};


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
#if (OS_TASK_NAME_EN > 0u)
CPU_INT08U os_err;
#endif
CPU_INT16U int_id;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  CPU_IntDis();
  for (int_id = CPU_INT_EXT0; int_id <= (EXT_INT_MAX_NBR - 1u); int_id++)
  {
	  /* Set all external intr. to KA interrupt priority boundary */
	  CPU_IntSrcPrioSet(int_id, CPU_CFG_KA_IPL_BOUNDARY, CPU_INT_KA);
  }
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  OSInit();

	OSTaskCreateExt( StartupTask,
					 0,
					 &StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1],
					 1,
					 1,
					 &StartupTaskStk[0],
					 APP_CFG_STARTUP_TASK_STK_SIZE,
					 0,
					 (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	#if (OS_TASK_NAME_EN > 0u)
		OSTaskNameSet( APP_CFG_STARTUP_TASK_PRIO,
		(INT8U *)"Startup task",
		&os_err);
	#endif

	OSTaskCreateExt( SenoTsk,
					 0,
					 &SenoTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1],
					 2,
					 2,
					 &SenoTaskStk[0],
					 APP_CFG_STARTUP_TASK_STK_SIZE,
					 0,
					 (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	#if (OS_TASK_NAME_EN > 0u)
		OSTaskNameSet( APP_CFG_STARTUP_TASK_PRIO,
		(INT8U *)"Seno Task",
		&os_err);
	#endif


	OSTaskCreateExt( PrimerSecuencia,
					 0,
					 &PrimerSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1],
					 3,
					 3,
					 &PrimerSecuenciaStk[0],
					 APP_CFG_STARTUP_TASK_STK_SIZE,
					 0,
					 (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	#if (OS_TASK_NAME_EN > 0u)
		OSTaskNameSet( APP_CFG_STARTUP_TASK_PRIO,
		(INT8U *)"Primer Secuencia",
		&os_err);
	#endif


	OSTaskCreateExt( SegundaSecuencia,
					 0,
					 &SegundaSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1],
					 4,
					 4,
					 &SegundaSecuenciaStk[0],
					 APP_CFG_STARTUP_TASK_STK_SIZE,
					 0,
					 (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	#if (OS_TASK_NAME_EN > 0u)
		 OSTaskNameSet( APP_CFG_STARTUP_TASK_PRIO,
		 (INT8U *)"Segunda Secuencia",
		 &os_err);
	#endif


	OSTaskCreateExt( TercerSecuencia,
					 0,
					 &TercerSecuenciaStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1],
					 5,
					 5,
					 &TercerSecuenciaStk[0],
					 APP_CFG_STARTUP_TASK_STK_SIZE,
					 0,
					 (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	#if (OS_TASK_NAME_EN > 0u)
		  OSTaskNameSet( APP_CFG_STARTUP_TASK_PRIO,
		  (INT8U *)"Tercer Secuencia",
		  &os_err);
	#endif


  DIOInit();
  OSStart();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB4 PB6
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*
*************************************************************************
* STM32Cube HAL FUNCTIONS
*************************************************************************
*/
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
/* define as empty to prevent the system tick being initialized before
    the OS starts */
 return (HAL_OK);
}

uint32_t HAL_GetTick(void)
{
 CPU_INT32U os_tick_ctr;

 #if (OS_VERSION >= 30000u)
  OS_ERR os_err;
  os_tick_ctr = OSTimeGet(&os_err);
 #else
  os_tick_ctr = OSTimeGet();
 #endif

 return os_tick_ctr;
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void StartupTask (void *p_arg){

	CPU_INT32U cpu_clk;
	(void)p_arg;
	cpu_clk = HAL_RCC_GetHCLKFreq();

	/* Initialize and enable System Tick timer */
	OS_CPU_SysTickInitFreq(cpu_clk);

	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();                                               /* Determine CPU capacity.                              */
	#endif

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);

	while (DEF_TRUE){
		switch (GetButton()) {
			case BOTON1:
				SuspendAllTasksExceptOne(SEC1);
				break;
			case BOTON2:
				SuspendAllTasksExceptOne(SEC2);
				break;
			case BOTON3:
				SuspendAllTasksExceptOne(SEC3);
				break;
			case BOTON4:
				SuspendAllTasksExceptOne(SENO);
				break;
			case BOTON5:
				SuspendAllTasksExceptOne(SENO);
				break;
			default:
				SuspendAllTasks();
				break;
		}
		OSTimeDly(1);
	}
}


static void SenoTsk (void *p_arg){

	CPU_INT32U cpu_clk;
	(void)p_arg;
	cpu_clk = HAL_RCC_GetHCLKFreq();

	OS_CPU_SysTickInitFreq(cpu_clk);

	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();
	#endif

	PinReset();

    DOCfgMode(LED1, DO_MODE_LOW, false);
    DOCfgMode(LED2, DO_MODE_LOW, false);
    DOCfgMode(LED3, DO_MODE_LOW, false);

	while (DEF_TRUE){
		UsbPrintf("Frencuencia Seno: %d Hz\n",valorFrecuenciaHz[frecuencia]);

		if(DIGet(3)){
			if(frecuencia < 4){
				frecuencia++;
			}
		}
		if(DIGet(4)){
			if(frecuencia > 0){
				frecuencia--;
			}
		}
		for(int i = 0; i < seno45; i++){
			for(int j = 0; j < 8; j++){
				salida[j] = (senoArreglo45[i] >> j) % 2;
				DOSet(j, salida[j]);
			}
			OSTimeDly(valorFrecuencia[frecuencia]);
		}
	}
}


static void PrimerSecuencia (void *p_arg){
	CPU_INT32U cpu_clk;
	(void)p_arg;
	cpu_clk = HAL_RCC_GetHCLKFreq();

	OS_CPU_SysTickInitFreq(cpu_clk);

	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();
	#endif


	while (DEF_TRUE){
	    DOCfgMode(LED1, DO_MODE_BLINK_ASYNC, false);
	    DOCfgBlink(LED1, DO_BLINK_EN, 99, 199);

	    DOCfgMode(LED2, DO_MODE_BLINK_ASYNC, false);
	    DOCfgBlink(LED2, DO_BLINK_EN, 199, 399);

	    DOCfgMode(LED3, DO_MODE_LOW, false);

	    OSTimeDly(1000);
	}
}


static void SegundaSecuencia (void *p_arg){
	CPU_INT32U cpu_clk;
	(void)p_arg;
	cpu_clk = HAL_RCC_GetHCLKFreq();

	OS_CPU_SysTickInitFreq(cpu_clk);

	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();
	#endif


	while (DEF_TRUE){
		DOCfgMode(LED1, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED1, DO_BLINK_EN, 99, 299);

		DOCfgMode(LED2, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED2, DO_BLINK_EN, 199, 399);

		DOCfgMode(LED3, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED3, DO_BLINK_EN, 299, 399);

		OSTimeDly(1000);
	}
}


static void TercerSecuencia (void *p_arg){
	CPU_INT32U cpu_clk;
	(void)p_arg;
	cpu_clk = HAL_RCC_GetHCLKFreq();

	OS_CPU_SysTickInitFreq(cpu_clk);

	#if (OS_TASK_STAT_EN > 0)
		OSStatInit();
	#endif

	while (DEF_TRUE){
		DOCfgMode(LED1, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED1, DO_BLINK_EN, 99, 199);

		DOCfgMode(LED2, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED2, DO_BLINK_EN, 149, 299);

		DOCfgMode(LED3, DO_MODE_BLINK_ASYNC, false);
		DOCfgBlink(LED3, DO_BLINK_EN, 199, 349);

		OSTimeDly(1000);
	}
}

/*
**************************************************************************************************************************
*                                               UsbPrintfMsg()
*
* Description :
* Argument(s) : none
* Return(s)   : none.
* Caller(s)   :
* Note(s)     : none.
**************************************************************************************************************************
*/
void UsbPrintf (CPU_CHAR  *p_fmt, ...)
{
    CPU_CHAR    str[80u + 1u];
    CPU_SIZE_T  len;
    va_list     vArgs;

    va_start(vArgs, p_fmt);

    vsprintf((char       *)str,
             (char const *)p_fmt,
                           vArgs);

    va_end(vArgs);

    len = strlen(str);

    CDC_Transmit_FS((uint8_t *)str, len);
}

int GetButton(){
	int boton;

	if(DIGet(BOTON1)){
		boton = BOTON1;
	}else if(DIGet(BOTON2)){
		boton = BOTON2;
	}else if(DIGet(BOTON3)){
		boton = BOTON3;
	}else if(DIGet(BOTON4)){
		boton = BOTON4;
	}else if(DIGet(BOTON5)){
		boton = BOTON5;
	}else
		boton = DEFAULT;

	return boton;
}

void PinReset(){
	for (int pin = 0; pin < 8; pin++) {
		DOSet(pin, 0);
	}
}

void SuspendAllTasks(){
	for (int task = 2; task < 6; task++) {
		OSTaskSuspend(task);
	}
}

void SuspendAllTasksExceptOne(int TaskID){

	OSTaskResume(TaskID);

	for (int task = 2; task < 6; task++) {
		if(task != TaskID){
			OSTaskSuspend(task);
		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
