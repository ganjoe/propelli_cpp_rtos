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
#include "iostream"
#include "BoardLed.hpp"
#include "TaskUartSend.hpp"

static int callback_write = 0;


void reset(int argc, const char **argv)
    {
    float f = -1;
    if (argc == 2)
	{
	//scanf(argv[1], "%f", &f);
	Usend.print("\r[CMDKEEN][PARSE]<reset><%f>",3.14);

	//Usend.print("\rdelayed", d);
	//HAL_NVIC_SystemReset();
	}
    }

void dbwrval(int argc, const char **argv)
    {
    float key = -1;
    float value = -1;
    if (argc == 3)
	{
	//scanf(argv[1], "%f", &f);
	key = std::stof(argv[1]);
	value = std::stof(argv[2]);
	Usend.print("\r[CMDKEEN][PARSE] dbwrval %f %f",key, value);

	//Usend.print("\rdelayed", d);
	//HAL_NVIC_SystemReset();
	}
    }




