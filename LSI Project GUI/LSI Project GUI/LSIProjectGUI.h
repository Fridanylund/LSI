#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"
#include <FrameClass.h>


using namespace std;

class LSIProjectGUI : public QMainWindow
{
    Q_OBJECT

public:
    LSIProjectGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::LSIProjectGUIClass ui;
	bool run = true;
	Frame frame_object;
	Image rgbImage;
	Image rawImage;
	Camera BW_Cam;
	QTimer *timer;


public slots: 
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
	void test_loop();
	void timertest();
	void update();
};
