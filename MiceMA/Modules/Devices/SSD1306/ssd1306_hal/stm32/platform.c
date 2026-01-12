/*
    MIT License

    Copyright (c) 2018, Alexey Dynda

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

#include <stdio.h>

#include <ssd1306_hal/io.h>

#if defined(SSD1306_STM32_PLATFORM)

#include <intf/ssd1306_interface.h>
#include <stm32f4xx_hal.h>

extern I2C_HandleTypeDef hi2c1;
// TODO: To add support. Any help is welcome

////////////////////////////////////////////////////////////////////////////////////////
// !!! PLATFORM I2C IMPLEMENTATION OPTIONAL !!!
void print_i2c_error();

static uint8_t s_i2c_addr = 0x3C;
uint8_t i2c_err_;



static void platform_i2c_start(void)
{
    // ... Open i2c channel for your device with specific s_i2c_addr
}

static void platform_i2c_stop(void)
{
    // ... Complete i2c communication
}

/*
static void platform_i2c_send(uint8_t data)
{
    // ... Send byte to i2c communication channel
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t buf[3];

	buf[0] = data;     // data


	status = HAL_I2C_Master_Transmit(&hi2c1, (s_i2c_addr << 1), buf, 1, 100);
	if(status != HAL_OK)
    {
	        // Error handling, for example re-initialization of the I2C peripheral
		i2c_err_ = status ;
	    print_i2c_error();
    }
}
*/

static void platform_i2c_close(void)
{
    // ... free all i2c resources here
}

static void platform_i2c_send_buffer(const uint8_t *data, uint16_t len)
{
    // ... Send len bytes to i2c communication channel here
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Master_Transmit(&hi2c1, (s_i2c_addr << 1), (uint8_t *) data, len, 100);
	//status = HAL_I2C_Master_Transmit_DMA(&hi2c1, (s_i2c_addr << 1), (uint8_t *) data, len); //, 100);
	if(status != HAL_OK)
    {
	        // Error handling, for example re-initialization of the I2C peripheral
		i2c_err_ = status ;
	    print_i2c_error();
    }
}

void ssd1306_platform_i2cInit(int8_t busId, uint8_t addr, ssd1306_platform_i2cConfig_t * cfg)
{
	HAL_StatusTypeDef status = HAL_OK;


    status= HAL_I2C_IsDeviceReady(&hi2c1, (s_i2c_addr << 1), 1, 20000);

	if(status != HAL_OK)
    {
	        // Error handling, for example re-initialization of the I2C peripheral
		i2c_err_ = status ;
	    print_i2c_error();
    }

    ssd1306_intf.spi = 0;
    ssd1306_intf.start = &platform_i2c_start;
    ssd1306_intf.stop  = &platform_i2c_stop;
    //ssd1306_intf.send  = &platform_i2c_send;
    ssd1306_intf.close = &platform_i2c_close;
    ssd1306_intf.send_buffer = &platform_i2c_send_buffer;
    // init your interface here
    //...
}

void print_i2c_error() {
    if (i2c_err_ == 7) return;  // to avoid stickbreaker-i2c branch's error code
    printf(" OLED I2C ERROR CODE : ");
    printf("%d\n",i2c_err_);
}

#endif // YOUR_PLATFORM
