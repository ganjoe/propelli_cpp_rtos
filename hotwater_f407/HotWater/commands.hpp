/*
 * commands.hpp
 *
 *  Created on: Dec 27, 2020
 *      Author: danie
 */

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

    #ifdef __cplusplus
    	extern "C"
    	{
    #endif


void term_lol_setCallback(const char *command,
			     const char *help,
			     const char *arg_names,
			     void (*cbf)(int argc, const char **argv));


//	config
void reset	(int argc, const char **argv);
void dbReadVal	(int argc, const char **argv);
void dbwrval	(int argc, const char **argv);
void dbReadKey	(int argc, const char **argv);
void dbWriteKey	(int argc, const char **argv);

void dbFindKey	(int argc, const char **argv);



/*
void selterm(int argc, const char **argv);
void selhhw(int argc, const char **argv);
void settime(int argc, const char **argv);
void setdate(int argc, const char **argv);
//	gpios setzen
void setword(int argc, const char **argv);
void writepin(int argc, const char **argv);
void readpin(int argc, const char **argv);
void setallin(int argc, const char **argv);
void setword(int argc, const char **argv);
//
void sdwrite(int argc, const char **argv);
void sdread(int argc, const char **argv);
void readinit(int argc, const char **argv);
void writeinit(int argc, const char **argv);
void clearinit(int argc, const char **argv);
void readrom(int argc, const char **argv);
void writerom(int argc, const char **argv);
void clearrom(int argc, const char **argv);
void nlog(int argc, const char **argv);
void nlogn(int argc, const char **argv);
void vrange(int argc, const char **argv);
void mode(int argc, const char **argv);
void trange(int argc, const char **argv);
*/

    #ifdef __cplusplus
    	}
    #endif
#endif /* COMMANDS_HPP_ */
