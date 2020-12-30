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
#include "stdio.h"

#include "commands.hpp"

//testing, only PARSEUART is used
 enum
{
    PEEK,
    POP,
    PARSE,
    PARSEUART,
};
//return values from command interpreter
enum
{
    CMD_VALID=1,
    CMD_ARGCOUNT,
    CMD_ARGRANGE,
};

//length for that array that holds pointer to the callbacks
#define CALLBACK_LEN 40

//length of cli input-string (file or uart) with arguments
#define CMD_MAXSTRG 32

//nr of cli-arguments that are processed
#define CMD_MAXARG 4

//array size for snprintf
#define CMD_PRINTBUFFER 32

//TODO:obsolet
//n items are send at once every taskloop
#define CMD_PRINTLOOP 8

//TODO:obsolet
//queue size for all sprintf-strings, that are not send yet
#define CMD_SENDBUFFER 128

//queue size for inputstrings, that are not processed yet
#define CMD_RECEIVEBUFF 128

 typedef struct
 	{

 	const char *command;
 	const char *help;
 	const char *arg_names;
 	void (*cbf)(int argc, const char **argv);
 	}
 TD_TERMINAL_CALLBACKS;

static TD_TERMINAL_CALLBACKS callbacks[CALLBACK_LEN];


class ClassCmdTerminal
    {
public:

    // virtual function implementation
   void init(uint32_t len, uint32_t size);
   void loop();

   //set new byte from isr
   void addByteFromISR(uint8_t pData);

   void addByte(uint8_t pData);

   //snprintf wrapper
   void pprint(const char *fmt, ...);

  //nr of occurences of line terminations in CmdRxBuffer
   int newCmdCnt;


   uint8_t pData;


    private:
   //FreeRTOS Queues
    QueueHandle_t CmdRxBufferHndl, CmdTxBufferHndl;

   //nr of registered callbacks
   int callback_write;

    void SendQueue();

    int parseCommand(uint8_t* CmdStrin);

    void ReadQueue(int mode);

    void RegisterCommand();

    void term_lol_vprint(const char *fmt, va_list argp);

    void term_lol_setCallback(const char *command,const char *help,const char *arg_names, void (*cbf)(int argc, const char **argv));
};


extern ClassCmdTerminal Cmd;

class TaskCmd: public ClassTaskCreate
    {
public:
    void setup() override
	{
	Cmd.init(CMD_RECEIVEBUFF, 1);

	}
    void loop() override
	{
	Cmd.loop();
	}
    };
extern TaskCmd taskCmd;

#endif /* CMDKEEN_HPP_ */
