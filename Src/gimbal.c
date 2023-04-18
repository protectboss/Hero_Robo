#include "gimbal.h"

#define pitch_high 8170
#define pitch_low 6300
#define yaw_middle 4587

int flag1=0;
void Gimbal_Judge(void)
{
 if(Remote_Control.Rc.s1==1)
 {
	Gimbal_RC();
 }
 if(Remote_Control.Rc.s1==3)
 {
  Gimbal_follow();
	flag1=0;
 }
 if(Remote_Control.Rc.s1==2)
 {
 Gimbal_RC2();
 }
}

void Gimbal_follow(void)//用来赶路使用
{
 JD_WZPid(&Pid.WZ.yaw_angle,yaw_middle,MotoData.yaw.Rx.angle);
 MotoData.yaw.Tx.target_speed=-Pid.WZ.yaw_angle.output;
	

 MotoData.pitch.Tx.angle_target-=Remote_Control.Mouse.Y/30;
 if(MotoData.pitch.Tx.angle_target>pitch_high) MotoData.pitch.Tx.angle_target=pitch_high;
 if(MotoData.pitch.Tx.angle_target<pitch_low) MotoData.pitch.Tx.angle_target=pitch_low;
 JD_WZPid(&Pid.WZ.pitch_angle,MotoData.pitch.Tx.angle_target,MotoData.pitch.Rx.angle);
 MotoData.pitch.Tx.target_speed=-Pid.WZ.pitch_angle.output;
}

void Gimbal_RC(void)
{
	if(MotoData.yaw.Rx.flag==1)
	{
	 if(flag1==0)
	 {
		 MotoData.yaw.Tx.angle_target=MotoData.yaw.Rx.angle;
		 flag1=1;
	 }
	 MotoData.yaw.Tx.angle_target-=Remote_Control.Rc.yaw/30;
	 if(MotoData.yaw.Tx.angle_target>8191)MotoData.yaw.Tx.angle_target=MotoData.yaw.Tx.angle_target-8192;
	 if(MotoData.yaw.Tx.angle_target<0)MotoData.yaw.Tx.angle_target=8192-MotoData.yaw.Tx.angle_target;
	 JD_WZPid(&Pid.WZ.yaw_angle,MotoData.yaw.Tx.angle_target,MotoData.yaw.Rx.angle);
	 MotoData.yaw.Tx.target_speed=-Pid.WZ.yaw_angle.output;
	}
	
		if(MotoData.pitch.Rx.flag==1)
	{
	 MotoData.pitch.Tx.angle_target+=Remote_Control.Rc.pitch/30;
	 if(MotoData.pitch.Tx.angle_target>pitch_high) MotoData.pitch.Tx.angle_target=pitch_high;
	 if(MotoData.pitch.Tx.angle_target<pitch_low) MotoData.pitch.Tx.angle_target=pitch_low;
	 JD_WZPid(&Pid.WZ.pitch_angle,MotoData.pitch.Tx.angle_target,MotoData.pitch.Rx.angle);
	 MotoData.pitch.Tx.target_speed=-Pid.WZ.pitch_angle.output;
	}
}

void Gimbal_RC2(void)
{
if(MotoData.yaw.Rx.flag==1)
	{
	 if(flag1==0)
	 {
		 MotoData.yaw.Tx.angle_target=MotoData.yaw.Rx.angle;
		 flag1=1;
	 }
	 MotoData.yaw.Tx.angle_target-=Remote_Control.Mouse.X/30;
	 if(MotoData.yaw.Tx.angle_target>8191)MotoData.yaw.Tx.angle_target=MotoData.yaw.Tx.angle_target-8192;
	 if(MotoData.yaw.Tx.angle_target<0)MotoData.yaw.Tx.angle_target=8192-MotoData.yaw.Tx.angle_target;
	 JD_WZPid(&Pid.WZ.yaw_angle,MotoData.yaw.Tx.angle_target,MotoData.yaw.Rx.angle);
	 MotoData.yaw.Tx.target_speed=-Pid.WZ.yaw_angle.output;
	}
	
 MotoData.pitch.Tx.angle_target-=Remote_Control.Mouse.Y/30;
 if(MotoData.pitch.Tx.angle_target>pitch_high) MotoData.pitch.Tx.angle_target=pitch_high;
 if(MotoData.pitch.Tx.angle_target<pitch_low) MotoData.pitch.Tx.angle_target=pitch_low;
 JD_WZPid(&Pid.WZ.pitch_angle,MotoData.pitch.Tx.angle_target,MotoData.pitch.Rx.angle);
 MotoData.pitch.Tx.target_speed=-Pid.WZ.pitch_angle.output;
}


#include <math.h>
double inc_x, inc_y;
double inc_x2, inc_y2;
#define pi 3.1415926535898
#define DEC (pi/180)
double Turn_Data=0;
double Turn_Data2=0;
void Gimbal_Turn(void)
{
 Turn_Data=MotoData.yaw.Rx.angle-yaw_middle+1024;
 Turn_Data=Turn_Data*360/8192;
 Turn_Data2=Turn_Data-90;
 inc_y = sin(Turn_Data* DEC);
 inc_x = cos(Turn_Data* DEC);
 inc_y2 = sin(Turn_Data2* DEC);
 inc_x2 = cos(Turn_Data2* DEC);
}


