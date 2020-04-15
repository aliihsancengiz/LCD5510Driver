#ifndef _LCD5510
#define _LCD5510

/*
	Name: LCD5510 Driver
	Copyright: Under The GNU General Public License v3.0
	Author: Ali ihsan Cengiz
	Date: 15.04.20 09:56
	Description: LCD Driver for Stm32f4  
*/

#include "main.h"
#include "Font.h"

extern SPI_HandleTypeDef hspi2;

/*
*   @Brief      :Send a command to the LCD usually these commands control the LCD
*   @Param[cmd] :Command to send 
*/
void writeCommand(uint8_t cmd)
{
  HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,&cmd,1,100);
  HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_SET);
}



/*
*   @Brief      :Send a data to the LCD
*   @Param[data] :data to send 
*/
void writeData(uint8_t data)
{
  HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
  HAL_SPI_Transmit(&hspi2,&data,1,100);
  HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_SET);
}


/*
*   @Brief  :Reset the LCD by drawing RST pin to low
*   @Param  :None
*   @returm :None
*/
void LCD_Reset()
{
  HAL_GPIO_WritePin(Reset_LCD_GPIO_Port,Reset_LCD_Pin,GPIO_PIN_RESET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(Reset_LCD_GPIO_Port,Reset_LCD_Pin,GPIO_PIN_SET);
}

/*
*   @Brief  :set the LCD current Position to the (X,Y) pair
*/
void LCD_Set_Postion(uint8_t PosX, uint8_t PosY) {
  writeCommand(0x40 | PosY);
  writeCommand(0x80 | PosX);
}



/*
*   @brief :Clear the LCD by writing to all pixel 0
*/
void LCD_Clear(void) {
  uint8_t t;
  uint8_t k;
  LCD_Set_Postion(0,0);
  for(t=0;t<6;t++)
  {
    for(k=0;k<84;k++)
    {
      writeData(0x00);
    }
  }
}

/*
*   @Brief : Write a character by using font table
*/
void LCD_Write_Char(uint8_t ch) {
  uint8_t line;
  ch -= 32;
  for (line=0; line<6; line++) writeData(font6x8[ch][line]);
}

/*
* @Brief : Send A string to the Specified position
*/
void LCD_Write_String(uint8_t PosX, uint8_t PosY, char * str) {
  LCD_Set_Postion(PosX, PosY);
  while(* str) {
    LCD_Write_Char(* str);
    str ++;
  }
}

/*
*   @Brief :Initialize the LCD 
*/
void LCD_Init()
{
  LCD_Reset();          //Reset LCD 
  writeCommand(0x21);   //Set Instruction Mode to extended
  writeCommand(0xD0);   //write VOP to register
  writeCommand(0x20);   //Set Instruction Mode to basic
  writeCommand(0x0C);   //Set Display Configuration to normal mode
  LCD_Clear();
}


/*
*   @Brief : Set Inverse Video Mode
*/
void makeInverseVideoMode()
{
    writeCommand(0x0D);
}

/*
*   @Brief : Set Normal Video Mode
*/
void makeNormalVideoMode()
{
    writeCommand(0x0C);
}

#endif