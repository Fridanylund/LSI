#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"

class LSIProjectGUI : public QMainWindow
{
    Q_OBJECT

public:
    LSIProjectGUI(QWidget *parent = Q_NULLPTR);
	// bool Get_Run_Real_Time();

private:
    Ui::LSIProjectGUIClass ui;
	// bool Run_Real_Time;

public slots: 
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
};
