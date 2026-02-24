#ifndef    _I2C_H
#define    _I2C_H


int  I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);


#endif