#include "LSIProjectGUI.h"
#include "Test-function.h"
#include <opencv/cv.h>
#include <QTimer>

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	//Frame temp("test", 640, 480, "Webcam", 3);
	//temp.Take_Picture("BaseImage");
	//Mat img_CV = temp.Get_Base_Image();
	//imwrite("images//test11102.png", img_CV);
	//frame_object = temp;
	//frame_object.Take_Picture("BaseImage");
	//Mat img_CV2 = frame_object.Get_Base_Image();
	//imwrite("images//test111022.png", img_CV2);
	Frame temp("test", 640, 480, "Fly", 3);
	frame_object = temp;
	BW_Cam.Connect(0);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}

void LSIProjectGUI::timertest() {


	timer->start(100);
}

void LSIProjectGUI::update() {
	BW_Cam.StartCapture();
	BW_Cam.RetrieveBuffer(&rawImage);
	rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
	unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
	cv::Mat image = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);

	cv::Mat smallimage; //To resize the image, until we figure out how to take smaller pictures 
	cv::resize(image, smallimage, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);

	QPixmap img_QT = QPixmap::fromImage(QImage((unsigned char*)image.data, image.cols, image.rows, QImage::Format_RGB888));
	ui.videoLabel->setPixmap(img_QT);
}

void LSIProjectGUI::on_startButton_clicked() {
	// Should, when it's ready, contain call to function Real_Time_Main in Free-Functions.
	//ui.button_test->setText("START!");
	////stilltest();
	//cv::Mat cv_bild;
	//cv_bild = cv::imread("3110_handwithlaser_1.png");
	// 
	////QPixmap bild;
	//QPixmap img = QPixmap::fromImage(QImage((unsigned char*)cv_bild.data, cv_bild.cols, cv_bild.rows, QImage::Format_RGB888));
	////bild.load("3110_handwithlaser_1.png");
	//ui.videoLabel->setPixmap(img);
	timertest();
	

}

void LSIProjectGUI::on_stopButton_clicked() {
	ui.button_test->setText("STOP!");
	timer->stop();
}

void LSIProjectGUI::on_createROIButton_clicked() {
	ui.button_test->setText("ROI!");
}

void LSIProjectGUI::on_removeROIButton_clicked() {
	BW_Cam.Disconnect();
	timer->stop();
	ui.button_test->setText("DELETED!");
}


void LSIProjectGUI::test_loop()
{
	Frame frame_object("test", 640, 480, "Webcam", 3);
	cv::Mat img_CV;
	QPixmap img_QT;
	//while (run)
	//{
		frame_object.Take_Picture("BaseImage");
		img_CV = frame_object.Get_Base_Image();
		img_QT = QPixmap::fromImage(QImage((unsigned char*)img_CV.data, img_CV.cols, img_CV.rows, QImage::Format_RGB888));
		ui.videoLabel->setPixmap(img_QT);
//
}