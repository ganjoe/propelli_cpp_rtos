/*
 * PrettyPrint.h
 *
 *  Created on: Dec 28, 2020
 *      Author: danie
 */

#ifndef HOTWATER_TASKPRETTYPRINTDB_H_
#define HOTWATER_TASKPRETTYPRINTDB_H_

#include "cpp_TaskLink.hpp"
#include "queue.h"
#include "iostream"

#define DBSIZE 12
#define KEYSTRLEN 16

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

    //baseclass implementation
   void setup(uint16_t dbsize);
   void loop();
    /*----------*/
   void storeItem(float item, 	DBKEYS name);
   void storeItem(int item, 	DBKEYS name);

   void getItem(DBKEYS name	, uint32_t* Itembuffer);
   void getItem(DBKEYS name	, float* Itembuffer);

   void setKeyname(char buffer, uint8_t position);
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

   //array as db
   int db32int [ DBSIZE ];
   float db16f [ DBSIZE ];
   char keynames[ DBSIZE * KEYSTRLEN ];


    };

extern PrettyPrint pprint;

class TaskPrettyPrint: public ClassTaskCreate
    {
    public:
	void setup() override
	    {
	    pprint.setup(DBSIZE);
	    }
	void loop() override
	    {
	    pprint.loop();
	    }
    };

extern TaskPrettyPrint taskPP;

#endif /* HOTWATER_TASKPRETTYPRINTDB_H_ */
