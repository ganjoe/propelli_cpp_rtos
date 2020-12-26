/*
 * CmdKeen.cpp
 *
 *  Created on: 24.12.2020
 *      Author: danie
 */

#include "CmdKeen.hpp"
#include "usart.h"




void ClassCmdTerminal::printQueue()
    {
   int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
   uint8_t lReceivedValue;
   while(ItemsLeft)
       {
        xQueueReceive(CmdRxBufferHndl, &lReceivedValue, 1);
        ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
        HAL_UART_Transmit(&huart1, &lReceivedValue, 1, 190);
       }
    }

void ClassCmdTerminal::init(uint32_t len, uint32_t size)
    {
    CmdRxBufferHndl = xQueueCreate((UBaseType_t)len, (UBaseType_t)size);

    }
void ClassCmdTerminal::loop()
    {
    printQueue();
    osDelay(200);
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

