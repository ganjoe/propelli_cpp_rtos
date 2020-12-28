/*
 * commands.cpp
 *
 *  Created on: Dec 27, 2020
 *      Author: danie
 */

#include "commands.hpp"

#include "CmdKeen.hpp"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include "BoardLed.hpp"

static int callback_write = 0;


void reset(int argc, const char **argv)
    {
    if (argc == 2)
	{
	int i =315;

	BoardLed.toggleGreen();

	Cmd.pprint("\rcmd reset ok %d\r", i);
	//HAL_NVIC_SystemReset();
	}
    }
void term_lol_setCallback(const char *command,
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
void RegisterCommand()
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



