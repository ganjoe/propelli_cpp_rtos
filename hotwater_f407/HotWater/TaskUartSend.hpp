/*
 * UartSend.hpp
 *
 *  Created on: Dec 30, 2020
 *      Author: danie
 */

#ifndef TASKUARTSEND_HPP_
#define TASKUARTSEND_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "stdio.h"
#include "cpp_TaskLink.hpp"
#include "usart.h"

//queue size for all sprintf-strings, that are not send yet
#define UART_SENDBUFFER 128

//n items are send at once every taskloop
#define UART_PRINTLOOP 8

/* Gatekeepertask for UartAccess. Prints out n Bytes from Queuebuffer every loop.
 * therfore, dma can be used
 * strings are copied when passed as pointers.
 * if stringsize is not given then it is determined by strlen()*/
class ClassUartSend
    {
public:
    // virtual function implementation
   void init(uint32_t len,  uint32_t sendatonce);
   void loop();
   //interface
   void SendQueue();

private:

   //nr of bytes that are send at once
   uint8_t sendatonce;

   //maybe dma needs static adress for continuing transfer after the task has be left
   static uint8_t* dmaBuff;

   //FreeRTOS Queues
    QueueHandle_t CmdTxBufferHndl;

    //FreeRTOS ISR Timer callback is not used, instead osDelay
    //void vApplicationTickHook( void );

    void addString( void *String );
    };

extern ClassUartSend Usend;

class TaskUsend: public ClassTaskCreate
    {
public:
    void setup() override
	{
	Usend.init(UART_SENDBUFFER, UART_PRINTLOOP);
	}
    void loop() override
	{
	Usend.loop();
	}
    };
extern TaskUsend taskUsend;

#endif /* TASKUARTSEND_HPP_ */
