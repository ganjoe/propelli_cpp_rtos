/*
 * CmdKeen.cpp
 *
 *  Created on: 24.12.2020
 *      Author: danie
 */

#include "CmdKeen.hpp"
#include "usart.h"
#include "stdlib.h"
#include "string.h"

void ClassCmdTerminal::ReadQueue(int mode)
    {
    //----------------------------------
    if (mode == POP)
	{
	int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
	uint8_t lReceivedValue;
	while (ItemsLeft)
	    {
	    xQueueReceive(CmdRxBufferHndl, &lReceivedValue, 1);
	    HAL_UART_Transmit(&huart1, &lReceivedValue, 1, 190);
	    ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);

	    }
	}
    //----------------------------------
    if (mode == PEEK)
	{
	int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
	uint8_t lReceivedValue;
	//uint8_t* lReceivedBytes = new uint8_t(ItemsLeft);
	uint8_t *lReceivedBytes;
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
	delete (lReceivedBytes);
	}
    //----------------------------------
    //make shure there is some terminatet string in queue
    if ((mode == PARSE) & newKey)
	{
	int ItemsLeft = uxQueueMessagesWaiting(CmdRxBufferHndl);
	uint8_t lReceivedValue;
	uint8_t *peekBuffer;
	//adding \0
	peekBuffer = new uint8_t(ItemsLeft + 1);
	//copy queue to sized buffer
	for (int var = 0; var < ItemsLeft; ++var)
	    {
	    //pop last item
	    xQueueReceive(CmdRxBufferHndl, &lReceivedValue, 1);

	    //copy to temp buffer
	    peekBuffer[var] = lReceivedValue;

	    //check for carriage return
	    if (lReceivedValue == 13)	//carriage return, \r
		{
		//adding string terminator
		memcpy((char*) peekBuffer + var, "\0", 1);

		//compare strings with registered callback-names
		if (parseCommand(peekBuffer) == CMD_VALID)
		    {
		    //valid command found
		    HAL_UART_Transmit(&huart1, peekBuffer, var, 199);

		    //"[CMDKEEN][PARSE] valid Command %s", peekBuffer"
		    }
		//no further bytes are processed in queue
		break;
		}
	    }
	newKey = false;
	delete (peekBuffer);
	}

    }

void ClassCmdTerminal::init(uint32_t len, uint32_t size)
    {

    CmdRxBufferHndl = xQueueCreate((UBaseType_t )len, (UBaseType_t )size);
    RegisterCommand();
    }

void ClassCmdTerminal::loop()
    {
    ReadQueue(PARSE);
    }

void ClassCmdTerminal::addKeyIsr(uint8_t pData)
    {
    BaseType_t *flag, xStatus;

    xStatus = xQueueSendToBackFromISR(CmdRxBufferHndl, &pData, flag);
    if (xStatus != pdPASS)
	{
	// vPrintString( "Could not send to the queue.\r\n" );
	}
    if (pData == 13)
	{
	newKey = true;
	}
    HAL_UART_Receive_IT(&huart1, &pData, sizeof(char));
    }

void ClassCmdTerminal::RegisterCommand()
    {
    /*	term_lol_setCallback("setword", "mcp regs A und B mit wort setzen",	"dword",	setword);
     term_lol_setCallback("writepin", "pin, state",		"bits ab port a setzen",	writepin);
     term_lol_setCallback("readpin", "register lesen",	    "pinnr, pullupstate", 	readpin);
     term_lol_setCallback("setallin", "help",    "arghelp", 	setallin);

     term_lol_setCallback("setdate", "dd mm yy",	    "rtc setzen", setdate);
     term_lol_setCallback("settime", "hh mm ss",	    "rtc setzen", settime);

     term_lol_setCallback("sdwrite", "filename string chars lines","schreibt zu beginn einer zeile",	sdwrite);
     term_lol_setCallback("sdread", 	"help",	    "arghelp", 	sdread);

     term_lol_setCallback("readinit","help",	    "arghelp", 	readinit);
     term_lol_setCallback("writeinit","help",	"arghelp", 	writeinit);
     term_lol_setCallback("clearinit","write blanks to initfile","lines to write", 	clearinit);

     term_lol_setCallback("readrom","help",   "arghelp", readrom);
     term_lol_setCallback("writerom","help",	"arghelp", 	writerom);
     term_lol_setCallback("clearrom","write blanks to eeprom","lines to write", 	clearrom);

     term_lol_setCallback("nlogn",	"help",		"arghelp", 	nlogn);
     term_lol_setCallback("nlog",	"help",		"arghelp", 	nlog);

     term_lol_setCallback("vrange","USV Spannungslevel. Bsp: 10.5 12.8 13.6 ","lowlimit(SoC:0%) highlimit(SoC:100%) invlimit(only charging)",vrange);
     term_lol_setCallback("mode","Heizung Betriebsmodus","0: eco 1: full", 	mode);
     term_lol_setCallback("trange","Heizung Temperaturschwellen","lowlimit<float>_highlimit<float>", 	trange);

     term_lol_setCallback("selterm",	"help",		"arghelp", 	selterm);
     term_lol_setCallback("selhhw", 	"help",		"arghelp", 	selhhw); */
    term_lol_setCallback("reset", "Backup und Reset", "kein Argument", reset);
    }

int ClassCmdTerminal::parseCommand(uint8_t *CmdString)
    {
    int argc = 0;

    char *argv[CMD_MAXARG];

    char *ptr = (char*) CmdString;

    char *sep = strdup(" ");

    char *token = strtok(ptr, sep);

    while (token && argc < CMD_MAXARG)
	{
	argv[argc++] = token;
	token = strtok(0, sep);
	}
    if (argc == 0)
	return CMD_ARGCOUNT;

    if (strcmp(argv[0], "help") == 0)
	{
	//term_printf(term, "registered commands:\n");

	for (int i = 0; i < callback_write; i++)
	    {
	    //term_printf(term, callbacks[i].command);
	    //term_printf(term, "\rhelp: ");
	    //term_printf(term, callbacks[i].help);
	    //term_printf(term, "\r");
	    }
	}

    for (int i = 0; i < callback_write; i++)
	{
	if (callbacks[i].cbf != 0 && strcmp(argv[0], callbacks[i].command) == 0)
	    {
	    callbacks[i].cbf(argc, (const char**) argv);
	    return CMD_VALID;
	    }
	}

    }

void ClassCmdTerminal::term_lol_setCallback(const char *command,
	const char *help, const char *arg_names,
	void (*cbf)(int argc, const char **argv))
    {
    int callback_num = callback_write;
    for (int i = 0; i < callback_write; i++)
	{
	// First check the address in case the same callback is registered more than once.
	if (callbacks[i].command == command)
	    {
	    callback_num = i;
	    break;
	    }
	// Check by string comparison.
	if (strcmp(callbacks[i].command, command) == 0)
	    {
	    callback_num = i;
	    break;
	    }
	// Check if the callback is empty (unregistered)
	if (callbacks[i].cbf == 0)
	    {
	    callback_num = i;
	    break;
	    }
	}
    callbacks[callback_num].command = command;
    callbacks[callback_num].help = help;
    callbacks[callback_num].arg_names = arg_names;
    callbacks[callback_num].cbf = cbf;

    if (callback_num == callback_write)
	{
	callback_write++;
	if (callback_write >= CALLBACK_LEN)
	    {
	    callback_write = 0;
	    }
	}
    }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
    Cmd.addKeyIsr((uint8_t) huart1.Instance->DR);
    }
//using namespace cpp_freertos;

ClassCmdTerminal Cmd;
TaskCmd taskCmd;

