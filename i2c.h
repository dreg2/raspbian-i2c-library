#ifndef I2C_H
#define I2C_H

// functions
int     i2c_open(const char *device);
int     i2c_select(int i2c_bus, uint8_t address);
ssize_t i2c_write(int i2c_bus, uint8_t *data, size_t len);
ssize_t i2c_read(int i2c_bus, uint8_t *data, size_t len);

#endif // I2C_H
