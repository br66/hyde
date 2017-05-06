#ifndef __TIME_H__
#define __TIME_H__

/*********************************************
* Time.h
* Will deal with all things time. ex. Delta time, currentTime, difference between two times, creating a timer
*
********************************************/

// this function gets the current time in milliseconds from SDL
Uint32 getCurrentTime(void);

// this function sets the current time
void setCurrentTime(void); 

#endif // !__TIME_H__