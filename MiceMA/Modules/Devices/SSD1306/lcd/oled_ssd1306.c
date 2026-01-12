/*
    MIT License

    Copyright (c) 2017-2019, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <lcd/oled_ssd1306.h>

#include <intf/i2c/ssd1306_i2c.h>
#include <intf/ssd1306_interface.h>
#include <lcd/lcd_common.h>
#include <lcd/ssd1306_commands.h>
#include <ssd1306_hal/io.h>


uint8_t s_ssd1306_startLine = 0;

static const uint8_t PROGMEM s_oled128x64_initData[] =
{
    0x00,  // command mode
    SSD1306_DISPLAYOFF, // display off
    SSD1306_MEMORYMODE, HORIZONTAL_ADDRESSING_MODE, // Page Addressing mode
    SSD1306_COMSCANDEC,             // Scan from 127 to 0 (Reverse scan)
    SSD1306_SETSTARTLINE | 0x00,    // First line to start scanning from
    SSD1306_SETCONTRAST, 0x7F,      // contast value to 0x7F according to datasheet
    SSD1306_SEGREMAP | 0x01,        // Use reverse mapping. 0x00 - is normal mapping
    SSD1306_NORMALDISPLAY,
    SSD1306_SETMULTIPLEX, 63,       // Reset to default MUX. See datasheet
    SSD1306_SETDISPLAYOFFSET, 0x00, // no offset
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,// set to default ratio/osc frequency
    SSD1306_SETPRECHARGE, 0x22,     // switch precharge to 0x22 // 0xF1
    SSD1306_SETCOMPINS, 0x12,       // set divide ratio
    SSD1306_SETVCOMDETECT, 0x20,    // vcom deselect to 0x20 // 0x40
    SSD1306_CHARGEPUMP, 0x14,       // Enable charge pump
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_DISPLAYON,
};


static void ssd1306_setBlock(lcduint_t x, lcduint_t y, lcduint_t w)
{
	uint8_t buf[10];

	buf[0] = 0x00; // command mode
	buf[1] = SSD1306_COLUMNADDR;
	buf[2] = x;
	buf[3] = w ? (x + w - 1) : (ssd1306_lcd.width - 1);
	buf[4] = SSD1306_PAGEADDR;
	buf[5] = y;
	buf[6] = (ssd1306_lcd.height >> 3) - 1;

	ssd1306_sendCommands(buf, 7);

	/*
    ssd1306_intf.start();
    ssd1306_intf.send(0x00);
    ssd1306_intf.send(SSD1306_COLUMNADDR);
    ssd1306_intf.send(x);
    ssd1306_intf.send(w ? (x + w - 1) : (ssd1306_lcd.width - 1));
    ssd1306_intf.send(SSD1306_PAGEADDR);
    ssd1306_intf.send(y);
    ssd1306_intf.send((ssd1306_lcd.height >> 3) - 1);
    ssd1306_intf.stop();
    ssd1306_intf.start();
    ssd1306_intf.send(0x40);
    */
}

static void ssd1306_nextPage(void)
{
}

static void ssd1306_setMode_int(lcd_mode_t mode)
{
}

void ssd1306_displayOff()
{
    ssd1306_sendCommand(SSD1306_DISPLAYOFF);
}


void ssd1306_displayOn()
{
    ssd1306_sendCommand(SSD1306_DISPLAYON);
}

void ssd1306_setContrast(uint8_t contrast)
{
	uint8_t buf[10];

	buf[0] = 0x00; // command mode
	buf[1] = SSD1306_SETCONTRAST;
	buf[2] = contrast;

	ssd1306_sendCommands(buf, 3);

//    ssd1306_commandStart();
//    ssd1306_intf.send(SSD1306_SETCONTRAST);
//    ssd1306_intf.send(contrast);
//    ssd1306_intf.stop();
}

void ssd1306_invertMode()
{
    ssd1306_sendCommand(SSD1306_INVERTDISPLAY);
}

void ssd1306_normalMode()
{
    ssd1306_sendCommand(SSD1306_NORMALDISPLAY);
}

void ssd1306_flipHorizontal(uint8_t mode)
{
    ssd1306_sendCommand( SSD1306_SEGREMAP | (mode ? 0x00: 0x01 ) );
}

void ssd1306_flipVertical(uint8_t mode)
{
    ssd1306_sendCommand( mode ? SSD1306_COMSCANINC : SSD1306_COMSCANDEC );
}

void ssd1306_setStartLine(uint8_t line)
{
    s_ssd1306_startLine = line;
    ssd1306_sendCommand( SSD1306_SETSTARTLINE | (line & 0x3F) );
}

uint8_t ssd1306_getStartLine(void)
{
    return s_ssd1306_startLine;
}

///////////////////////////////////////////////////////////////////////////////
//  I2C SSD1306 128x64
///////////////////////////////////////////////////////////////////////////////

void    ssd1306_init()
{
    ssd1306_128x64_i2c_init();
}


void    ssd1306_128x64_init()
{
    ssd1306_lcd.type = LCD_TYPE_SSD1306;
    ssd1306_lcd.height = 64;
    ssd1306_lcd.width = 128;
    ssd1306_lcd.set_block = ssd1306_setBlock;
    ssd1306_lcd.next_page = ssd1306_nextPage;
    ssd1306_lcd.send_pixels1   = ssd1306_sendData;
    ssd1306_lcd.send_pixels8   = ssd1306_sendData;
    ssd1306_lcd.send_pixels16  = ssd1306_sendWordData;
   // ssd1306_lcd.send_pixels_buffer1 = ssd1306_intf.send_buffer;
    ssd1306_lcd.set_mode = ssd1306_setMode_int;
    ssd1306_lcd.data_start = ssd1306_sendDataStart;
    ssd1306_lcd.data_finish = ssd1306_sendDataFinish;

    ssd1306_sendCommands((uint8_t *) &s_oled128x64_initData[0], sizeof(s_oled128x64_initData));
    //for( uint8_t i=0; i<sizeof(s_oled128x64_initData); i++)
    //{
    //        ssd1306_sendCommand(pgm_read_byte(&s_oled128x64_initData[i]));
    //}
}

void    ssd1306_128x64_i2c_init()
{
    ssd1306_i2cInit();
    ssd1306_128x64_init();
}

void    ssd1306_128x64_i2c_initEx(int8_t scl, int8_t sda, int8_t sa)
{
    ssd1306_i2cInitEx(scl, sda, sa);
    ssd1306_128x64_init();
}


