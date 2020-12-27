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



static int callback_write = 0;

 enum
{
    PEEK,
    POP,
    PARSE,
    PARSEUART,
};

enum
{
    CMD_VALID,
    CMD_ARGCOUNT,
    CMD_ARGRANGE,
};
#define CALLBACK_LEN 40
#define CMD_MAXSTRG 32
#define CMD_MAXARG 4


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


   void init(uint32_t len, uint32_t size);
   void addByte(uint8_t pData);
   void ReadQueue(int mode);
  void RegisterCommand();
   int parseCommand(uint8_t* CmdStrin);
   void SendQueue(int len);
   void pprint(const char *fmt, ...);
  int newCmd;
   void loop();


   int callback_write;
   uint8_t pData;
   QueueHandle_t CmdRxBufferHndl, CmdTxBufferHndl;
    private:

  void flushQueue(QueueHandle_t BufferHndl);
  void term_lol_vprint(const char *fmt, va_list argp);
  void term_lol_setCallback(const char *command,const char *help,const char *arg_names, void (*cbf)(int argc, const char **argv));
};


extern ClassCmdTerminal Cmd;

class TaskCmd: public ClassTaskCreate
    {
public:
    void setup() override
	{
	Cmd.init(32, 1);

	}
    void loop() override
	{
	Cmd.loop();
	}
    };
extern TaskCmd taskCmd;

#endif /* CMDKEEN_HPP_ */
