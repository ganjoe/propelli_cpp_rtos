/*
 * cpp_link.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */
#include "cpp_link.hpp"
#include "mcp23017.hpp"
#include "BoardLed.hpp"

    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init			(void)
    	    {

    	    }
    	void classBoardLed_toggleGreen 	(void) 	{classBoardLed.toggleGreen();}
    	void classBoardLed_toggleRed 	(void) 	{classBoardLed.toggleRed();}
    #ifdef __cplusplus
    	}
    #endif

