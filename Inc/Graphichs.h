#ifndef _MYGRAPHICS_
#define _MYGRAPHICS_

#include "LCD5510.h"

/*
	Name: LCD5510 Basic Graphic Library
	Copyright: Under The GNU General Public License v3.0
	Author: Ali ihsan Cengiz
	Date: 15.04.20 09:56
	Description: Basic graphics Function like draw H,V lines,rectangles
*/




/*
*   @Brief : Draw a Horizontal line with starting(x0,y0) and has a length len
*
*/
void drawHLine(uint8_t x0,uint8_t y0,uint8_t len)
{
    if((x0<0) || (x0>84) || (y0<0) ||(y0>84))
    {
        x0=0;
        y0=0;
    }
    if(len < 0)
    {
        len+=84;
    }
    else if(len > 84)
    {
        len-=84;
    }
    for (size_t i = 0; i < len; i++)
    {
        LCD_Set_Postion(x0+i,y0);
        writeData(0x01);
    }
}


/*
*   @Brief : Draw a Vertical line with starting(x0,y0) and has a length len
*/
void drawVLine(uint8_t x0,uint8_t y0,uint8_t len)
{
    if((x0<0) || (x0>84) || (y0<0) ||(y0>84))
    {
        x0=0;
        y0=0;
    }
    for (size_t i = 0; i < len; i++)
    {
        LCD_Set_Postion(x0,y0+i);
        writeData(0xFF);
    }

}


/*
*   @Brief Draw a rectangle between(x0,y0) (x1,y1) points
*/
void drawRectangle(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1)
{
    drawHLine(x0,y0,(x1-x0));
    drawVLine(x0,y0,(y1-y0));
    drawHLine(x0,y1,(x1-x0));
    drawVLine(x1,y0,(y1-y0));
}
#endif