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
#include <fstream>
#include <FlyCapture2.h>
#include <QVector>
#include <QTime>


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
	Mat Main_Image_CV_for_ambient_light;
	Image rgbImage;
	Image rawImage;
	Image rgbImage2;
	Image rawImage2;
	Camera camera;
	VideoCapture webcam;
	QSerialPort *port;
	bool static_ambient_ligth; //If the ambient light image should update or not
	int ambient_ligth_refresh_rate; //How often ambient light is updated
	int ambient_ligth_refresh_rate_count;
	
	double Calib_Still = 0;
	double Calib_Moving = 0;
	
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
	string filename;
	VideoWriter Video_Base;
	VideoWriter Video_Contrast;
	
	
	void take_laser_image();
	void take_ambient_light_image();
	void remove_ambient_ligth_and_black_image();
	void uppdate_ambientlight();
	void do_contrast();
	void load_init();
	void save_init();
	
	//

	public slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_createROIButton_clicked();
	void on_removeROIButton_clicked();
	void on_Dark_Button_clicked();
	void on_AmbL_Button_clicked();
	void on_laserButton_clicked();
	// These two calibration buttons are needed in the GUI:
	void on_CalibrateStill_Button_clicked();
	void on_CalibrateMoving_Button_clicked();

	//
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void on_patientName_textEdited(const QString &text);
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
