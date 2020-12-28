/*
 * PrettyPrint.h
 *
 *  Created on: Dec 28, 2020
 *      Author: danie
 */

#ifndef TASKPRETTYPRINT_H_
#define TASKPRETTYPRINT_H_

#include "cpp_TaskLink.hpp"
#include "queue.h"

typedef enum
{
    DATE,
    TIME,
    OSTICKS,
    CPUTEMP,
    CPUVOLT,
}
DBKEYS;

typedef enum
{
    DB_OK = 1,
    DB_FAULT_BUFFER,
    DB_FAULT_MEDIA,
}
DBRETURN;

class PrettyPrint
    {
    public:
    /*----------*/
   int storeItem(float item, 	DBKEYS name);
   int storeItem(int32_t item, 	DBKEYS name);

   int getItem(DBKEYS name	, uint32_t* Itembuffer);
   int getItem(DBKEYS name	, float* Itembuffer);

   void setKeyname(uint8_t* buffer, uint8_t position);
   void getKeyname(uint8_t* buffer, uint8_t position);
   /*----------*/

   //printout all keynames
   void printHeader(char* 	buffer, uint8_t buffsize);
   void printHeader(QueueHandle_t* buffer, uint8_t buffsize);

   //printout all values
   void printData(char* buffer, uint8_t buffsize);
   void printData(QueueHandle_t* buffer, uint8_t buffsize);

   //printout key-value
   void printPairs(char* buffer, uint8_t buffsize);
   void printPairs(QueueHandle_t* buffer, uint8_t buffsize);

    private:
    };


class TaskPrettyPrint: public ClassTaskCreate
    {
    public:
	void setup() override
	{

	}
	void loop() override
	{

	}
    };

extern TaskPrettyPrint taskPrettyPrint;

#endif /* TASKPRETTYPRINT_H_ */
