#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <time.h>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "workerMeasurement.h"
#include "workerCCD.h"


#define CAM_NUM 9

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(VimbaSystem&	system, QWidget *parent = 0);
	virtual ~MainWindow();

private slots:
	
	void TurnToMeasurement1();
	void TurnToMeasurement2();
	void TurnToMeasurement3();
	void TurnToModeling1();
	void TurnToModeling2();
	void TurnToSettings();
	void TurnToTest();
	void TurnToPreCamera();
	
	
	void PushButton_Save_Pressed();
	void PushButton_Defaults_Pressed();

	
	void PushButton_StartMeasurement_Pressed();
	void PushButton_StopMeasurement_Pressed();
	void PushButton_SampleReset_Pressed();
	void SendingMat(int workerID, QImage mat);

	
	void PushButton_IniCCD_Pressed();
	void PushButton_CaptureContinuously_Pressed();
	void PushButton_Chess_Pressed();
	void PushButton_WhiteBalance_Pressed();
	void PushButton_DeadPixel_Pressed();
	void PushButton_BlackLevel_Pressed();
	void PushButton_FiniCCD_Pressed();

	
	void IsEdited();
	void DisplayImage(int workerID, QImage img);

private:
	Ui::MainWindowClass ui;

	
	WorkerMeasurement*			workerMeasurement;
	QThread*					threadMeasurement;
	WorkerCCD*					workerCCD[9];
	QThread*					threadCCD[9];
	VimbaSystem&				_system;
	QSettings					*ini;
	QString						_qMaterialName;
	bool						_displayFlag;
	int							_measureFlag;
	QMutex						_mutex;

	
	string						_capturePath = "..\\imgs_calibration";
	vector<float>				_trans;
	vector<vector<float>>		_transs;

	void CreateFolds(int flag, string root, string fileName = "");
	inline void ShowImgOnQLabel(QLabel* qlabel, QImage img);

	
	int gain = 0;
	int gain_Int = 0;
	QString gain_Str = "";
	int darkLevel = 0;
	int darkLevel_Int = 0;
	QString darkLevel_Str = "";
	QString imageSaveFormat = "";
	QString imageSaveFormat_Str = "";
	QString imageSavePath = "";
	QString imageSavePath_Str = "";
	QString serialPortSelection = "";
	QString serialPortSelection_Str = "";
	QString baudRate = "";
	QString baudRate_Str = "";
	int delaySetting = 0;
	QString delaySetting_Str = "";
	int lightingSequence = 0;
	QString lightingSequence_Str = "";
	QString stepperMotorPortSelection = "";
	QString stepperMotorPortSelection_Str = "";
	int stepperMotorSpeed_Int = 0;
	QString stepperMotorSpeed = "";
	QString stepperMotorSpeed_Str = "";
	int stepperMotorAcceleration_Int = 0;
	QString stepperMotorAcceleration = "";
	QString stepperMotorAcceleration_Str = "";
	int stepperMotorDeceleration_Int = 0;
	QString stepperMotorDeceleration = "";
	QString stepperMotorDeceleration_Str = "";
	int stepperMotorResolution_Int = 0;
	QString stepperMotorResolution = "";
	QString stepperMotorResolution_Str = "";
	QString sampleRotationAngle = "";
	QString sampleRotationAngle_Str = "";
	QString servoMotorPortSelection = "";
	QString servoMotorPortSelection_Str = "";
	QString servoMotorSpeed = "";
	QString servoMotorSpeed_Str = "";
	QString servoMotorAcceleration = "";
	QString servoMotorAcceleration_Str = "";
	QString servoMotorDeceleration = "";
	QString servoMotorDeceleration_Str = "";
	QString servoMotorResolution = "";
	QString servoMotorResolution_Str = "";
	int slideTableMovingDistance = 0;
	QString slideTableMovingDistance_Str = "";

signals:
	void startTimer(/*int dispalyFlag*/);
	void startMeasure(int measureFlag);
	void sendingMaterialName(QString materialName);
	void sendingMat(int workerID, QImage mat);

};
#endif
