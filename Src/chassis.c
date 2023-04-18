#include "chassis.h"
#include "gimbal.h"


void chassis_Judge(void)
{
if(Remote_Control.Rc.s1==1)
{
 remote_control();
}
if(Remote_Control.Rc.s1==3)
{
 Data_Count();
 ChassisData_processing();
}
if(Remote_Control.Rc.s1==2)
{
 Data_Count();
 ChassisData_processing2();
}

}


void remote_control(void)
{
  MotoData.moto_1.Tx.target_speed=(-Remote_Control.Rc.y-Remote_Control.Rc.x+Remote_Control.Rc.roller);
  MotoData.moto_2.Tx.target_speed=(Remote_Control.Rc.y-Remote_Control.Rc.x+Remote_Control.Rc.roller);
  MotoData.moto_3.Tx.target_speed=(-Remote_Control.Rc.y+Remote_Control.Rc.x+Remote_Control.Rc.roller);
  MotoData.moto_4.Tx.target_speed=(Remote_Control.Rc.y+Remote_Control.Rc.x+Remote_Control.Rc.roller); 
}


#define Chassis_Turn_Sent 5 //底盘转向灵敏度调整
#define speed_add 2  //shift键底盘加速倍率


int Data_WS,Data_AD;
int WS_Count,AD_Count;


void Data_Count(void)
{
 if(Remote_Control.Key.W==1) WS_Count=1000;
 if(Remote_Control.Key.S==1) WS_Count=-1000; 
 if(Remote_Control.Key.S==0&Remote_Control.Key.W==0) WS_Count=0;
 if(Remote_Control.Key.D==1) AD_Count=1000;
 if(Remote_Control.Key.A==1) AD_Count=-1000;
 if(Remote_Control.Key.A==0&Remote_Control.Key.D==0) AD_Count=0;
 }

 
 void ChassisData_processing(void)
 {
  MotoData.moto_1.Tx.target_speed=(-WS_Count-AD_Count-Remote_Control.Mouse.X*Chassis_Turn_Sent);
  MotoData.moto_2.Tx.target_speed=(WS_Count-AD_Count-Remote_Control.Mouse.X*Chassis_Turn_Sent);
  MotoData.moto_3.Tx.target_speed=(-WS_Count+AD_Count-Remote_Control.Mouse.X*Chassis_Turn_Sent);
  MotoData.moto_4.Tx.target_speed=(WS_Count+AD_Count-Remote_Control.Mouse.X*Chassis_Turn_Sent); 
	if(Remote_Control.Key.Shift)
  {
   MotoData.moto_1.Tx.target_speed=MotoData.moto_1.Tx.target_speed*speed_add;
   MotoData.moto_2.Tx.target_speed=MotoData.moto_2.Tx.target_speed*speed_add;
   MotoData.moto_3.Tx.target_speed=MotoData.moto_3.Tx.target_speed*speed_add;
   MotoData.moto_4.Tx.target_speed=MotoData.moto_4.Tx.target_speed*speed_add;
  }
 }

 void ChassisData_processing2(void)
 {
  MotoData.moto_1.Tx.target_speed=2*(-WS_Count*inc_x-AD_Count*inc_x2);
  MotoData.moto_2.Tx.target_speed=2*(WS_Count*inc_y+AD_Count*inc_y2);
  MotoData.moto_3.Tx.target_speed=2*(-WS_Count*inc_y-AD_Count*inc_y2);
  MotoData.moto_4.Tx.target_speed=2*(WS_Count*inc_x+AD_Count*inc_x2); 
	 	if(Remote_Control.Key.Shift)
  {
   MotoData.moto_1.Tx.target_speed=MotoData.moto_1.Tx.target_speed*speed_add;
   MotoData.moto_2.Tx.target_speed=MotoData.moto_2.Tx.target_speed*speed_add;
   MotoData.moto_3.Tx.target_speed=MotoData.moto_3.Tx.target_speed*speed_add;
   MotoData.moto_4.Tx.target_speed=MotoData.moto_4.Tx.target_speed*speed_add;
  }

 }
 