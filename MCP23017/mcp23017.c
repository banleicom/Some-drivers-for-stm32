#include "mcp23017.h"

// Registers
#define REGISTER_IODIRA		0x00
#define REGISTER_IODIRB		0x01
#define REGISTER_IPOLA		0x02
#define REGISTER_IPOLB		0x03
#define REGISTER_GPINTENA	0x04
#define REGISTER_GPINTENB	0x05
#define REGISTER_DEFVALA	0x06
#define REGISTER_DEFVALB	0x07
#define REGISTER_INTCONA	0x08
#define REGISTER_INTCONB	0x09
#define	REGISTER_IOCON		0x0A
//	IOCON			0x0B
#define REGISTER_GPPUA		0x0C
#define REGISTER_GPPUB		0x0D
#define REGISTER_INTFA		0x0E
#define REGISTER_INTFB		0x0F
#define REGISTER_INTCAPA	0x10
#define REGISTER_INTCAPB	0x11
#define REGISTER_GPIOA		0x12
#define REGISTER_GPIOB		0x13
#define REGISTER_OLATA		0x14
#define REGISTER_OLATB		0x15

#define I2C_TIMEOUT		10

void mcp23017_init(MCP23017_HandleTypeDef *hdev, I2C_HandleTypeDef *hi2c, uint16_t addr)
{
    hdev->hi2c = hi2c;
    hdev->addr = addr << 1;
}

HAL_StatusTypeDef mcp23017_read(MCP23017_HandleTypeDef *hdev, uint16_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Read(hdev->hi2c, hdev->addr, reg, 1, data, 1, I2C_TIMEOUT);

    //return I2cRead( hdev->hi2c, hdev->addr, reg, data );
}

HAL_StatusTypeDef mcp23017_write(MCP23017_HandleTypeDef *hdev, uint16_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Write(hdev->hi2c, hdev->addr, reg, 1, data, 1, I2C_TIMEOUT);
    //uint8_t dat=*data;
    //return I2cWrite(hdev->hi2c,hdev->addr,reg,dat);
}

HAL_StatusTypeDef mcp23017_iodir(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t iodir)
{
    uint8_t data[1] = {iodir};
    return mcp23017_write(hdev, REGISTER_IODIRA|port, data);
}

HAL_StatusTypeDef mcp23017_ipol(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t ipol)
{
    uint8_t data[1] = {ipol};
    return mcp23017_write(hdev, REGISTER_IPOLA|port, data);
}

HAL_StatusTypeDef mcp23017_ggpu(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t pu)
{
    uint8_t data[1] = {pu};
    return mcp23017_write(hdev, REGISTER_GPPUA|port, data);
}

HAL_StatusTypeDef mcp23017_read_gpio(MCP23017_HandleTypeDef *hdev, uint8_t port)
{
    uint8_t data[1];
    HAL_StatusTypeDef status;
    status = mcp23017_read(hdev, REGISTER_GPIOA|port, data);
    if (status == HAL_OK)
        hdev->gpio[port] = data[0];
    return status;
}

HAL_StatusTypeDef mcp23017_write_gpio(MCP23017_HandleTypeDef *hdev, uint8_t port)
{
    uint8_t data[1] = {hdev->gpio[port]};
    return mcp23017_write(hdev, REGISTER_GPIOA|port, data);
}

HAL_StatusTypeDef mcp23017_intA_en(MCP23017_HandleTypeDef *hdev, uint8_t intEn)
{
    uint8_t data[1] = {intEn};
    return mcp23017_write(hdev, REGISTER_GPINTENA, data);
}

HAL_StatusTypeDef mcp23017_intB_en(MCP23017_HandleTypeDef *hdev, uint8_t intEn)
{
    uint8_t data[1] = {intEn};
    return mcp23017_write(hdev, REGISTER_GPINTENB, data);
}

HAL_StatusTypeDef mcp23017_setA_defval(MCP23017_HandleTypeDef *hdev, uint8_t defVal)
{
    uint8_t data[1] = {defVal};
    return mcp23017_write(hdev, REGISTER_DEFVALA, data);
}

HAL_StatusTypeDef mcp23017_setB_defval(MCP23017_HandleTypeDef *hdev, uint8_t defVal)
{
    uint8_t data[1] = {defVal};
    return mcp23017_write(hdev, REGISTER_DEFVALB, data);
}

HAL_StatusTypeDef mcp23017_setA_intcom(MCP23017_HandleTypeDef *hdev, uint8_t intCom)
{
    uint8_t data[1] = {intCom};
    return mcp23017_write(hdev, REGISTER_INTCONA, data);
}

HAL_StatusTypeDef mcp23017_setB_intcom(MCP23017_HandleTypeDef *hdev, uint8_t intCom)
{
    uint8_t data[1] = {intCom};
    return mcp23017_write(hdev, REGISTER_INTCONA, data);
}

HAL_StatusTypeDef mcp23017_set_iocom(MCP23017_HandleTypeDef *hdev, uint8_t ioCom)
{
    uint8_t data[1] = {ioCom};
    return mcp23017_write(hdev, REGISTER_IOCON, data);
}

void mcp23017_readA_intcap(MCP23017_HandleTypeDef *hdev,uint8_t *data)
{   
    mcp23017_read(hdev, REGISTER_INTCAPA, data);
}

