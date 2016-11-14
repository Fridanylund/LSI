#include "LSIProjectGUI.h"

//#include "ROIclass.h"


LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	camera.Connect(0);
	camera.StartCapture();
	
	//For webcam
	VideoCapture temp(0);
	webcam = temp;

}

void LSIProjectGUI::update()
{
	//camera.Connect(0);
	//camera.StartCapture();
	//camera.RetrieveBuffer(&rawImage);

	//rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
	//unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
	//Main_Image_CV = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);

	webcam >> Main_Image_CV;
	webcam >> Main_Image_CV;
	cout << "test";

	Main_Image = QPixmap::fromImage(QImage((unsigned char*)Main_Image_CV.data, Main_Image_CV.cols, Main_Image_CV.rows, QImage::Format_RGB888)); //Converts Mat to QPixmap
	ui.videoLabel->setPixmap(Main_Image);

}


void LSIProjectGUI::on_startButton_clicked() {
	timer->start(200);
}

void LSIProjectGUI::on_stopButton_clicked() {
	ui.button_test->setText("STOP!");
	timer->stop();
}

void LSIProjectGUI::on_createROIButton_clicked() 
{
	Is_ROI_Button_Is_Pressed = true; // to start mouseEvent functions
}

void LSIProjectGUI::on_removeROIButton_clicked() 
{
	Is_ROI_Button_Is_Pressed = false; // to stop mouseEvent functions

	QPixmap bild; // should not have to load bild again here
	bild.load("3110_handwithlaser_1.png");

	QPainter painter(&bild);
	painter.eraseRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
	ui.videoLabel->setPixmap(bild);

	// immediately after erasing, a new image should be loaded


}


void LSIProjectGUI::mousePressEvent(QMouseEvent *event) 
{
	if (Is_ROI_Button_Is_Pressed)
	{
		Start_Click_Coordinates = event->pos(); // in whole GUI, not in videoLabel
		x_Start_Click_Coordinate = Start_Click_Coordinates.x();
		y_Start_Click_Coordinate = Start_Click_Coordinates.y();

		videoLabel_Coordinates = ui.videoLabel->pos();
		x_videoLabel_Coordinate = videoLabel_Coordinates.x();
		y_videoLabel_Coordinate = videoLabel_Coordinates.y();

		QString x_videoLabel_string = QString::number(x_videoLabel_Coordinate);
		QString y_videoLabel_string = QString::number(y_videoLabel_Coordinate);
		ui.button_test->setText(x_videoLabel_string + "<x  y>" + y_videoLabel_string); // just to see videoLabel coordinates

		x_Start_ROI_Coordinate = x_Start_Click_Coordinate - x_videoLabel_Coordinate;
		y_Start_ROI_Coordinate = y_Start_Click_Coordinate - y_videoLabel_Coordinate;
		Start_ROI_Coordinates = QPoint(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate);
		
	}
}


void LSIProjectGUI::mouseMoveEvent(QMouseEvent *event) 
{
	if (Is_ROI_Button_Is_Pressed)
	{
		QPixmap bild; // should not have to load bild again here
		bild.load("3110_handwithlaser_1.png");

		QPainter painter(&bild);
		pen;  // creates a default pen
		//pen.setStyle(Qt::DashDotLine); // other line style
		pen.setWidth(4);
		pen.setBrush(Qt::red);
		painter.setPen(pen); //sets pen settings to painter

		painter.drawRect(QRect(Start_ROI_Coordinates, event->pos()-videoLabel_Coordinates));
		ui.videoLabel->setPixmap(bild);

		QString x_Start_Click_Coordinates_string = QString::number(x_Start_Click_Coordinate);
		QString y_Start_Click_Coordinates_string = QString::number(y_Start_Click_Coordinate);
		ui.button_test->setText(x_Start_Click_Coordinates_string + "<x  y>" + y_Start_Click_Coordinates_string); // just to see GUI window coordinates

	}
}


void LSIProjectGUI::mouseReleaseEvent(QMouseEvent *event) 
{
	if (Is_ROI_Button_Is_Pressed)
	{
		QPoint End_Click_Coordinates = event->pos();
		int x_End_Click_Coordinate = End_Click_Coordinates.x();
		int y_End_Click_Coordinate = End_Click_Coordinates.y();

		x_End_ROI_Coordinate = x_End_Click_Coordinate - x_videoLabel_Coordinate;
		y_End_ROI_Coordinate = y_End_Click_Coordinate - y_videoLabel_Coordinate;

		ROI_Width = x_End_ROI_Coordinate - x_Start_ROI_Coordinate;
		ROI_Height = y_End_ROI_Coordinate - y_Start_ROI_Coordinate;
		
		QString Width_string = QString::number(ROI_Width);
		QString Height_string = QString::number(ROI_Height);
		ui.button_test->setText(Width_string + "<Width   Hight>" + Height_string); // just to check width and height of ROI

		QPixmap bild; // should not have to load bild again here
		bild.load("3110_handwithlaser_1.png");

		QPainter painter(&bild);
		painter.setPen(pen); //sets pen settings from above to painter
		painter.drawRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
		ui.videoLabel->setPixmap(bild);

		ui.listROI->addItem("ROI");

		//vector<int> ROIlocation;
		//vector<int> ROIregion;
		////
		//ROIregion.push_back(abs(ROI_Width));
		//ROIregion.push_back(abs(ROI_Height));
		////
		//if (ROI_Height<0 && ROI_Width<0) {
		//	ROIlocation.push_back(x_End_ROI_Coordinate);
		//	ROIlocation.push_back(y_End_ROI_Coordinate);
		//}
		//else if (ROI_Height>0 && ROI_Width>0) {
		//	ROIlocation.push_back(x_Start_ROI_Coordinate);
		//	ROIlocation.push_back(y_Start_ROI_Coordinate);
		//}
		//else if (ROI_Height>0 && ROI_Width<0) {
		//	ROIlocation.push_back(x_End_ROI_Coordinate);
		//	ROIlocation.push_back(y_Start_ROI_Coordinate);
		//}
		//else if (ROI_Height<0 && ROI_Width>0) {
		//	ROIlocation.push_back(x_Start_ROI_Coordinate);
		//	ROIlocation.push_back(y_End_ROI_Coordinate);
		//}

		//ROI ROI1(ROIlocation, ROIregion);
		//List_Of_ROI.push_back(ROI1);
	}
	//Is_ROI_Button_Is_Pressed = false;
}

void LSIProjectGUI::on_listROI_itemClicked(QListWidgetItem * item) {
	
	item->setBackground(Qt::darkRed);
}
