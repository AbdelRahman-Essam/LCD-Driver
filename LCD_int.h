#ifndef LCD_INT_H_
#define LCD_INT_H_

#include"STD_TYPES.h"

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 command);
void LCD_voidDisplayCharacter(u8 data);
void LCD_voidDisplayString(const u8 *Str);
void LCD_voidClearScreen(void);
void LCD_voidDisplayStringRowColumn(u8 row,u8 col,const u8 *Str);
void LCD_voidGoToRowColumn(u8 row,u8 col);

#endif /* LCD_INT_H_ */
