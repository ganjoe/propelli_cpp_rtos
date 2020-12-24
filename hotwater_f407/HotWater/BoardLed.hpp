 /*
 * BoardLed.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */


#ifndef INC_BOARDLED_HPP_
#define INC_BOARDLED_HPP_
#include "cpp_TaskLink.hpp"

class MFBoardLed: public ClassTaskCreate
    {
public:
       void loop() override
	{
	toggleGreen();
	osDelay(200);
	}
    void toggleRed();
    void toggleGreen();

private:

};


extern MFBoardLed classBoardLed;




#endif /* INC_BOARDLED_HPP_ */
