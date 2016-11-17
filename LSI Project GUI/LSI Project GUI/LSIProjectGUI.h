#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"
#include "FrameClass.h"
#include "ROIclass.h"
//
#include <QColor>
#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <opencv/cv.h>
#include <iostream>
#include <FlyCapture2.h>
#include <QVector>
using namespace std;
using namespace FlyCapture2;
using namespace cv;


class LSIProjectGUI : public QMainWindow
{
	Q_OBJECT

public:
	LSIProjectGUI(QWidget *parent = Q_NULLPTR);
	Frame Frame_Object;
	QPixmap Main_Image;
	QPixmap temp_Main_Image;
	Mat Main_Image_CV;
	Image rgbImage;
	Image rawImage;
	Camera camera;
	VideoCapture webcam;
	vector<cv::Mat> Contrast_Images;
	
private:
	Ui::LSIProjectGUIClass ui;
	vector<ROI> List_Of_ROI;
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
	QTimer *timer;
	int i = 0;
	int color_index;
	//QVector<QColor> ROI_Colors; // would like to have it here but doesn't work
	int refresh_rate; //How often the update function will be called in mS
	int exposure_time; //Exposure time in mS
	int lasca_area;
	bool should_i_run;
	int x_max;
	int x_min;
	int graph_update;
	void set_exposure(int);
	QVector<qreal> b;
	//

	public slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
	//
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void update();
	//
	void on_LASCAarea_valueChanged();
	void on_exposuretime_valueChanged();
	//Real time hanterarn
	private slots:
		void makePlot(QVector<qreal>);
};
