/*
 * TutorialClass.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: danie
 */

#ifndef CPP_TASKLINK_HPP_
#define CPP_TASKLINK_HPP_
#include "main.h"
#include "cmsis_os.h"


class ClassTaskCreate
    {
public:
    virtual ~ClassTaskCreate()
	{
	}
    inline void start(const char *const pcName, const uint16_t usStackDepth,
	    UBaseType_t uxPriority)
	{
	this->stopCalled = false;
	xTaskCreate(ClassTaskCreate::bootstrap, pcName, usStackDepth, this, uxPriority,
		&this->xHandle);
	}
    inline void stop()
	{
	this->stopCalled = true;
	}

protected:
    inline void sleep(int time_ms)
	{
	vTaskDelay(time_ms / portTICK_PERIOD_MS);
	}

private:
    virtual void setup()
	{
	}
    virtual void loop()
	{
	}
    virtual void cleanup()
	{
	}

    static void bootstrap(void *pvParameters)
	{
	//Sachen passieren
	ClassTaskCreate *taskObject = reinterpret_cast<ClassTaskCreate*>(pvParameters);
	taskObject->setup();
	while (!taskObject->stopCalled)
	    {
	    taskObject->loop();
	    }
	// task clean up
	taskObject->cleanup();
	vTaskDelete(taskObject->xHandle);
	}
    bool stopCalled = false;
    TaskHandle_t xHandle = 0;
    };
/*
class MFBoardLed: public ClassTaskCreate
    {
private:

    void loop() override
	{
	classBoardLed.toggleGreen();
	}

    };
extern MFBoardLed mfBoardLed;
*/
#endif /* CPP_TASKLINK_HPP_ */
