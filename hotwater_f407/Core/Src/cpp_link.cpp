/*
 * cpp_link.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */
#include "cpp_TaskLink.hpp"
#include "cpp_link.hpp"
#include "mcp23017.hpp"
#include "BoardLed.hpp"


    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init(void)
    	    {
    	  taskLedGreen.start("BlinkGreen", 128, 2);
    	  taskLedRed.start("BlinkRed", 128, 2);
    	  mcp.init(0x20<<1, &hi2c1);
    	  //taskMcp.setup();	//call an anderer stelle zu mcp.init
    	  taskMcp.start("mcp_io", 128, 1);
    	    }

    #ifdef __cplusplus
    	}
    #endif

