 /*
 * BoardLed.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */


#ifndef INC_BOARDLED_HPP_
#define INC_BOARDLED_HPP_




class ClassBoardLed
    {
    public:
    void toggleRed();
    void toggleGreen();
    };


extern ClassBoardLed	LedRed;
extern ClassBoardLed 	LedGreen;




#endif /* INC_BOARDLED_HPP_ */
