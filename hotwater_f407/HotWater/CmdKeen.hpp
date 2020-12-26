/*
 * CmdKeen.hpp
 *
 *  Created on: 24.12.2020
 *      Author: daniel
 */

#ifndef CMDKEEN_HPP_
#define CMDKEEN_HPP_

#include "FreeRTOS.h"
#include "queue.h"
#include "usart.h"
#include "cpp_TaskLink.hpp"

 enum
{
    PEEK,
    POP,
    PARSE,
};

class ClassCmdTerminal
    {
public:

   void init(uint32_t len, uint32_t size);
   void addKey(uint8_t pData);
   void printQueue(int mode);
   void loop();

private:

   QueueHandle_t CmdRxBufferHndl;


};

extern ClassCmdTerminal Cmd;

class TaskCmd: public ClassTaskCreate
    {
public:
    void setup() override
	{
	Cmd.init(256, 1);
	}
    void loop() override
	{
	Cmd.loop();
	}
    };
extern TaskCmd taskCmd;
#endif /* CMDKEEN_HPP_ */
