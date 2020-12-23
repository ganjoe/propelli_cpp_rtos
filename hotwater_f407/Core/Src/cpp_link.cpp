/*
 * cpp_link.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */
#include "cpp_link.hpp"
#include "mcp23017.hpp"
#include "BoardLed.hpp"
#include "TutorialClass.hpp"


    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init(void)
    	    {
    	    mfBoardLed.start("BlinkGreen", 1200, 1);
    	    }

    #ifdef __cplusplus
    	}
    #endif

