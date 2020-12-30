/*
 * cpp_link.cpp
 *
 *  Created on: 23.12.2020
 *      Author: daniel
 */
#include "cpp_TaskLink.hpp"
#include "cpp_link.hpp"
#include "mcp23017.hpp"
#include "BoardLed.hpp"
#include "CmdKeen.hpp"
#include "TaskPrettyPrint.h"
#include "TaskUartSend.hpp"

    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init(void)
    	    {
    	    //setup params are hidden inside
    	    taskMcp.setup();
    	    taskCmd.setup();
    	    taskPP.setup();
    	    taskUsend.setup();

    	    //receive dummybytes.
    	    //if any received a handler in isr is called
    	    uint8_t* pData=0;
  	    HAL_UART_Receive_DMA(&huart1, pData, 1);

  	    //most useful task: blinking leds
    	    taskLedGreen.start("BlinkGreen", 128, 2);
    	    taskLedRed.start("BlinkRed", 128, 2);

    	    //shadowing io register for easy access
    	    taskMcp.start("mcp_io", 128, 1);
    	    taskCmd.start("TermGetKey", 256, 1);
    	    taskUsend.start("uart_io", 128, 1);
    	    }

    #ifdef __cplusplus
    	}
    #endif

