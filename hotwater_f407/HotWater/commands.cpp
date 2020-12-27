/*
 * commands.cpp
 *
 *  Created on: Dec 27, 2020
 *      Author: danie
 */

#include "commands.hpp"
#include "stdio.h"
#include "main.h"

void reset(int argc, const char **argv)
    {
    if (argc == 2)
	{
	//term_printf(&btTerm, "\rcmd reset ok:%5fs ok\r", f);
	HAL_NVIC_SystemReset();
	}
    }

