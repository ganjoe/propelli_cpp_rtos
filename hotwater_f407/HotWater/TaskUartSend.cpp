/*
 * TaskUartSend.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: danie
 */

#include "TaskUartSend.hpp"
#include "stdarg.h"
#include "utils.h"
#include "string.h"

void ClassUartSend::addString( void *String )
    {

    }

void ClassUartSend::init(uint32_t len, uint32_t sendatonce )
    {
    CmdTxBufferHndl = xQueueCreate( len, sizeof( char * ) );
    this->sendatonce = sendatonce;
    }

void ClassUartSend::loop()
    {
    SendQueue();

    }

void ClassUartSend::SendQueue()
    {
    if ( ! transmissionFlag)
	{
	uint8_t popedByte;
	int ItemsLeft;


	ItemsLeft = uxQueueMessagesWaiting( CmdTxBufferHndl );

	if ( ItemsLeft )
	    {
	    //limits the numbers of bytes to send
	    utils_truncate_number_int( &ItemsLeft, 0, sendatonce );

	    //pvPortMalloc assumes unsigned int as size. the buffersize is truncated by sendatonce value
	    dmaBuff = ( uint8_t* )pvPortMalloc( ItemsLeft / 2 );

	    //copy bytes that are send at once to temp buffer
	    for ( int var = 0; var < ItemsLeft; ++var )
		{
		//should receive from front
		xQueueReceive( CmdTxBufferHndl, &popedByte, 0 );

		dmaBuff[ var ] = popedByte;
		}

		//transmission time[s]: 10 bit / n baud
		Usend.transmissionFlag = true;
		HAL_UART_Transmit_DMA( &huart1, dmaBuff, ItemsLeft );

	    //TODO: consider allocating once and didn't free
	    vPortFree( dmaBuff );
	    }
	}
    }

void ClassUartSend::write( uint8_t* buffer )
    {

    uint8_t bytesWrote =strlen( ( char* ) buffer );

    //TODO: check makes no sense, but better than nothing
    if (bytesWrote>=0 && bytesWrote < UART_PRINTBUFFER)
	{
	for (int var = 0; var < bytesWrote; ++var)
	    {
	    xQueueSendToBack(CmdTxBufferHndl,	&buffer[ var ], portMAX_DELAY);
	    }
	}

    }

void ClassUartSend::print(const char *fmt, ...)
    {
    va_list argp;
    va_start(argp, fmt);
    char pbuffer[UART_PRINTBUFFER];
    uint8_t bytesWrote;

    bytesWrote = snprintf(pbuffer, UART_PRINTBUFFER, fmt);

    if (bytesWrote>=0 && bytesWrote < UART_PRINTBUFFER)
	{
	for (int var = 0; var < bytesWrote; ++var)
	    {
	    xQueueSendToBack(CmdTxBufferHndl,	&pbuffer[var], portMAX_DELAY);
	    }
	}
    va_end(argp);
    }

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
    {
    //works only with _DMA and _ISR
    Usend.transmissionFlag = false;
    }

ClassUartSend Usend;

TaskUsend taskUsend;



