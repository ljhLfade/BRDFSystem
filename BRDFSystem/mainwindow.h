#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QDebug>
//#include <QTimerEvent>
#include <QFileDialog>
#include <time.h>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "slideComm.h"
#include "sampleComm.h"
#include "ccd.h"
#include "workerCCD.h"
//#include "configuration.h"

#define CAM_NUM 2  //相机数量

////////////////////////////界面主线程类声明////////////////////////////
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(VimbaSystem&	system, QWidget *parent = 0);
	virtual ~MainWindow();

private:
	Ui::MainWindowClass ui;

	SlideComm*					slideComm;
	SampleComm*					sampleComm;
	WorkerCCD*					workerCCD[9];
	QThread*					threadCCD[9];
	VimbaSystem&				_system;
	//VimbaSystem&				_system = VimbaSystem::GetInstance();//相机的SDK-Vimba系统
																	 //为了避免每个相机线程重复开启Vimba系统，只能暂时吧该引用提到最上层
	QString _qMaterialName;
	bool _displayFlag;

private slots:
	//页面切换栏
	void TurnToMeasurement1();
	void TurnToMeasurement2();
	void TurnToMeasurement3();
	void TurnToModeling1();
	void TurnToModeling2();
	void TurnToSettings();
	void TurnToTest();
	void TurnToPreCamera();
	
	//材质采集页面
	void PushButton_StartMeasurement_Pressed();
	void StopMeasurement();
	void ConnectRGB();

	//相机预处理页面
	void PushButton_IniCCD_Pressed();
	void PushButton_CaptureContinuously_Pressed();


	//槽函数的公用函数
	//不知道有没有更好的写法
	void DisplayImage0(QImage img);
	void DisplayImage1(QImage img);
	void DisplayImage2(QImage img);
	void DisplayImage3(QImage img);
	void DisplayImage4(QImage img);
	void DisplayImage5(QImage img);
	void DisplayImage6(QImage img);
	void DisplayImage7(QImage img);
	void DisplayImage8(QImage img);

signals:
	void startTimer();
	//void startMeasureMent();
};
#endif
