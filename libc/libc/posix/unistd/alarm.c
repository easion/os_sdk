/* Copyright (C) 1995 Charles Sandmann (sandmann@clio.rice.edu)
   alarm() implmentation using setitimer 
   This software may be freely distributed, no warranty. */
#include <unistd.h>
#include <sys/time.h>

unsigned int alarm(unsigned int seconds)
{
 return _alarm(seconds);
}
