#include "LSIProjectGUI.h"


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
	
	// For BW camera
	//camera.Connect(0);
	//camera.StartCapture();
	//camera.RetrieveBuffer(&rawImage);

	rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
	unsigned int rowBytes = (double)rawImage.GetReceivedDataSize() / (double)rawImage.GetRows(); //Converts the Image to Mat
	Main_Image_CV = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8U, rgbImage.GetData(), rowBytes);

	//webcam >> Main_Image_CV;
	//webcam >> Main_Image_CV;

	Main_Image = QPixmap::fromImage(QImage((unsigned char*)Main_Image_CV.data, Main_Image_CV.cols, Main_Image_CV.rows, QImage::Format_RGB888)); //Converts Mat to QPixmap
	ui.videoLabel->setPixmap(Main_Image);

	if (Is_ROI_Button_Is_Pressed)
	{
		QPainter painter(&Main_Image);
		painter.setPen(pen); //sets pen settings from above to painter
		painter.drawRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
		ui.videoLabel->setPixmap(Main_Image);
	}

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

	QPainter painter(&Main_Image);
	painter.eraseRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
	ui.videoLabel->setPixmap(Main_Image);

	// immediately after erasing, a new image should be loaded

}


void LSIProjectGUI::mousePressEvent(QMouseEvent *event) 
{
	if (Is_ROI_Button_Is_Pressed)
	{
		ROI_Width = 0; //so if a new ROI is drawn, the old one doesn't appear right next to it while drawing the new one
		ROI_Height = 0;

		Start_Click_Coordinates = event->pos(); // in whole GUI, not in videoLabel
		x_Start_Click_Coordinate = Start_Click_Coordinates.x();
		y_Start_Click_Coordinate = Start_Click_Coordinates.y();

		videoLabel_Coordinates = ui.videoLabel->pos();
		x_videoLabel_Coordinate = videoLabel_Coordinates.x();
		y_videoLabel_Coordinate = videoLabel_Coordinates.y();

		x_Start_ROI_Coordinate = x_Start_Click_Coordinate - x_videoLabel_Coordinate;
		y_Start_ROI_Coordinate = y_Start_Click_Coordinate - y_videoLabel_Coordinate;
		Start_ROI_Coordinates = QPoint(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate);

		QString x_videoLabel_string = QString::number(x_videoLabel_Coordinate);
		QString y_videoLabel_string = QString::number(y_videoLabel_Coordinate);
		ui.button_test->setText(x_videoLabel_string + "<x  y>" + y_videoLabel_string); // just to see videoLabel coordinates

		QString x_Start_Click_Coordinates_string = QString::number(x_Start_Click_Coordinate);
		QString y_Start_Click_Coordinates_string = QString::number(y_Start_Click_Coordinate);
		ui.button_test->setText(x_Start_Click_Coordinates_string + "<x  y>" + y_Start_Click_Coordinates_string); // just to see GUI window coordinates

		QString x_Start_ROI_Coordinate_string = QString::number(x_Start_ROI_Coordinate);
		QString y_Start_ROI_Coordinate_string = QString::number(y_Start_ROI_Coordinate);
		ui.button_test->setText(x_Start_ROI_Coordinate_string + "<x  y>" + y_Start_ROI_Coordinate_string); // just to see ROI coordinates

	}
}


void LSIProjectGUI::mouseMoveEvent(QMouseEvent *event) 
{
	if (Is_ROI_Button_Is_Pressed)
	{
		temp_Main_Image = Main_Image;

		QPainter painter(&temp_Main_Image);
		pen;  // creates a default pen
		//pen.setStyle(Qt::DashDotLine); // other line style
		pen.setWidth(4);
		pen.setBrush(Qt::red);
		painter.setPen(pen); //sets pen settings to painter

		painter.drawRect(QRect(Start_ROI_Coordinates, event->pos()-videoLabel_Coordinates));
		ui.videoLabel->setPixmap(temp_Main_Image);

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

		ui.listROI->addItem("ROI");

		vector<int> ROIlocation;
		vector<int> ROIregion;
		//
		ROIregion.push_back(abs(ROI_Width));
		ROIregion.push_back(abs(ROI_Height));
		//
		if (ROI_Height<0 && ROI_Width<0) {
			ROIlocation.push_back(x_End_ROI_Coordinate);
			ROIlocation.push_back(y_End_ROI_Coordinate);
		}
		else if (ROI_Height>0 && ROI_Width>0) {
			ROIlocation.push_back(x_Start_ROI_Coordinate);
			ROIlocation.push_back(y_Start_ROI_Coordinate);
		}
		else if (ROI_Height>0 && ROI_Width<0) {
			ROIlocation.push_back(x_End_ROI_Coordinate);
			ROIlocation.push_back(y_Start_ROI_Coordinate);
		}
		else if (ROI_Height<0 && ROI_Width>0) {
			ROIlocation.push_back(x_Start_ROI_Coordinate);
			ROIlocation.push_back(y_End_ROI_Coordinate);
		}

		ROI ROI(ROIlocation, ROIregion);
		List_Of_ROI.push_back(ROI);
	}
	//Is_ROI_Button_Is_Pressed = false; // only make one ROI at a time
}

void LSIProjectGUI::on_listROI_selectedItems(QListWidgetItem * item) {
	
	item->setBackground(Qt::darkRed);

}
