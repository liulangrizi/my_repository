#include "device.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_NODE(type) \
		struct list_node_##type{ \
			type data; \
			list_node_##type *next; \
		}
#define LIST_MANAGE(type) \
		struct list_node_##type{ \
			struct list_node_##type *head;
			int count;
			void (*append)(struct list_node_##type, type); \
		}

void (*append)(struct list_node_device *dev, device_t data)
{
	struct list_node_device *new_node = malloc(sizeof(struct list_node_device));
	memcpy(new_node, data, sizeof(data));
}
device gdev[5];

error_t device_register(device_t dev, void *user_data)
{
	for(uint8_t i = 0; i < sizeof(dev) / sizeof(dev[0]); i++)
	{
		if(gdev[i] == NULL)
		{
			gdev[i].init = dev -> init;
			gdev[i].read = dev -> read;
			gdev[i].write = dev -> write;
			gdev[i].control = dev -> control;
			gdev[i].user_data = dev-> user_data;
		}
	}
	if( i < sizeof(dev) / sizeof(dev[0])
		return 0;
	return i;
}
void hal_lcd_setup(void)
{
	device_t lcd_device;
	static lcd_user_data_t lcd_user_data;
	lcd_user_data.base_addr = (lcd_bass_addr_t *)EXMC_BASE_ADDR;
	lcd_user_data.refresh_area = lcd_refresh_area;
	
	device_register(lcd_device, (void *)&lcd_user_data);
	lcd_device->init = lcd_init;
	lcd_device->read = lcd_read;
	lcd_device->control = lcd_control;
	
	lcd_device->init(lcd_device);
	lcd_device->control(lcd_device, LCD_BACKLIGHT_CMD, (void *)BL_ON);
}
static int lcd_read(device_t dev, int pos, void *buffer, int size)
{
	
}
static error_t lcd_control(device_t dev, uint8_t cmd, void *arg)
{
	uint8_t param = *(uint8_t *)arg;
	switch(cmd)
	{
		case LCD_RESET_CMD:
		{
			lcd_delay(150);
			hal_pin_reset(_LCD_RESET_PIN);
			lcd_delay(150);
			hal_pin_reset(_LCD_RESET_PIN);
		}break;
		case LCD_BACKLIGHT_CMD:
		{
			if(param >= 2)
				return 1;
			hal_pin_write(_LCD_BK_CTL_PIN, param);
		}break;
		default:break;
	};
	return 0;
}
static int lcd_write(device_t dev, int pos, const void *buffer, int size)
{
	for(int i = 0; i < size; i++)
	{
		pos = *((color_t *)buffer + i);
	}
}
static void lcd_delay(uint16_t ms)
{
	SysTick_Delay(ms);
}
static error_t lcd_init(device_t dev)
{
	lcd_user_data_t *lcd_dev_user_data = (lcd_user_data_t *)dev->user_data;
	dev->control(dev, LCD_RESET_CMD, 0);
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x11, 1);
	lcd_delay(150);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00D0, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0007, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0042, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x001f, 1);//18
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00D1, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0016, 1);//05
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);//06

	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00D2, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0001, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0012, 1);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00C0, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);//D4:REV  D3:SM  D2:GS
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x003B, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0002, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0001, 1);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00C5, 1);//Frame Rate
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0003, 1);
	
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00C8, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0014, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0033, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0010, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0016, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0044, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0036, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0077, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x000f, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	
//	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00F8, 1);
//	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0001, 1); 
//	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x00FE, 1);
//	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
//	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0002, 1);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x000b, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x002A, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0001, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x003F, 1);
	
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x002B, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0000, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x0001, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x00DF, 1);
	
	//dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x0021, 1);
	/*This command causes the display module to invert the image data only on the display device. The frame memory
contents remain unchanged. No status bits are changed.*/
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x002C, 1);
	lcd_delay(10);
	
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x0029, 1);
	
	lcd_delay(50);
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x3A, 1);
	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x55, 1);//55是565，也就是16位；66是666，也就是18位，77则是888，即24位(注意：需要能支持24位的液晶屏才可设置77)
	dev->write(dev, lcd_dev_user_data->base_addr->reg_addr, (const void *)0x36, 1);

	dev->write(dev, lcd_dev_user_data->base_addr->data_addr, (const void *)0x2B, 1);
//	lcd_dev->refresh_area(0,0,480 - 1,320 - 1,Red);
}



/****************************EOF (not truncated)*************************************/
