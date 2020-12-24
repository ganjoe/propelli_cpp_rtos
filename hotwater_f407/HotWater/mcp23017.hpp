/*
 * mcp23017.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */

#ifndef INC_MCP23017_HPP_
#define INC_MCP23017_HPP_
#include "main.h"
#include "i2c.h"
#include "cpp_TaskLink.hpp"

typedef enum
    {
    MCP_INPUT,
    MCP_OUTPUT,
    MCP_PULLUP,
    MCP_HIGHZ,
    }
MCP_PINMODE;

#define REGISTER_IODIRA		0x00
#define REGISTER_GPPUA		0x0C
#define REGISTER_GPIOA		0x12
#define REGISTER_OLATA		0x14
#define MCP23017_PORTA		0x00

class ClassMcp
    {
public:
    uint16_t addr;
    uint16_t pullups, direction, outlatch, inputstate;
    I2C_HandleTypeDef* hi2c;

    //modflag /rtos - init
    void init(uint16_t i2caddr, I2C_HandleTypeDef* hi2c);
    // interface
    void WritePin(uint8_t pinnr, int state);
    void PinMode(MCP_PINMODE pinmode, uint8_t pinnr);
    bool ReadPin(uint8_t pinnr);
    void ToggPin(uint8_t pinnr);
    void set_all_input();
    void WriteWord(uint16_t word);

private:

    // lowlevel
    void lolWriteBuffer(uint16_t *buffer, uint16_t addr);
    void lolReadBuffer(uint16_t *buffer, uint16_t addr);
    // hardwarelevel
    void lolWriteByte(uint16_t regaddr, uint8_t data);
    void lolReadByte(uint8_t regaddr, uint8_t *data);

    };
extern ClassMcp mcp;

class TaskMcp: public ClassTaskCreate
    {
public:

	void setup() override
	    {
	    mcp.init(0x20, &hi2c1);
	    }
	void loop() override
	    {
	    osDelay(200);
	    }
};
extern TaskMcp taskMcp;

#endif /* INC_MCP23017_HPP_ */
