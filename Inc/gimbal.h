#ifndef __GIMBAL_H_
#define __GIMBAL_H_


#include "remote_control.h"
#include "gimbal.h"
#include "pid.h"

void Gimbal_RC(void);
void Gimbal_RC2(void);
void Gimbal_follow(void);
void Gimbal_Judge(void);
void Gimbal_Turn(void);

extern double inc_x, inc_y;
extern double inc_x2, inc_y2;
extern double Turn_Data;
extern double Turn_Data2;

#endif
