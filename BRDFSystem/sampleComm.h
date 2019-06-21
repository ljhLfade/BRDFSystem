///////////////////////////////////材质样品台步进电机驱动控制类/////////////////////////////////
//功能：控制步进电机驱动器MSST5 - S, 从而驱动AMP电机完成材质台样品平面旋转

////////////////////////////////电机命令释义////////////////////////////////////
/*
// 设置电机为计算机控制
PM2:  Power - up Mode以Q / SCL模式上电；
SA : Save Parameters保存参数数据；
SS : Send String发送字符串；（SSdone : 当SS执行时发送“done”）

// 设置电机参数（加速度、速度等）
AC : Acceleration Rate加速度；
VE : Velocity速度；
DE : Deceleration减速度；
MR : Microstep Resolution 微步调分辨率；
DI : Distance / Position 距离，位置；
FL : Feed to Length 按一定长度提供参数；
DC : Change Distance 改变距离；
FY3L : (FY)Feed to Sensor with Safety Distance安全距离内提供传感器参数；
DL1 : Define Limits 定义限制，设置限制输入与常开限制开关一起工作；
AL : Alarm Code 报警代码；
AR : Alarm Reset(Immediate) 报警复位（直接）
*/

#pragma once
#ifndef SAMPLECOMM_H
#define SAMPLECOMM_H

#include "stdafx.h"
#include "cnComm.h"

#define STEP_FEEDBACK      "DONE"    //电机反馈标识
#define STEP_ACCELERATE    5       //电机加速度
#define STEP_DECELERATE    5       //电机减速度
#define STEP_RESOLUTION    8        //电机分辨率
#define STEP_TIMEOUT       120000   //超时,毫秒
#define STEP_SAFESTEP     500000	 //归位电机保护步数,最多转这么多步后会停下来

class SampleComm : public CRs232Comm
{
public:
	SampleComm();
	virtual ~SampleComm();
	
	//初始化设备
    bool Init(int wheel_port, int wheel_step, double velocity, int accelerate, int decelerate, int resolution, int wheel_homeadj);
	bool Init(int wheel_port);
	//调整到下一个通道的位置
	bool  GotoNextPos(int step);
	//设置速度
	bool SetVel(double v);
	//归位
	bool Reset();
	//停止设备
	void Fini();



private:
	int m_step;             //转到下一通道电机需要移动的步数
	int m_homeadj;          //归位时电机需要移动的步数
    int m_port;             //电机连接的串口	
	int m_accelerate;       //电机加速度
	int m_decelerate;       //电机减速度
	int m_resolution;       //电机分辨率
	double m_velocity;      //电机速度

	//确认电机已经完成当前指令
	bool IsFinished(int wait_time);
	//时间等待函数
	void Wait(int millisec);

};
#endif
