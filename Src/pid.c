#include "pid.h"


#define LIMIT(x,min,max) x=(x<(min)?min:((x>=max)?max:x))


/*位置pid*/
void WZPid(WZPID_TypeDef *WZpid,float target,float real)
{
 WZpid->error_last=WZpid->error;
 WZpid->error=target-real;
 WZpid->output=(WZpid->error-WZpid->error_last)*WZpid->Kd;//微分部分
 WZpid->output+=(WZpid->error*WZpid->Kp);//误差部分
 WZpid->integral+=(WZpid->error*WZpid->Ki);//积分部分 
 LIMIT(WZpid->integral,-WZpid->integral_max,WZpid->integral_max);
 WZpid->output+=WZpid->integral;
 LIMIT(WZpid->output,-WZpid->output_max,WZpid->output_max);
}

void JD_WZPid(WZPID_TypeDef *WZpid,float target,float real)
{
 WZpid->error_last=WZpid->error;
 WZpid->error=target-real;
 if(WZpid->error>4096) WZpid->error=target-real-8192;
 if(WZpid->error<-4096) WZpid->error=8192+target-real;
 if(WZpid->error<3&WZpid->error>-3) WZpid->error=0;
 WZpid->output=(WZpid->error-WZpid->error_last)*WZpid->Kd;//微分部分
 WZpid->output+=(WZpid->error*WZpid->Kp);//误差部分
 WZpid->integral+=(WZpid->error*WZpid->Ki);//积分部分 
 LIMIT(WZpid->integral,-WZpid->integral_max,WZpid->integral_max);
 WZpid->output+=WZpid->integral;
 LIMIT(WZpid->output,-WZpid->output_max,WZpid->output_max);
}

/*增量pid*/
void ZLPid(ZLPID_TypeDef *ZLpid,float target,float real)
{
 ZLpid->error_last=ZLpid->error;
 ZLpid->error_last_last=ZLpid->error_last;
 ZLpid->error=target-real;
 ZLpid->outputI=(ZLpid->error-ZLpid->error_last)*ZLpid->Kp;
 ZLpid->outputI+=ZLpid->error*ZLpid->Ki;
 ZLpid->outputI+=(ZLpid->error+ZLpid->error_last_last-2*ZLpid->error_last)*ZLpid->Kd;
 LIMIT(ZLpid->outputI,-ZLpid->outputI_max,ZLpid->outputI_max);
 ZLpid->output+=ZLpid->outputI;
 LIMIT(ZLpid->output,-ZLpid->output_max,ZLpid->output_max);
}


/*位置pid赋值*/
void WZPid_Init(WZPID_TypeDef *WZpid,float p,float i,float d,float Integral_max,float Out_max)
{
 WZpid->Kp=p;
 WZpid->Ki=i;
 WZpid->Kd=d;
 WZpid->integral_max=Integral_max;
 WZpid->output_max=Out_max;
}


/*增量pid赋值*/
void ZLPid_Init(ZLPID_TypeDef *ZLpid,float p,float i,float d,float Intergral_max,float Out_max)
{
ZLpid->Kp=p;
ZLpid->Ki=i;
ZLpid->Kd=d;
ZLpid->outputI_max=Intergral_max;
ZLpid->output_max=Out_max;
}


/*各个pid初始化*/
PID_TypeDef Pid;
void All_Pid_Init(void)
{
 ZLPid_Init(&Pid.ZL.No1,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No2,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No3,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No4,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No5,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No6,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.No7,15,0.5,0.5,16000,16000);
 ZLPid_Init(&Pid.ZL.pitch,0.2,0.5,0,120,3000);
 WZPid_Init(&Pid.WZ.pitch,3.5,0,0,5000,5000);
 WZPid_Init(&Pid.WZ.pitch_angle,2,0,0,600,600);
 WZPid_Init(&Pid.WZ.yaw,7,0,0,5000,5000);
 WZPid_Init(&Pid.WZ.yaw_angle,5,0,0,600,600);
}

