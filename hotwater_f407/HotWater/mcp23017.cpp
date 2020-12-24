/*
 * mcp23017.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */

#include  "mcp23017.hpp"

#include "utils.h"

void ClassMcp::WritePin(uint8_t pinnr, int state)
    {
    utils_set_bit_in_Word(&outlatch, pinnr, (bool) state);
    }

void ClassMcp::ToggPin(uint8_t pinnr)
    {
    utils_togg_bit_in_Word(&outlatch, pinnr);
    }

bool ClassMcp::ReadPin(uint8_t pinnr)
    {
    return utils_get_bit_in_Word(&inputstate, pinnr);
    }

void ClassMcp::PinMode(MCP_PINMODE pinmode, uint8_t pinnr)
    {
    switch (pinmode)
	{
    case MCP_PULLUP:
	{
	utils_set_bit_in_Word(&direction, pinnr, true);
	utils_set_bit_in_Word(&pullups, pinnr, true);
	}
	break;
    case MCP_INPUT:
	{
	utils_set_bit_in_Word(&direction, pinnr, true);
	utils_set_bit_in_Word(&pullups, pinnr, false);
	}
	break;
    case MCP_OUTPUT:
	{
	utils_set_bit_in_Word(&direction, pinnr, false);
	utils_set_bit_in_Word(&pullups, pinnr, false);
	}

	break;
	}
    //When a bit is set, the corresponding pin becomes aninput.
    //mcp_lolWriteBuffer(io, &io->direction, REGISTER_IODIRA);

    //A read from this register results in a read of theOLAT  and  not  the  port  itself.
    //A  write  to  this  registermodifies  the  output  latches  that  modifies  the  pinsconfigured as outputs
    //mcp_lolWriteBuffer(io, &io->outlatch, REGISTER_OLATA);

    //If  a  bit  is  set  and  the  corresponding  pin  is configured  as  an  input,
    //the  corresponding  port  pin  isinternally pulled up with a 100 k resistor.
    //mcp_lolWriteBuffer(io, &io->pullups, REGISTER_GPPUA);

    }

void ClassMcp::WriteWord(uint16_t word)
    {
    pullups = 0;
    direction = !word;
    outlatch = word;
    }

void ClassMcp::lolWriteBuffer(uint16_t *buffer, uint16_t addr)
    {
    uint16_t dword = *buffer;
    uint8_t highByte = dword >> 8;
    uint8_t lowByte = dword & 0x00FF;
    lolWriteByte(addr, lowByte);
    lolWriteByte(addr + 1, highByte);
    }

void ClassMcp::lolReadBuffer(uint16_t *buffer, uint16_t addr)
    {
    uint16_t dword;
    uint16_t *ptr = &dword;
    uint8_t highByte, lowByte;
    lolReadByte(addr, &lowByte);
    lolReadByte(addr + 1, &highByte);

    dword = highByte << 8;
    dword |= lowByte;
    *buffer = *ptr;
    }

void ClassMcp::lolWriteByte(uint16_t regaddr, uint8_t data)
    {
    HAL_StatusTypeDef complete = HAL_ERROR;
    complete = HAL_I2C_Mem_Write(&hi2c1, addr, regaddr, 1, &data, 1,
	    HAL_TIMEOUT);
    if (complete == !HAL_OK)
	{
	//TODO:I2C ERROR
	}
    }

void ClassMcp::lolReadByte(uint8_t regaddr, uint8_t *data)
    {
    uint8_t localbuff;

    HAL_StatusTypeDef complete = HAL_ERROR;
    //complete =  HAL_I2C_Mem_Read_DMA(&hi2c1, io->addr, &regaddr, 1, &localbuff, 1);

	complete = HAL_I2C_Master_Transmit(&hi2c1, addr, (uint8_t*)regaddr, 1,	HAL_TIMEOUT);
	complete = HAL_I2C_Master_Receive(&hi2c1, addr, &localbuff, 1,		HAL_TIMEOUT);

    if (complete == HAL_OK)
	{
	*data = localbuff;
	}
    else
	{
	//TODO:I2C ERROR
	}
    }

void ClassMcp::init(uint16_t i2caddr, I2C_HandleTypeDef* hi2c)
    {
    this->addr=i2caddr;
    this->hi2c = hi2c;
    }

ClassMcp mcp;
TaskMcp taskMcp;
