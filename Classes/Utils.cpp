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

int Utils::myrandom (int i) { return std::rand()%i;}