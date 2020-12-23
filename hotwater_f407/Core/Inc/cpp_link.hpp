/*
 * cpp_link.hpp
 *
 *  Created on: 23.12.2020
 *      Author: danie
 */

#ifndef INC_CPP_LINK_HPP_
#define INC_CPP_LINK_HPP_

    #ifdef __cplusplus
    	extern "C"
    	{
    #endif
    	void cpp_init			(void);
    	void classBoardLed_toggleGreen 	(void);
    	void classBoardLed_toggleRed 	(void);
    #ifdef __cplusplus
    	}
    #endif




#endif /* INC_CPP_LINK_HPP_ */
