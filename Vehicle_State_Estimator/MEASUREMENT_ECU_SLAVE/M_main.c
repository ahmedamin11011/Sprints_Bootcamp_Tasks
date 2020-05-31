/*
 * M_main.c
 *
 *  Created on: Feb 13, 2020
 *      Author: Amin, Joo
 */


#include "gpio.h"
#include "LCD.h"
#include "pushButton.h"
#include "SPI.h"
#include "UART.h"
#include "timers.h"
#include <stdlib.h>

uint8_t gu8_currentSpeed = 0;
uint8_t gu8_time = 0;
uint16_t gu16_distance = 0;
sint8_t gas8_str[5];


void test(void)
{
	gu8_currentSpeed = SPI_receiveByte();
	gu8_time++;
	gu16_distance += gu8_currentSpeed;
}

int main(void)
{
	uint8_t au8_totalDistance;

	gpioPinDirection(GPIOC, BIT0 | BIT1, OUTPUT);

	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);

	UART_ConfigType uart_configtype = {
			UART_ASYNCHRONOUS_MODE,
			UART_SENDER_MODE,
			UART_EIGHT_BITS,
			UART_PARITY_DISABLED,
			UART_ONE_STOP_BIT,
			UART_INTERRUPT_DISABLED
	};

	SPI_ConfigType spi_configtype = {
			SPI_SLAVE,
			SPI_INTERRUPT_ENABLED,
			SPI_F_OSC_4
	};

	LCD_init();

	UART_init(&uart_configtype);
	SPI_init(&spi_configtype);

	SPI_setCallBack(&test);

	sei();

	while(1)
	{
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			gu8_time = 0;
			gu16_distance = 0;
			gu8_currentSpeed = 0;
			while(pushButtonGetStatus(BTN_0) == Pressed);
			gpioPinWrite(GPIOC, BIT0, HIGH);
		}else if(pushButtonGetStatus(BTN_0) == Released)
		{
			gpioPinWrite(GPIOC, BIT0, LOW);
		}

		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			while(pushButtonGetStatus(BTN_1) == Pressed);
			gpioPinWrite(GPIOC, BIT1, HIGH);

            UART_Send_String("time = ");
			itoa((gu8_time), gas8_str, 10);
			UART_Send_String(gas8_str);
			UART_Send_String(" sec");
			UART_transmit('\r');

			UART_Send_String("distance = ");
			au8_totalDistance = gu16_distance - (gu8_time-1) * '0';
            itoa((au8_totalDistance - '0'), gas8_str, 10);
            UART_Send_String(gas8_str);
			UART_Send_String(" m");
			UART_transmit('\r');

			UART_Send_String("speed = ");
			itoa((gu8_currentSpeed - '0'), gas8_str, 10);
			UART_Send_String(gas8_str);
			UART_Send_String(" m/s");
			UART_transmit('\r');
			UART_transmit('\r');
		}else if(pushButtonGetStatus(BTN_1) == Released)
		{
			gpioPinWrite(GPIOC, BIT1, LOW);
		}
	}
}
