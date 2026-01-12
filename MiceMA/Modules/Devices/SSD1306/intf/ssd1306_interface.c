/*
    MIT License

    Copyright (c) 2017-2018, Alexey Dynda

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

#include <intf/ssd1306_interface.h>

#include <stdio.h>
#include <stddef.h>
#include <string.h>

uint8_t  display_buf[1025];
uint16_t display_cnt;
//static void ssd1306_send_buffer_generic(const uint8_t* buffer, uint16_t size);

ssd1306_interface_t ssd1306_intf =
{
    //.send_buffer = ssd1306_send_buffer_generic
};

void ssd1306_commandStart(void)
{
    //ssd1306_intf.start();
    //ssd1306_intf.send(0x00);
}

void ssd1306_sendDataStart(void)
{
	display_cnt = 0;
	display_buf[display_cnt++] = 0x40;
	//ssd1306_intf.start();
    //ssd1306_intf.send(0x40);
}

void ssd1306_sendCommand(uint8_t command)
{
	uint8_t buf[5];

	buf[0] = 0x00;
	buf[1] = command;

    ssd1306_intf.send_buffer(buf, 2);
}

void ssd1306_sendCommands(const uint8_t* buffer, uint16_t size)
{
	//uint8_t buf[20];

	//printf("commands Size over %d\n", size);
	//buf[0] = 0x00;
    //memcpy(&buf[1], buffer, size);
    ssd1306_intf.send_buffer(buffer, size );
}


void ssd1306_sendData(const uint8_t data)
{
//	uint8_t buf[5];

//	buf[0] = 0x40;
//	buf[1] = data;

	//display_buf[display_cnt ++] =  0x40;
	display_buf[display_cnt ++] =  data;
//    ssd1306_intf.send_buffer(buf, 2);
}


void ssd1306_sendWordData(const uint16_t data)
{
//	uint8_t buf[5];

	display_buf[display_cnt ++] =  (data >> 8) & 0x00ff;
	display_buf[display_cnt ++] =   data       & 0x00ff;


//	printf("word %x\n", data);
//	buf[0] = 0x40;
//	buf[1] = (data >> 8) & 0x00ff;
//	buf[2] =  data & 0x00ff;

//  ssd1306_intf.send_buffer(buf, 3);
}


void ssd1306_sendDatas(const uint8_t* buffer, uint16_t size)
{
    memcpy(&display_buf[display_cnt], buffer, size);
    display_cnt += size;
}

void ssd1306_sendDataFinish(void)
{
	 if( display_cnt < 2 ) return;
     ssd1306_intf.send_buffer(display_buf, display_cnt);
     //printf("count = %d \n", display_cnt);
     display_cnt = 0;
}

/*
void ssd1306_sendDatas(const uint8_t* buffer, uint16_t size)
{
	uint8_t buf[100];

	printf("datas Size over %d\n", size);
	if(  size > 100) {
		printf("Size over \n");
		return;
	}
	buf[0] = 0x40;
    memcpy(&buf[1], buffer, size);

    //ssd1306_commandStart();
    ssd1306_intf.send_buffer(buf, size+1);
    //ssd1306_intf.stop();
}
*/
/*
void ssd1306_send_buffer_generic(const uint8_t* buffer, uint16_t size)
{
    while (size--)
    {
        ssd1306_intf.send(*buffer);
        buffer++;
    }
}
*/
