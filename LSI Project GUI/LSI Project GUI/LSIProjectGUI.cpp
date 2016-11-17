#include "LSIProjectGUI.h"
#include "qcustomplot.h"
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
	lasca_area = 5;
	//For webcam
	VideoCapture temp(0);
	webcam = temp;
	should_i_run = true;

	//LSIProjectGUI::makePlot();
	graph_update=0;
	x_min = -1;
	x_max = 5;
	
	// give the axes some labels:
	ui.customPlot->xAxis->setLabel("Time");
	ui.customPlot->yAxis->setLabel("Mean Contrast");
	ui.customPlot->xAxis->setRange(x_min, x_max);
	ui.customPlot->yAxis->setRange(0, 20);

	////Declare a Property struct.
	//Property prop;
	////Define the property to adjust.
	//prop.type = GAIN;
	////Ensure auto-adjust mode is off.
	//prop.autoManualMode = false;
	////Ensure the property is set up to use absolute value control.
	//prop.absControl = true;
	////Set the absolute value of gain to 10.5 dB.
	//prop.absValue = 10.5;
	////Set the property.
	//camera.SetProperty(&prop);
	//set_exposure(exposure_time);

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
	if (should_i_run) {
		// For BW camera
		camera.Connect(0);
		camera.StartCapture();
		camera.RetrieveBuffer(&rawImage);

		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
		unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
		Main_Image_CV = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);
		//CV_8UC3
		//webcam >> Main_Image_CV;
		//webcam >> Main_Image_CV;

		Main_Image_CV = CalculateContrast2(Main_Image_CV, lasca_area); //QImage::Format_RGB888 QImage::Format_Grayscale8
		cv::resize(Main_Image_CV, Main_Image_CV, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);

		Main_Image_CV = Main_Image_CV;

		//Main_Image_CV=  one_divided_by_kontrast(Main_Image_CV);

		//Main_Image_CV = one_divided_by_kontrast_squared(Main_Image_CV);

		//Main_Image_CV = one_minus_kontrast(Main_Image_CV);

		//Main_Image_CV = kontrast_squared(Main_Image_CV);

		//imshow("ewa", Main_Image_CV);
		//cvtColor(Main_Image_CV, Main_Image_CV, cv::COLOR_GRAY2BGR);
		Main_Image = QPixmap::fromImage(QImage((unsigned char*)Main_Image_CV.data, Main_Image_CV.cols, Main_Image_CV.rows, QImage::Format_RGB888)); //Converts Mat to QPixmap
		ui.videoLabel->setPixmap(Main_Image);

		// vector for ROI colours
		QVector<QColor> ROI_Colors{QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };

		//QString color_index_string = QString::number(color_index);
		//ui.button_test->setText(color_index_string); // just to see color_index

		for (int f = 0; f < List_Of_ROI.size(); f++)
		{
			QPainter painter(&Main_Image);
			pen.setBrush(ROI_Colors.at(f)); // sets new color for each ROI
			painter.setPen(pen); //sets pen settings from above to painter
			int x = List_Of_ROI.at(f).Get_ROI_Location().at(0);
			int y = List_Of_ROI.at(f).Get_ROI_Location().at(1);
			int ROI_w = List_Of_ROI.at(f).Get_ROI_Region().at(0);
			int ROI_h = List_Of_ROI.at(f).Get_ROI_Region().at(1);
			painter.drawRect(x, y, ROI_w, ROI_h);
			ui.videoLabel->setPixmap(Main_Image);
		}
	}
	//Fel att ta in frame objekt nu...

	//vector<double> averageROI = Calc_ROI_Average(Main_Image, List_Of_ROI);
	if (Is_ROI_Button_Is_Pressed)
	{
		QPainter painter(&Main_Image);
		painter.setPen(pen); //sets pen settings from above to painter
		painter.drawRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
		ui.videoLabel->setPixmap(Main_Image);
	}
	graph_update++;
	if (graph_update == 5) {
		b.append(b.count());
		makePlot(b);
		graph_update = 0;
	}
	

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
	if (!List_Of_ROI.empty()) // prevents program from crashing if vector is empty
	{
		int selectedROI = ui.listROI->currentRow();
		ui.button_test->setText(QString::number(selectedROI));

		List_Of_ROI.erase(List_Of_ROI.begin() + selectedROI); // maybe instead of deleting ROI, set Width and Height to 0 but obs: list.ROI and List_Of_ROI are not the same size any more
		//List_Of_ROI(List_Of_ROI.begin() + selectedROI).Set_ROI_Region(vector<int>(0, 0));
		delete ui.listROI->takeItem(selectedROI); 

		
		////Declare a Property struct.
		//Property prop;
		////Define the property to adjust.
		//prop.type = SHUTTER;
		////Ensure the property is on.
		//prop.onOff = true;
		////Ensure auto-adjust mode is off.
		//prop.autoManualMode = false;
		////Ensure the property is set up to use absolute value control.
		//prop.absControl = true;
		////Set the absolute value of shutter to X ms.
		//prop.absValue = 20;
		////Set the property.
		//camera.SetProperty(&prop);

		// program crashes if we remove ROI when nothing is selected
		//ui.listROI->item(0)->setSelected(true); // sets first row to selected row by default (doesn't work)
	}
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

		// same color vector as in update function
		QVector<QColor> ROI_Colors{QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };
		
		// color_index from 1 to ROI_Colors.size -> loops through ROI_Colours
		//color_index = i - ROI_Colors.size() * floor((i - 1) / ROI_Colors.size()); // floor() = round down

		// needs this manually for the first rectangle, otherwise it cannot be seen while it's drawn
		if (List_Of_ROI.size() == 0)
		{
			QPainter painter(&temp_Main_Image);
			pen;
			pen.setWidth(4);
			pen.setBrush(Qt::red);
			painter.setPen(pen);
			painter.drawRect(QRect(Start_ROI_Coordinates, event->pos() - videoLabel_Coordinates));
			ui.videoLabel->setPixmap(temp_Main_Image);
		}

		// then loop for all other rectangles
		for (int f = 1; f < List_Of_ROI.size() + 1; f++)
		{
			QPainter painter(&temp_Main_Image);
			pen;  // creates a default pen
			pen.setWidth(4);
			pen.setBrush(ROI_Colors.at(f)); // sets new color for each ROI
			painter.setPen(pen); //sets pen settings to painter

			painter.drawRect(QRect(Start_ROI_Coordinates, event->pos() - videoLabel_Coordinates));
			ui.videoLabel->setPixmap(temp_Main_Image);
		}
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

		// Lägger in Nya ROI i listan i GUIt
		i++;
		ui.listROI->addItem("ROI" + QString::number(i));

		// skapar vektorer för att skapa nytt ROI object
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

