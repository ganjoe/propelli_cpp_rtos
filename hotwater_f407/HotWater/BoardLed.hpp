 /*
 * BoardLed.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */


#ifndef INC_BOARDLED_HPP_
#define INC_BOARDLED_HPP_
#include "cpp_TaskLink.hpp"



class ClassBoardLed
    {
    public:
    void toggleRed();
    void toggleGreen();
    };

extern ClassBoardLed 	BoardLed;

class TaskLedRed: public ClassTaskCreate
    {

public:
       void loop() override
	{
	BoardLed.toggleRed();
	osDelay(20);
	}
};

class TaskLedGreen: public ClassTaskCreate
    {

public:
       void loop() override
	{
	BoardLed.toggleGreen();
	osDelay(50);
	}
};

extern TaskLedRed	taskLedRed;
extern TaskLedGreen 	taskLedGreen;




#endif /* INC_BOARDLED_HPP_ */
