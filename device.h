#ifndef _DEVICE_H
#define _DEVICE_H
#include "stdint.h"
//lcd_bass_addr_t *base_addr;
typedef uint16_t error_t;

typedef struct device *device_t;
struct device
{
	error_t (*init)(device_t dev);
	int (*read)(device_t dev, int pos, void *buffer, int size);
	int (*write)(device_t dev, int pos, const void *buffer, int size);
	error_t (*control)(device_t dev, uint8_t cmd, void *arg);
	void *user_data;
}device;

error_t device_register(device_t dev, void *user_data);
#endif

/****************************EOF (not truncated)*************************************/
