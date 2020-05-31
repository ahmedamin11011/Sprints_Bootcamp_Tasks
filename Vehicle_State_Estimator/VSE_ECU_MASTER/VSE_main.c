/*
 * VSE_main.c
 *
 *  Created on: Feb 13, 2020
 *      Author: Amin, Joo
 */


#include "gpio.h"
#include "LCD.h"
#include "pushButton.h"
#include "SPI.h"
#include "UART.h"
#include "led.h"
#include "timers.h"
#include <stdlib.h>

#define T1_ONE_SEC_OUTPUT_COMPARE_VALUE 62500

uint8_t gu8_flag = 0;
uint8_t gu8_currentSpeed;

void test(void)
{
	gu8_flag = 1;
}

void test_uart(void)
{
	gu8_currentSpeed = UART_receive();
	LCD_goToRowColumn(0, 0);
	LCD_displayInteger(gu8_currentSpeed);
}

int main(void)
{
	uint8_t au8_alreadyStartedFlag = 0;

	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);

	UART_ConfigType uart_configtype = {
			UART_ASYNCHRONOUS_MODE,
			UART_RECEIVER_MODE,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_ENABLED
	};

	SPI_ConfigType spi_configtype = {
			SPI_MASTER,
			SPI_INTERRUPT_DISABLED,
			SPI_F_OSC_4
	};

	UART_RXC_setCallBack(&test_uart);
	UART_init(&uart_configtype);

	SPI_init(&spi_configtype);

	gpioPinDirection(GPIOC, BIT0 | BIT1, INPUT);
	gpioPinWrite(GPIOC, BIT0 | BIT1, HIGH);

	timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1_DIS, T1_PRESCALER_256, 0, T1_ONE_SEC_OUTPUT_COMPARE_VALUE, 0, 0, T1_INTERRUPT_CMP_1A);
	Timer1_CTC_A_setCallBack(&test);

	sei();

	while(1)
	{
		if(gpioPinRead(GPIOC, BIT0) == 1 && au8_alreadyStartedFlag == 0)
		{
			timer1Start();
			SPI_sendByte(gu8_currentSpeed);
			au8_alreadyStartedFlag = 1;
		}

		if(gpioPinRead(GPIOC, BIT1) == 1)
		{
			timer1Stop();
			au8_alreadyStartedFlag = 0;
		}

		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			while(pushButtonGetStatus(BTN_0) == Pressed);
			gu8_currentSpeed++;
		}

		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			while(pushButtonGetStatus(BTN_1) == Pressed);
			gu8_currentSpeed--;
		}

		if(gu8_flag == 1)
		{
			SPI_sendByte(gu8_currentSpeed);
			gu8_flag = 0;
		}
	}
}

