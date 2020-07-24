#ifndef __ANJIAN_H
#define __ANJIAN_H

#include <sys.h>
#include <GPIO.h>

#define F429 1                                                 

void Anjian_init(void);
int scan(void);
void f429_anjian_init(void);
int read(char *p);
int anjian_inc(void);
#endif



