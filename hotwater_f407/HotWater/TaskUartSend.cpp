/*
 * TaskUartSend.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: danie
 */

#include "TaskUartSend.hpp"

void ClassUartSend::addString( void *String )
    {

    }
void ClassUartSend::init(uint32_t len, uint32_t sendatonce )
    {
    CmdTxBufferHndl = xQueueCreate( len, sizeof( char * ) );
    this->sendatonce = sendatonce;
    }

void ClassUartSend::SendQueue()
    {
    uint8_t lReceivedValue;
    //TODO: which malloc are to use ? pvPortMalloc assumes unsinged int as size
    dmaBuff = (uint8_t*)pvPortMalloc(sendatonce/2);

    for ( int var = 0; var < sendatonce; ++var )
	{
	xQueueReceive( CmdTxBufferHndl, &lReceivedValue, 0 );
	dmaBuff[var] = lReceivedValue;
	}

    int ItemsLeft = uxQueueMessagesWaitingFromISR( CmdTxBufferHndl );
    if( ItemsLeft )
	HAL_UART_Transmit_DMA( &huart1, dmaBuff, sendatonce );
    vPortFree(dmaBuff);
    }
