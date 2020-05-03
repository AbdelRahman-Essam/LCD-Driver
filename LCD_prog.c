#include "std_types.h"
#include "utils.h"
#include <util/delay.h>

#include "DIO_int.h"

#include "LCD_priv.h"
#include "LCD_config.h"
#include "LCD_int.h"

void LCD_voidInit(void)
{
    DIO_voidInit();

    LCD_voidSendCommand(RETURN_CURSOR_TO_HOME);             /* Returns the cursor to the home position (Address 0). */
	#if (DATA_BITS_MODE == 4)
		LCD_voidSendCommand(TWO_LINE_LCD_Four_BIT_MODE);  /* 2-line LCD + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
	#endif

	LCD_voidSendCommand(CURSOR_OFF);                     /* cursor off */
	LCD_voidSendCommand(CLEAR_COMMAND);                  /* Clear LCD at the beginning */
}

void LCD_voidSendCommand(u8 command)
{
    DIO_voidSetPin(LCD_RS, DIO_LOW);     /* Instruction register selected, LCD_RS=0 */
	DIO_voidSetPin(LCD_RW, DIO_LOW); /* Write data to LCD, LCD_RW=0 */
	_delay_ms(1);

	DIO_voidSetPin(LCD_EN, DIO_HIGH);    /* Enable LCD, LCD_EN=1 */
	_delay_ms(1);

	#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			DIO_voidSetPort(LCD_DATA_PORT, (command & 0xF0));
		#else
            DIO_voidSetPort(LCD_DATA_PORT, (command >> 4) & 0x0F);
		#endif

		_delay_ms(1);

		DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);

        /* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
		DIO_voidSetPin(LCD_EN, DIO_HIGH); /* Enable LCD, LCD_EN=1 */
		_delay_ms(1);

		#ifdef UPPER_PORT_PINS
            DIO_voidSetPort(LCD_DATA_PORT, (command << 4) & 0xF0);
		#else
            DIO_voidSetPort(LCD_DATA_PORT, (command & 0x0F));
		#endif

		_delay_ms(1);

        DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);

	#elif (DATA_BITS_MODE == 8)
        DIO_voidSetPort(LCD_DATA_PORT, command);
		_delay_ms(1);
		DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);
	#endif

}

void LCD_voidDisplayCharacter(u8 data)
{
    DIO_voidSetPin(LCD_RS, DIO_HIGH);     /* Data register selected, LCD_RS=1 */
	DIO_voidSetPin(LCD_RW, DIO_LOW); /* Write data to LCD, LCD_RW=0 */
	_delay_ms(1);

	DIO_voidSetPin(LCD_EN, DIO_HIGH);    /* Enable LCD, LCD_EN=1 */
	_delay_ms(1);

		#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			DIO_voidSetPort(LCD_DATA_PORT, (data & 0xF0));
		#else
            DIO_voidSetPort(LCD_DATA_PORT, (data >> 4) & 0x0F);
		#endif

		_delay_ms(1);

		DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);

        /* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
		DIO_voidSetPin(LCD_EN, DIO_HIGH); /* Enable LCD, LCD_EN=1 */
		_delay_ms(1);

		#ifdef UPPER_PORT_PINS
            DIO_voidSetPort(LCD_DATA_PORT, (data << 4) & 0xF0);
		#else
            DIO_voidSetPort(LCD_DATA_PORT, (data & 0x0F));
		#endif

		_delay_ms(1);

        DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);

	#elif (DATA_BITS_MODE == 8)
        DIO_voidSetPort(LCD_DATA_PORT, data);
		_delay_ms(1);
		DIO_voidSetPin(LCD_EN, DIO_LOW); /* Disable LCD, LCD_EN=0 */
		_delay_ms(1);
	#endif
}

void LCD_voidDisplayString(const u8 *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_voidDisplayCharacter(Str[i]);
		i++;
	}
}

void LCD_voidClearScreen(void)
{
    LCD_voidSendCommand(CLEAR_COMMAND);
}

void LCD_voidDisplayStringRowColumn(u8 row,u8 col,const u8 *Str)
{
    LCD_voidGoToRowColumn(row,col);
	LCD_voidDisplayString(Str);

}

void LCD_voidGoToRowColumn(u8 row,u8 col)
{
    u8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;

	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_voidSendCommand(Address | SET_CURSOR_LOCATION);
}
