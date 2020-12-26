/*
 * CmdKeen.cpp
 *
 *  Created on: 24.12.2020
 *      Author: danie
 */

#include "CmdKeen.hpp"
#include "usart.h"
#include "stdlib.h"



void ClassCmdTerminal::printQueue(int mode)
    {
    if(mode==POP)
	{
       int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
       uint8_t lReceivedValue;
       while(ItemsLeft)
	   {
	    xQueueReceive(CmdRxBufferHndl, &lReceivedValue, 1);
	     HAL_UART_Transmit(&huart1, &lReceivedValue, 1, 190);
	    ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);

	   }
	}
    if(mode==PEEK)
	{
	int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
	uint8_t lReceivedValue;
	//uint8_t* lReceivedBytes = new uint8_t(ItemsLeft);
	 uint8_t* lReceivedBytes;
	 lReceivedBytes = new uint8_t(ItemsLeft);
       for (int var = 0; var < ItemsLeft; ++var)
	   {
	   xQueueReceive(CmdRxBufferHndl, &lReceivedValue, 1);
	   lReceivedBytes[var] = lReceivedValue;
	   }
       HAL_UART_Transmit(&huart1, lReceivedBytes, ItemsLeft, 199);

       for (int var = 0; var < ItemsLeft; ++var)
	   {
	   xQueueSendToBack(CmdRxBufferHndl, &lReceivedBytes[var], 1);
	   }
       free(lReceivedBytes);


	}
    }

void ClassCmdTerminal::init(uint32_t len, uint32_t size)
    {
    CmdRxBufferHndl = xQueueCreate((UBaseType_t)len, (UBaseType_t)size);

    }
void ClassCmdTerminal::loop()
    {
    printQueue(PEEK);
    osDelay(1000);
    }

void ClassCmdTerminal::addKey(uint8_t pData)
    {
    BaseType_t* flag;
    xQueueSendToBackFromISR(CmdRxBufferHndl, &pData, flag);
    HAL_UART_Receive_IT(&huart1, &pData, sizeof(char));
    }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
    Cmd.addKey((uint8_t)huart1.Instance->DR);
    }
//using namespace cpp_freertos;



ClassCmdTerminal Cmd;
TaskCmd taskCmd;

