/*
 * BoardLed.cpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */

#include "BoardLed.hpp"
#include "main.h"
#include "cmsis_os.h""


void _classBoardLed::toggleGreen()
    {
    HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);
    vTaskDelay(1000);
    }

void _classBoardLed::toggleRed()
    {
    HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
    vTaskDelay(200);
    }

_classBoardLed classBoardLed;


