/* 
 * File:   Timer.h
 * Author: GJ Fouche
 *
 * Created on 22 September 2015, 12:49 PM
 */
#include <time.h>

#ifndef TIMER_H
#define	TIMER_H

class AITimer {
public:
    AITimer();
    AITimer(const AITimer& orig);
    virtual ~AITimer();
    
    void start();
    unsigned long elapsedTime();
    bool isTimeout(unsigned long seconds);
    
private:
    unsigned long begTime;
};

#endif	/* TIMER_H */

