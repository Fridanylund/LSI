#pragma once
#include <windows.h>
#include <QtWidgets/QMainWindow>
#include "ui_LSIProjectGUI.h"
#include "FrameClass.h"
#include "ROIclass.h"
#include "Free-Functions.h"
#include "qcustomplot.h"
//
#include <QColor>
#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QSerialPort>
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
	Mat Raw_im;
	Mat Raw_temp;
	Mat Black_im;
	QPixmap temp_Main_Image;
	Mat Main_Image_CV;
	Image rgbImage;
	Image rawImage;
	Camera camera;
	VideoCapture webcam;
	QSerialPort *port;
	
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
	int refresh_rate; //How often the update function will be called in mS
	int exposure_time; //Exposure time in mS
	int lasca_area;
	bool should_i_run;
	int x_max;
	int x_min;
	int graph_update;
	void set_exposure(int);
	bool laser_switch = false;
	QVector<qreal> b;
	vector<Mat> Contrast_Images;
	void Add_Contrast_Image(Mat New_Cont_Image);
	Mat LSIProjectGUI::Help_Average_Images_RT(int Num_Images);
	//

	public slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
	void on_Dark_Button_clicked();
	void on_AmbL_Button_clicked();
	void on_laserButton_clicked();
	//
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void update();
	//
	void on_LASCAarea_valueChanged();
	void on_exposuretime_valueChanged();

	void laser_ON();
	void laser_OF();
	//Real time hanterarn
	private slots:
		void makePlot(QVector<qreal>);
};
