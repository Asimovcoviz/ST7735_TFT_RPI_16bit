/*!
	@file     ST7735_TFT_graphics.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_RPI graphics library.
			  This file handles the graphic methods 	
*/

#pragma once


// Section: Includes 
#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ST7735_TFT_Print.hpp"  //custom

// Section defines 

#define _swap_TFT(a, b) { int16_t t; t = a; a = b; b = t;}

/*!
	@brief Class to handle fonts and graphics of ST7735 display
*/
class ST7735_TFT_graphics : public Print {

 public:

	ST7735_TFT_graphics(); // Constructor
	~ST7735_TFT_graphics(){};
	
		/*! Font type 1-8 */
	enum TFT_Font_Type_e : uint8_t	
	{
		TFTFont_Default = 1,    /**< Default Font, Full extended ASCII */
		TFTFont_Thick = 2,      /**< Thick font , no lower case letters*/
		TFTFont_Seven_Seg = 3,  /**< Seven Segment Font */
		TFTFont_Wide = 4,       /**< Wide font no lowercase letters*/
		TFTFont_Tiny = 5,       /**< Tiny font */
		TFTFont_HomeSpun = 6,   /**< HomeSpun Font */
		TFTFont_Bignum = 7,     /**< Bignum numbers only */
		TFTFont_Mednum = 8      /**< Mednum number only */
	}; 

	/*! Width of the font in bits each representing a bytes sized column*/
	enum TFT_Font_width_e : uint8_t	
	{
		TFTFont_width_3 = 3,   /**< 3 tiny font */
		TFTFont_width_4 = 4,   /**< 4 seven segment font */
		TFTFont_width_5 = 5,   /**< 5 default font */
		TFTFont_width_7 = 7,   /**< 7 homespun & thick font*/
		TFTFont_width_8 = 8,   /**< 8 wide font */
		TFTFont_width_16  = 16 /**< Big and Medium number  font */
	}; 

	/*! font offset in the ASCII table*/
	enum TFT_Font_offset_e : uint8_t	
	{
		TFTFont_offset_none = 0x00,  /**< extended ASCII */
		TFTFont_offset_space = 0x20, /**< Starts at Space */
		TFTFont_offset_zero = 0x30   /**< Starts at zero */
	}; 

	/*! Height of the font in bits*/
	enum TFT_Font_height_e : uint8_t
	{
		TFTFont_height_8 = 8,  /**< 8 font  1-6 at size 1*/
		TFTFont_height_16 = 16, /**< 16 font 8 */
		TFTFont_height_32 = 32  /**< 32 font 7 */
	}; 
	
	virtual size_t write(uint8_t);
	void TFTsetAddrWindow(uint16_t, uint16_t, uint16_t, uint16_t);
	void TFTfillScreen(uint16_t color);
	void TFTsetCursor(int16_t x, int16_t y);
	
	// Shapes and lines
	void TFTdrawPixel(uint16_t, uint16_t, uint16_t);
	void TFTdrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void TFTdrawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
	void TFTdrawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);

	void TFTdrawRectWH(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
	void TFTfillRectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
	void TFTfillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

	void TFTdrawRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	void TFTfillRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
	
	void TFTdrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void TFTfillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	void TFTdrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void TFTfillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

	// Text
	void TFTsetTextWrap(bool w);
	void TFTFontNum(TFT_Font_Type_e FontNumber);
	void TFTdrawChar(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size);
	void TFTdrawText(uint16_t x, uint16_t y, char *_text, uint16_t color, uint16_t bg, uint8_t size);
	void TFTdrawCharNumFont(uint16_t x, uint16_t y, uint8_t c, uint16_t color ,uint16_t bg);
	void TFTdrawTextNumFont(uint16_t x, uint16_t y, char *pText, uint16_t color, uint16_t bg);
	void setTextColor(uint16_t c);
	void setTextColor(uint16_t c, uint16_t bg);
	void setTextSize(uint8_t s);
	
	// Bitmap & Icon
	void TFTdrawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t color, uint16_t bgcolor, const unsigned char character[]);
	void TFTdrawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, uint16_t bgcolor, uint8_t *pBmp);
	void TFTdrawBitmap24(uint16_t x, uint16_t y, uint8_t *pBmp, char w, char h);
	void TFTdrawBitmap16(uint16_t x, uint16_t y, uint8_t *pBmp, char w, char h);
	
	
protected:

	void pushColor(uint16_t color);
	int16_t Color565(int16_t ,int16_t , int16_t );
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
	
	void writeCommand(uint8_t);
	void writeData(uint16_t);
	void spiWrite(uint16_t);
	void spiWriteSoftware(uint16_t spidata);
	void spiWriteDataBuffer(uint8_t* spidata, uint32_t len);
	void spiWriteDataBuffer(uint16_t* spidata, uint32_t len);
	
	bool _hardwareSPI=true; /**< True for Hardware SPI on , false fpr Software SPI on*/
	
	uint8_t _FontNumber = TFTFont_Default;            /**< Store current font */
	uint8_t _CurrentFontWidth = TFTFont_width_5;      /**< Store current font width */
	uint8_t _CurrentFontoffset = TFTFont_offset_none; /**< Store current offset width */
	uint8_t _CurrentFontheight = TFTFont_height_8;    /**< Store current offset height */
	
	bool _wrap = true;				/**< wrap text around the screen on overflow*/
	uint16_t _textcolor =0xFFFF ;   /**< ForeGround color for text*/
	uint16_t _textbgcolor =0x0000 ; /**< BackGround color for text*/
	uint8_t _textSize = 1;          /**< Size of text , fonts 1-6 only*/
	
	uint8_t _currentMode = 0; //TFT mode 
	int16_t _cursorX = 0; 
	int16_t _cursorY = 0;
	
	uint8_t _colstart; 
	uint8_t  _rowstart;
	uint8_t _XStart; 
	uint8_t _YStart;
	
	uint16_t _widthTFT;
	uint16_t _heightTFT;
	uint16_t _widthStartTFT; //  never change after first init
	uint16_t _heightStartTFT; // never change after first init
	
	int8_t _TFT_DC;
	int8_t _TFT_RST;
	int8_t _TFT_CS;    // Software SPI only
	int8_t _TFT_SCLK; // Software SPI only
	int8_t _TFT_SDATA;  // Software SPI only

};

// ********************** EOF *********************
