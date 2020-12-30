/*
 * PrettyPrint.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: danie
 */

#include <hotwater/TaskPrettyPrintDB.h>
#include "string.h"



void PrettyPrint::setup(uint16_t dbsize)
    {

    }

void PrettyPrint::loop()
    {

    }

void PrettyPrint::storeItem(float item, DBKEYS name)
    {
    db16f[name] = item;
    }

void PrettyPrint::storeItem(int item, DBKEYS name)
    {
    db32int[name] = item;
    }

void PrettyPrint::getItem(DBKEYS name	, uint32_t* Itembuffer)
    {
    *Itembuffer = db32int[ name ];
    }

void PrettyPrint::getItem(DBKEYS name	, float* Itembuffer)
    {
    *Itembuffer = db16f [ name ];
    }

void PrettyPrint::setKeyname(char buffer, uint8_t position)
    {
  //  char* namebuf = ( char* ) calloc ( KEYSTRLEN, 1);
    memccpy(&keynames[position], &buffer, KEYSTRLEN, 1);
    }

void PrettyPrint::getKeyname(uint8_t* buffer, uint8_t position)
    {
    memccpy(&buffer, &keynames[position], KEYSTRLEN, 1);    }

TaskPrettyPrint taskPP;
PrettyPrint pprint;
