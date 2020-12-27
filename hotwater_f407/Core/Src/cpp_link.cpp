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

    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init(void)
    	    {
    	    uint8_t* dData;

    	    taskMcp.setup();
    	    taskCmd.setup();
    	   uint8_t* pData;
  	    HAL_UART_Receive_DMA(&huart1, pData, 1);
    	    taskLedGreen.start("BlinkGreen", 128, 2);
    	    taskLedRed.start("BlinkRed", 128, 2);
    	    taskMcp.start("mcp_io", 128, 1);
    	    taskCmd.start("TermGetKey", 256, 1);
    	    }

    #ifdef __cplusplus
    	}
    #endif