// Tittar om bilden är delbar med vald LASCA area
void LSIProjectGUI::on_LASCAarea_valueChanged() {
	//Tömmer error labeln
	should_i_run = false;
	ui.error_LASCA_label->setText("");
	int LASCA = ui.LASCAarea->value();
	if (LASCA > 0) {
		// Tar ut storleken på bilden
		QSize im_size = Main_Image.size();
		int h = im_size.height();
		int w = im_size.width();
		// Sätter ett error om någon av höjd/bredd inte är delbar med LASCA arean
		if (h % LASCA != 0 && w % LASCA != 0) {
			ui.error_LASCA_label->setText("Change to a value that the image is divadible by!");
		}
		else { lasca_area = LASCA; should_i_run = true; }
	}
	else
	{
		ui.error_LASCA_label->setText("Choose a non-zero value!");
	}
}


void LSIProjectGUI::on_exposuretime_valueChanged()
{
	int t = ui.exposuretime->value();
	//ui.error_LASCA_label->setText(Width_string);
	set_exposure(t);
}

void LSIProjectGUI::makePlot(QVector<qreal> a)
{
	// generate some data:
	QVector<qreal> x(a.count()); 
	for (int i = 0; i<a.count(); ++i)
	{
		x[i] = i; 
	}
	ui.customPlot->addGraph();
	//ui.customPlot->graph(0)->addData(0, 10);
	ui.customPlot->graph(0)->setData(x, a);
	ui.customPlot->replot();
	
	/*if (a.count() <= 5 ) {
		x_min++;
		x_max++;
	}*/
		
	ui.customPlot->xAxis->setRange(x_min, x_max);

}