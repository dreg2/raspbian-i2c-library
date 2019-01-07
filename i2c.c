#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <linux/i2c-dev.h>

#include "i2c.h"

static uint8_t i2c_address = 0x00;

//----------------------------------------------------------------------------------------------------//
// open i2c bus                                                                                       //
//----------------------------------------------------------------------------------------------------//
int i2c_open(const char *device)
	{
	int i2c_bus;

	// open I2C bus
	if ((i2c_bus = open(device, O_RDWR)) < 0)
		{
		perror("I2C: open failed:");
		return -1;	
		}

	return i2c_bus;
	}

//----------------------------------------------------------------------------------------------------//
// select i2c bus device                                                                              //
//----------------------------------------------------------------------------------------------------//
int i2c_select(int i2c_bus, uint8_t address)
	{
	i2c_address = address;

	// select for I/O on I2C bus
	if (ioctl(i2c_bus, I2C_SLAVE, i2c_address) < 0)
		{
		perror("I2C: ioctl for select failed:");
		return -1;
		}

	return 0;
	}

//----------------------------------------------------------------------------------------------------//
// write to i2c                                                                                       //
//----------------------------------------------------------------------------------------------------//
ssize_t i2c_write(int i2c_bus, uint8_t *data, size_t len)
        {
        if (write(i2c_bus, data, len) < 1)
                {
                perror("I2C: write failed:");
                return -1;
                }
        return (ssize_t)len;
        }

//----------------------------------------------------------------------------------------------------//
// read from i2c                                                                                      //
//----------------------------------------------------------------------------------------------------//
ssize_t i2c_read(int i2c_bus, uint8_t *data, size_t len)
        {
        if (read(i2c_bus, data, len) != (ssize_t)len)
                {
                perror("I2C: read failed:");
                return -1;
                }
        return (ssize_t)len;
        }
