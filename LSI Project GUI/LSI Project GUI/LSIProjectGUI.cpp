#include "LSIProjectGUI.h"


LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	camera.Connect(0);
	camera.StartCapture();
	
	refresh_rate = 200;
	exposure_time = 20;
	//For webcam
	VideoCapture temp(0);
	webcam = temp;

	//Declare a Property struct.
	Property prop;
	//Define the property to adjust.
	prop.type = GAIN;
	//Ensure auto-adjust mode is off.
	prop.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	//prop.absControl = true;
	//Set the absolute value of gain to 10.5 dB.
	//prop.absValue = 10.5;
	//Set the property.
	camera.SetProperty(&prop);


}

void LSIProjectGUI::set_exposure(int time)
{
	//Declare a Property struct.
	Property prop;
	//Define the property to adjust.
	prop.type = SHUTTER;
	//Ensure the property is on.
	prop.onOff = true;
	//Ensure auto-adjust mode is off.
	prop.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	prop.absControl = true;
	//Set the absolute value of shutter to X ms.
	prop.absValue = time;
	//Set the property.
	camera.SetProperty(&prop);
}


void LSIProjectGUI::update()
{
	
	// For BW camera
	camera.Connect(0);
	camera.StartCapture();
	camera.RetrieveBuffer(&rawImage);

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

	for (int f = 0; f < List_Of_ROI.size(); f++) {
		QPainter painter(&Main_Image);
		pen.setBrush(Qt::darkBlue);
		painter.setPen(pen); //sets pen settings from above to painter
		int x = List_Of_ROI.at(f).Get_ROI_Location().at(0);
		int y = List_Of_ROI.at(f).Get_ROI_Location().at(1);
		int ROI_w = List_Of_ROI.at(f).Get_ROI_Region().at(0);
		int ROI_h = List_Of_ROI.at(f).Get_ROI_Region().at(1);
		painter.drawRect(x, y, ROI_w, ROI_h);
		ui.videoLabel->setPixmap(Main_Image);
	}
	//Fel att ta in frame objekt nu...

	//vector<double> averageROI = Calc_ROI_Average(Main_Image, List_Of_ROI);
}


void LSIProjectGUI::on_startButton_clicked() {
	timer->start(refresh_rate);
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
	int selectedROI = ui.listROI->currentRow();
	ui.button_test->setText(QString::number(selectedROI));

	List_Of_ROI.erase(List_Of_ROI.begin() + selectedROI);
	delete ui.listROI->takeItem(selectedROI);
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

		// L�gger in Nya ROI i listan i GUIt
		i++;
		ui.listROI->addItem("ROI" + QString::number(i));

		// skapar vektorer f�r att skapa nytt ROI object
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
	Is_ROI_Button_Is_Pressed = false; // only make one ROI at a time
}

// Tittar om bilden �r delbar med vald LASCA area
void LSIProjectGUI::on_LASCAarea_valueChanged() {
	//T�mmer error labeln
	ui.error_LASCA_label->setText("");
	int LASCA = ui.LASCAarea->value();
	if(LASCA > 0 ){
		// Tar ut storleken p� bilden
		QSize im_size = Main_Image.size();
		int h = im_size.height();
		int w = im_size.width();
		// S�tter ett error om n�gon av h�jd/bredd inte �r delbar med LASCA arean
		if (h % LASCA != 0 && w % LASCA != 0) {
			ui.error_LASCA_label->setText("Change to a value that the image is divadible by!");
		}
	}
	else
	{
		ui.error_LASCA_label->setText("Choose a non-zero value!");
	}
}
