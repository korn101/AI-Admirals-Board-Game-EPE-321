/* 
 * File:   Timer.cpp
 * Author: GJ Fouche
 * 
 * Created on 22 September 2015, 12:49 PM
 */

#include "AITimer.h"

AITimer::AITimer() {
}

AITimer::AITimer(const AITimer& orig) {
}

AITimer::~AITimer() {
}

void AITimer::start()
{
    begTime = clock();
}

unsigned long AITimer::elapsedTime()
{
    return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
}

bool AITimer::isTimeout(unsigned long seconds)
{
    return seconds >= elapsedTime();
}