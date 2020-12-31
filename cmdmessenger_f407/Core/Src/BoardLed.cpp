/*
 * BoardLed.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */

#include "BoardLed.hpp"




void ClassBoardLed::toggleGreen()
    {
    HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);

    }

void ClassBoardLed::toggleRed()
    {
    HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);

    }
ClassBoardLed	LedRed;
ClassBoardLed 	LedGreen;

