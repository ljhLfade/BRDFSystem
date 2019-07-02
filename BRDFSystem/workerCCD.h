////////////////////////////Camera相机线程类声明////////////////////////////
#pragma once
#ifndef WORKERCCD_H
#define WORKERCCD_H

#include <QObject>
#include <QImage>
#include <QTimerEvent>
#include <QThread>
#include <QMutex>
#include "workerMeasurement.h"

class WorkerCCD : public QObject
{
	Q_OBJECT

public:
	//WorkerCCD(int workerID, QObject *parent = 0);
	WorkerCCD(int workerID, VimbaSystem& system, QObject *parent = 0);
	virtual ~WorkerCCD();
	virtual void timerEvent(QTimerEvent *event);
	//virtual void run();
	friend class MainWindow;//主界面类需要用到该类的采集图像相关变量

private slots:
	void StartTimer(int measureFlag);

private:
	WorkerMeasurement*		workerMeasurement;
	QThread*				threadMeasurement;

	VimbaSystem&			_system;
	int						_workerID;
	AVTCamera				*_cameraAVT;
	QImage					_img;
	Mat						_mat;
	bool					_capture;
	int						_measurement;
	//int framerate = 0;
	int						_timerId;
	unsigned char*			_pImageFrame;
	int						_height;
	int						_width;

	int						_measureFlag;//主界面传入的采集类型标记
	QMutex					_mutex;

signals:
	void sendingMat(int workerID, Mat mat);
	void sendingImg(int workerID, QImage img);
	void startMeasurement(int measureFlag);
};
#endif

