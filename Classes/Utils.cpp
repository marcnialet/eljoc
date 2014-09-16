//
//  Utils.cpp
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#include "Utils.h"

double Utils::getTimeTick()
{
    timeval time;
    gettimeofday(&time, NULL);
    double millisecs = ((double)time.tv_sec * (double)1000.0) + ((double)time.tv_usec/(double)1000.0);
    return millisecs;
}

string Utils::formatMilliseconds(double  timeinMs)
{
    long milliseconds = timeinMs;
    long seconds = milliseconds / 1000.0;
    long minutes = seconds / 60.0;
    long hours = minutes / 60.0;
    
    char formattime[64];
    sprintf(formattime, "%02ld:%02ld:%02ld.%03ld", hours, minutes, seconds, milliseconds);
    return formattime;
}
int Utils::myrandom (int i) { return std::rand()%i;}