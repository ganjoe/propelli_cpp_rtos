 /*
 * BoardLed.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */
#include "FreeRTOS.h"

#ifndef INC_BOARDLED_HPP_
#define INC_BOARDLED_HPP_

class _classBoardLed
    {
public:
    void toggleRed();
    void toggleGreen();

private:
};

extern _classBoardLed classBoardLed;


#endif /* INC_BOARDLED_HPP_ */
