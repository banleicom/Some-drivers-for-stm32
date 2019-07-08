/*------------------------------------------------------------------------------
* Module Name      :  PCF2129.h
* Copyright        :
* Description      :  PCF2129  I2C接口驱动
* Revision History :
* Date          Author        Version        Notes
                 bdx            V1.0           创建
------------------------------------------------------------------------------*/

#include "drives.h"

#ifndef  __PCF2129_H
#define  __PCF2129_H

#define PCF2129_SLAVE_ADDRESS 0x51 ///< I2C Slave Address

/// @name Register Addresses
/// @{
#define PCF2129_CONTROL_12_24 0x04

#define PCF2129_CONTROL_REGISTERS 0x00
#define PCF2129_SECONDS 0x03
#define PCF2129_MINUTES 0x04
#define PCF2129_HOURS 0x05
#define PCF2129_DAYS 0x06
#define PCF2129_WEEKDAYS 0x07
#define PCF2129_MONTHS 0x08
#define PCF2129_YEARS 0x09
/// @}

/*
=============================================================================
 *  @brief :            时间日期结构体
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
typedef struct{

    uint8_t y,m,d,hh,mm,ss;
}DateTime_t;
/*
=============================================================================
 *  @brief :            PCF2129 结构体
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
typedef struct{
  I2C_HandleTypeDef i2c_h;
  uint8_t i2caddr;
  DateTime_t date;
}PCF2129_t;

void PCF2129_Init(I2C_HandleTypeDef i2c_h,uint8_t addr);
bool PCF2129_searchDevice(void);
void PCF2129_configure(void);
void PCF2129_getDate(void);
void PCF2129_setDate(uint16_t years, uint8_t months, uint8_t days,
                              uint8_t hours, uint8_t minutes, uint8_t seconds);
void PCF2129_set12mode(void);
void PCF2129_set24mode(void);
uint8_t PCF2129_read(uint8_t address);
void PCF2129_write(uint8_t address, uint8_t data);
void PCF2129_writeCtrl(uint8_t data);
uint8_t PCF2129_readCtrl(void);

uint8_t bcdToDec(uint8_t value);
uint8_t decToBcd(uint8_t value);







#endif 