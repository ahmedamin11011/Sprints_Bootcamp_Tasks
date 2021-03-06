#include"Dio.h"
#include "DIO.h"

/* This function can set the direction of a full port, a nibble  or even one pin*/

ERROR_STATUS DIO_init(DIO_Cfg_s *gpstrDIO_info)
{
	ERROR_STATUS E_STAT = E_NOK;
	uint8 au8_temp_reg;
	uint8 au8_Masked_Pins;
	if (gpstrDIO_info != NULL)
	{
		switch (gpstrDIO_info->GPIO)
		{
			case GPIOA:
			{
				au8_temp_reg = PORTA_DIR & ~(gpstrDIO_info->pins);
				au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
				PORTA_DIR= au8_temp_reg |au8_Masked_Pins;
				E_STAT = E_OK;
				break;
			}
			case GPIOB:
			{
				au8_temp_reg = PORTB_DIR & ~(gpstrDIO_info->pins);
				au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
				PORTB_DIR= au8_temp_reg |au8_Masked_Pins;
				E_STAT = E_OK;
				break;
			}
			case GPIOC:
			{
				au8_temp_reg = PORTC_DIR & ~(gpstrDIO_info->pins);
				au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
				PORTC_DIR= au8_temp_reg |au8_Masked_Pins;
				E_STAT = E_OK;
				break;
			}
			case GPIOD:
			{
				au8_temp_reg = PORTD_DIR & ~(gpstrDIO_info->pins);
				au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
				PORTD_DIR= au8_temp_reg |au8_Masked_Pins;
				E_STAT = E_OK;
				break;
			}
			default:	E_STAT= E_NOK; break;
		}
	}
	else
	{
		E_STAT= E_NOK;
	}
	return E_STAT;
}

/*This function can set the value of a full port, a nibble or even one pin*/
ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value)
{
	ERROR_STATUS E_STAT = E_NOK;
	uint8 au8_temp_reg;
	uint8 au8_Masked_Pins;
	switch (GPIO)
	{
		case GPIOA:
		{
			au8_temp_reg = PORTA_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTA_DATA= au8_temp_reg |au8_Masked_Pins;
			E_STAT = E_OK;
			break;
		}
		case GPIOB:
		{
			au8_temp_reg = PORTB_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTB_DATA= au8_temp_reg |au8_Masked_Pins;
			E_STAT = E_OK;
			break;
		}
		case GPIOC:
		{
			au8_temp_reg = PORTC_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTC_DATA= au8_temp_reg |au8_Masked_Pins;
			E_STAT = E_OK;
			break;
		}
		case GPIOD:
		{
			au8_temp_reg = PORTD_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTD_DATA= au8_temp_reg |au8_Masked_Pins;
			E_STAT = E_OK;
			break;
		}
		default: E_STAT= E_NOK;	break;
	}
	return E_STAT;
}

/*This function gets the value of a full port, a nibble or even one pin*/
ERROR_STATUS DIO_Read_ (uint8 GPIO,uint8 pins, uint8 *data)
{
	ERROR_STATUS E_STAT = E_NOK;
	switch (GPIO)
	{
		case (GPIOA):
		 *data= PORTA_PIN & (pins);
		 E_STAT = E_OK;
		  break;
		case (GPIOB): 
		*data= PORTB_PIN & (pins);
		 E_STAT = E_OK;
		  break;
		case (GPIOC):
		 *data= PORTC_PIN & (pins);
		  E_STAT = E_OK;
		   break;
		case (GPIOD): *data= PORTD_PIN & (pins);
		 E_STAT = E_OK;
		  break;
		default:
			E_STAT=E_NOK;
			 break;
	}
	return E_STAT;
}

/* This function toggles the value of a full port, a nibble or even one pin */
ERROR_STATUS DIO_Toggle_ (uint8 GPIO, uint8 pins)
{
	ERROR_STATUS E_STAT = E_NOK;
	switch (GPIO)
	{
		case GPIOA:
		 PORTA_DATA^=pins;
		 E_STAT = E_OK;
		  break;
		case GPIOB:
		 PORTB_DATA^=pins;
		  E_STAT = E_OK;
		   break;
		case GPIOC:
		 PORTC_DATA^=pins;
		  E_STAT = E_OK;
		   break;
		case GPIOD:
		 PORTD_DATA^=pins;
		  E_STAT = E_OK;
		   break;
		default:
			E_STAT= E_NOK;
			 break;
	}
	return E_STAT;
}