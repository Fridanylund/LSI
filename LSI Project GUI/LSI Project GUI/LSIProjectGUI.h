#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"
//#include "ROIclass.h"
#include "Test-function.h"
//
#include <QWidget>
#include <QMouseEvent>
#include <QImage>
#include <QString>
#include <QPainter>
#include <QPen>
#include <opencv/cv.h>
#include <iostream>
#include <QVector>
using namespace std;

//


class LSIProjectGUI : public QMainWindow
{
    Q_OBJECT

public:
    LSIProjectGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::LSIProjectGUIClass ui;
	//vector<ROI> List_Of_ROI;
	bool Is_ROI_Button_Is_Pressed;
	QPoint Start_Click_Coordinates;
	int x_Start_Click_Coordinate;
	int y_Start_Click_Coordinate;
	QPoint videoLabel_Coordinates;
	int x_videoLabel_Coordinate;
	int y_videoLabel_Coordinate;
	int x_Start_ROI_Coordinate;
	int y_Start_ROI_Coordinate;
	QPoint Start_ROI_Coordinates;
	int x_End_ROI_Coordinate;
	int y_End_ROI_Coordinate;
	int ROI_Width;
	int ROI_Height;
	QPen pen;
	//

public slots: 
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
	//
	void on_listROI_itemClicked(QListWidgetItem * item);
	//
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//
};
