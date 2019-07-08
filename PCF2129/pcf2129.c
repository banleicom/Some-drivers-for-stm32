/*------------------------------------------------------------------------------
* Module Name      :  PCF2129.c
* Copyright        :
* Description      :  PCF2129  I2C接口驱动
* Revision History :
* Date          Author        Version        Notes
2019/7/8       banduoxing       V1.0           创建
------------------------------------------------------------------------------*/
#include "PCF2129.h"
#include "i2c.h"

#define I2C_TIMEOUT   10             //超时时间

PCF2129_t pcf2129;

/*
=============================================================================
 *  @brief :         初始化函数
 *  @note :
 *  @param :         使用HAL库 I2C接口
 *  @retva l: None
=============================================================================
*/
void PCF2129_Init(I2C_HandleTypeDef i2c_h,uint8_t addr) {
    pcf2129.i2c_h = i2c_h;
    pcf2129.i2caddr = addr;
}

/*
=============================================================================
 *  @brief :        查找设备
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
bool PCF2129_searchDevice(void) {
    return !(PCF2129_read(pcf2129.i2caddr) >>7);
}

/*
=============================================================================
 *  @brief :             设置24小时计时格式
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_configure(void) {
    PCF2129_set24mode();
}


/*
=============================================================================
 *  @brief :           获取PCF2129时间 日期
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_getDate(void) {
    pcf2129.date.ss=(PCF2129_read(PCF2129_SECONDS));
    pcf2129.date.mm=(PCF2129_read(PCF2129_MINUTES));
    pcf2129.date.hh=(PCF2129_read(PCF2129_HOURS));
    pcf2129.date.d=(PCF2129_read(PCF2129_DAYS));
    pcf2129.date.m=(PCF2129_read(PCF2129_MONTHS));
    pcf2129.date.y=(PCF2129_read(PCF2129_YEARS));
}

/*
=============================================================================
 *  @brief :          设置PCF2129时间
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_setDate(uint16_t years, uint8_t months, uint8_t days,
                     uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    PCF2129_write(PCF2129_SECONDS,decToBcd(seconds) + 0x80);
    PCF2129_write(PCF2129_MINUTES,decToBcd(minutes));
    PCF2129_write(PCF2129_HOURS,decToBcd(hours));
    PCF2129_write(PCF2129_DAYS,decToBcd(days));
    PCF2129_write(PCF2129_WEEKDAYS,0x00);
    PCF2129_write(PCF2129_MONTHS,decToBcd(months));
    PCF2129_write(PCF2129_YEARS,decToBcd(years-2000));
}

/*
=============================================================================
 *  @brief :        设置12小时计时格式
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_set12mode(void) {
    uint8_t ctrl;
    ctrl = PCF2129_readCtrl();
    ctrl |= PCF2129_CONTROL_12_24;
    PCF2129_writeCtrl(ctrl);
}

/*
=============================================================================
 *  @brief :     设置24小时计时格式
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_set24mode(void) {
    uint8_t ctrl;
    ctrl = PCF2129_readCtrl();
    ctrl &= ~(PCF2129_CONTROL_12_24);
    PCF2129_writeCtrl(ctrl);
}

/*
=============================================================================
 *  @brief :       读取一个寄存器内容
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
uint8_t PCF2129_read(uint8_t address) {
    uint8_t data;
    HAL_I2C_Mem_Read(&(pcf2129.i2c_h), pcf2129.i2caddr, address, 1, &data, 1, I2C_TIMEOUT);
}

/*
=============================================================================
 *  @brief :       写入一个结存器内容
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_write(uint8_t address, uint8_t data) {
    HAL_I2C_Mem_Write(&(pcf2129.i2c_h), pcf2129.i2caddr, address, 1, &data, 1, I2C_TIMEOUT);
}

/*
=============================================================================
 *  @brief :        读取控制结存器内容
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
uint8_t PCF2129_readCtrl(void) {
    return PCF2129_read(PCF2129_CONTROL_REGISTERS);
}

/*
=============================================================================
 *  @brief :       写入编辑寄存器内容
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
void PCF2129_writeCtrl(uint8_t data) {
    PCF2129_write(PCF2129_CONTROL_REGISTERS, data);
}

/*
=============================================================================
 *  @brief :        BCD编码 转 十进制
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
uint8_t bcdToDec(uint8_t value) {
    return (uint8_t) ( (value/16*10) + (value%16) );
}

/*
=============================================================================
 *  @brief :       十进制 转 BCD编码
 *  @note :
 *  @param :None
 *  @retva l: None
=============================================================================
*/
uint8_t decToBcd(uint8_t value) {
    return (uint8_t) ( (value/10*16) + (value%10) );
}

