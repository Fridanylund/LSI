#include "LSIProjectGUI.h"

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);

	//Timer which updates the gui and takes images
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	//Connects the serial port which is used to control the laser
	port = new QSerialPort(this);
	connect_laser();

	
	camera.Connect(0);
	camera.StartCapture();
	camera.SetVideoModeAndFrameRate(VIDEOMODE_1280x960Y8, FRAMERATE_60); //Changes the resolution of the camera

	refresh_rate = 200;
	exposure_time = 5;
	set_exposure(exposure_time);
	lasca_area = 5;
	//For webcam
	/*VideoCapture temp(0);
	webcam = temp;*/
	should_i_run = true;
	load_init();
	show_perfusion = false;

	//LSIProjectGUI::makePlot();
	graph_update=0;
	x_min = -1;
	x_max = 5;
	ambient_ligth_refresh_rate = 100;
	ambient_ligth_refresh_rate_count = 0;
	//port = new QSerialPort(this);

	
	// give the axes some labels:
	ui.customPlot->xAxis->setLabel("Time");
	ui.customPlot->yAxis->setLabel("Perfusion");
	ui.customPlot->xAxis->setRange(x_min, x_max);
	ui.customPlot->yAxis->setRange(0, 255);

	connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
	connect(ui.customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));

	//Declare a Property struct.
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
	load_init();
	timer->start(refresh_rate);
}

void LSIProjectGUI::connect_laser()
{
	for (unsigned int k = 0; k <= 15; k++)
	{
		QString port_name;
		port_name = "COM" + QString::number(k);
		port->setPortName(port_name);
		bool temp = port->open(QIODevice::WriteOnly);
		if (temp)
		{
			port->setRequestToSend(false);
			ui.button_test->setText(port_name);
			break;
		}
		else if (k == 15)
		{
			ui.button_test->setText("Failed to connect the laser controller to a COM port!");
			break;
		}
			
	}
	


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

void LSIProjectGUI::take_laser_image()
{
	camera.Connect(0);
	camera.StartCapture();
	camera.RetrieveBuffer(&rawImage);
	rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
	unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
	Main_Image_CV = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);
	cv::resize(Main_Image_CV, temp, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
	//imshow("sadsa", Main_Image_CV);
	if (!Black_im.empty()) // Removes the black image when taken.
	{
		//absdiff(Main_Image_CV, Black_im, Main_Image_CV);
		Main_Image_CV = Main_Image_CV - Black_im;
	}
	if (!Raw_im.empty()) // Removes the ambient light when image taken.
	{
		//absdiff(Main_Image_CV, Raw_im, Main_Image_CV);
		Main_Image_CV = Main_Image_CV - Raw_im;
	}
	//cv::resize(Main_Image_CV, temp, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
	//imshow("Råbild", Main_Image_CV);
	/*webcam >> Main_Image_CV;
	webcam >> Main_Image_CV;*/
	//remove_ambient_ligth_and_black_image();
}

void LSIProjectGUI::take_ambient_light_image()
{
	port->setRequestToSend(false);
	Sleep(100);
	camera.Connect(0);
	camera.StartCapture();
	camera.RetrieveBuffer(&rawImage2);
	port->setRequestToSend(true);
	Sleep(650);
	rawImage2.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage2);
	unsigned int rowBytes = (double)rgbImage2.GetReceivedDataSize() / (double)rgbImage2.GetRows(); //Converts the Image to Mat
	Main_Image_CV_for_ambient_light = cv::Mat(rgbImage2.GetRows(), rgbImage2.GetCols(), CV_8UC3, rgbImage2.GetData(), rowBytes);
	/*webcam >> Main_Image_CV;
	webcam >> Main_Image_CV;*/
	//remove_ambient_ligth_and_black_image();
	if (!Black_im.empty()) // Removes the black image when taken.
	{
		Raw_im = Main_Image_CV_for_ambient_light - Black_im;
		/*imshow("Ambient light", Raw_im);*/
	}
	else 
	{
		Raw_im = Main_Image_CV_for_ambient_light;

	}

}



void LSIProjectGUI::do_contrast()
{
	//cv::resize(Main_Image_CV, Main_Image_CV, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
	//Main_Image_CV = CalculateContrast2(Main_Image_CV, lasca_area, Calib_Still, Calib_Moving); //QImage::Format_RGB888 QImage::Format_Grayscale8
	
	int scaling_factor = ui.scaling_spinBox->value();

	if (ui.Contrast_checkBox->isChecked()) {
		Main_Image_CV = CalculateContrast_pix_by_pix(Main_Image_CV, lasca_area, Calib_Still, Calib_Moving);
	}
	else
	{
		Main_Image_CV = CalculateContrast2(Main_Image_CV, lasca_area, Calib_Still, Calib_Moving);
	}


	cv::resize(Main_Image_CV, Main_Image_CV, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
	Add_Contrast_Image(Main_Image_CV);
	Mat Main_Image_CV_filter = TemporalFiltering(Contrast_Images);
	

	Mat Main_Image_CV_divided_log;
	Mat Main_Image_CV_divided_reg;
	
	Main_Image_CV_divided_log = one_divided_by_kontrast_squared(Main_Image_CV_filter,true); //Tar 1/k^2 och log på det
	Main_Image_CV_divided_reg = one_divided_by_kontrast_squared(Main_Image_CV_filter, false);


	Main_Image_CV_divided_log = 2 * Main_Image_CV_divided_log;
	Main_Image_CV_divided_log.convertTo(Main_Image_CV_divided_log, CV_8UC3);

	Main_Image_CV_divided_reg = Main_Image_CV_divided_reg/scaling_factor; ///////////////2////////////// Gainfaktor! ////////////////////////////

	Main_Image_CV_divided_reg.convertTo(Main_Image_CV_divided_reg, CV_8UC3);


	applyColorMap(Main_Image_CV_divided_reg, Main_Image_CV_divided_reg, COLORMAP_JET);
	//applyColorMap(Main_Image_CV_divided_log, Main_Image_CV_divided_log, COLORMAP_JET);
	//cv::cvtColor(Main_Image_CV_divided_log, Main_Image_CV_divided_log, cv::COLOR_GRAY2BGR);
	//cv::cvtColor(divided_converted, color, cv::COLOR_GRAY2BGR);
	Video_Base.write(Main_Image_CV_divided_reg);
	cv::cvtColor(Main_Image_CV_divided_reg, Main_Image_CV_divided_reg, CV_BGR2RGB);
	//imshow("1/Kontrast^2", Main_Image_CV_divided_reg);
	//imshow("1/kontrast^2 log", Main_Image_CV_divided_log);

	Main_Image_CV = Main_Image_CV_divided_reg;
	Main_Image = QPixmap::fromImage(QImage((unsigned char*)Main_Image_CV_divided_reg.data, Main_Image_CV_divided_reg.cols, Main_Image_CV_divided_reg.rows, QImage::Format_RGB888)); //Converts Mat to QPixmap
	ui.videoLabel->setPixmap(Main_Image);
	
}

void LSIProjectGUI::load_init()
{
	ifstream read;
	read.open("settings//settings.txt");

	if (read.is_open())
	{
		read >> refresh_rate >> Calib_Still >> Calib_Moving; //Reads the variables in the order they come in the settings.txt
	}
	else
	{
		//Set standard values instead and write and error.
		refresh_rate = 5;
	}
	refresh_rate = 100;
	Black_im = imread("images//morkerBild.png");

}

void LSIProjectGUI::save_init()
{
	ofstream write;
	write.open("settings//settings.txt", std::ofstream::trunc);
	write << refresh_rate<< endl << Calib_Still << endl << Calib_Moving << endl; //Add any other variables to be saved.
}


void LSIProjectGUI::horzScrollBarChanged(int value)
{
	if (qAbs(ui.customPlot->xAxis->range().center() - value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		ui.customPlot->xAxis->setRange(value / 100.0, ui.customPlot->xAxis->range().size()); //, Qt::AlignCenter
		ui.customPlot->replot();
	}
}

void LSIProjectGUI::xAxisChanged(QCPRange range)
{
	ui.horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
	ui.horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}


void LSIProjectGUI::update()
{
	time(&time1);
	if (should_i_run) {
		if (show_perfusion)
		{
			if (ambient_ligth_refresh_rate_count == 0)
			{
				take_ambient_light_image();
				ambient_ligth_refresh_rate_count = ambient_ligth_refresh_rate;
			}
			else {
				take_laser_image();
				do_contrast();
				ambient_ligth_refresh_rate_count--;
			}
		}
		else
		{
			camera.Connect(0);
			camera.StartCapture();
			camera.RetrieveBuffer(&rawImage);
			rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
			unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
			Main_Image_CV = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);
			cv::resize(Main_Image_CV, Main_Image_CV, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
			Main_Image = QPixmap::fromImage(QImage((unsigned char*)Main_Image_CV.data, Main_Image_CV.cols, Main_Image_CV.rows, QImage::Format_RGB888));


		}


		// vector for ROI colours
		QVector<QColor> ROI_Colors{QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };
		
		for (int f = 0; f < List_Of_ROI.size(); f++)
		{
			QPainter painter(&Main_Image);
			color_index = List_Of_ROI.at(f).ROI_Colour - 1;
			pen.setBrush(ROI_Colors.at(color_index)); // sets new color for each ROI
			painter.setPen(pen); //sets pen settings from above to painter
			int x = List_Of_ROI.at(f).Get_ROI_Location().at(0);
			int y = List_Of_ROI.at(f).Get_ROI_Location().at(1);
			int ROI_w = List_Of_ROI.at(f).Get_ROI_Region().at(0);
			int ROI_h = List_Of_ROI.at(f).Get_ROI_Region().at(1);
			painter.drawRect(x, y, ROI_w, ROI_h);
			ui.videoLabel->setPixmap(Main_Image);
		}
	}


	if (Is_ROI_Button_Is_Pressed)
	{
		if (List_Of_ROI.empty())
		{
			ROI_Width = 0;
			ROI_Height = 0;
		}
		QPainter painter(&Main_Image);
		painter.setPen(pen); //sets pen settings from above to painter
		painter.drawRect(x_Start_ROI_Coordinate, y_Start_ROI_Coordinate, ROI_Width, ROI_Height);
		ui.videoLabel->setPixmap(Main_Image);
	}


	// plots graphs
	if (!List_Of_ROI.empty()) // prevents program from crashing if vector is empty
	{
		graph_update++;
		if (graph_update == 5) // after 5*200ms = 1s graphs update
		{
		
		// calculates average for all ROIs and saves them in a vector
		// gets overwritten until graph_update == 5
		QVector<double> ROI_Averages = Calc_ROI_Average(Main_Image_CV, List_Of_ROI); // Main_Image_CV not right perfusion image yet
		QVector<qreal> ROI_Averages_qreal;

		for (int i = 0; i < ROI_Averages.size(); i++)
		{
			// saves ROI Averages before they get overwritten
			QVector<qreal> firstvector;
			firstvector.append(ROI_Averages.at(0));
			Multiple_ROI_Averages.append(firstvector);
			ROI_Averages_qreal.append(ROI_Averages.at(i)); // makes QVector out of vector
			Multiple_ROI_Averages[i].append(ROI_Averages_qreal.at(i));
		}



			//for (int k = 0; k < ROI_Averages.size(); k++) // loops through ROI vector
			for (int k = 0; k < List_Of_ROI.size(); k++)
			{
				QVector<qreal> x(Multiple_ROI_Averages[k].count());
				for (int i = 0; i < Multiple_ROI_Averages[k].count(); ++i)
				{
					x[i] = i;
				}

				QVector<QColor> ROI_Colors{ QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };
				int color = List_Of_ROI.at(k).ROI_Colour - 1;

				ui.customPlot->addGraph();
				ui.customPlot->graph(k)->setData(x, Multiple_ROI_Averages[k]);
				ui.customPlot->graph(k)->setPen(QPen(ROI_Colors.at(color)));


				//horzScrollBarChanged(value);
				range = QCPRange::QCPRange(x_min, x_max);
				xAxisChanged(range);

				if (k == 0 & Multiple_ROI_Averages[k].count() >= 6)
				{
					x_min++;
					x_max++;

					//// Horizontal scroll bar
					//connect(ui.horizontalScrollBar, SIGNAL(timeout()), SLOT(update()));
				}
			}
				ui.customPlot->replot();
				ui.customPlot->xAxis->setRange(x_min, x_max);
				ui.horizontalScrollBar->setRange(-100, x_max * 100);
				graph_update = 0;
		}
	}
	if (List_Of_ROI.empty())
	{
		Multiple_ROI_Averages.clear();
	}
	if (Multiple_ROI_Averages.empty())
	{
		ui.customPlot->clearGraphs();
		ui.customPlot->replot();
	}

	time(&time2);
	diff = difftime(time1, time2);
	if (diff < refresh_rate)
	{
		timer->start(refresh_rate - diff);
	}

}


void LSIProjectGUI::on_startButton_clicked() {
	//timer->start(refresh_rate);
	show_perfusion = !show_perfusion;
	// Läsa av vad patienten heter för att spara videon som en fil med patient + datum som namn
	//string time = QTime::currentTime().toString().toStdString();
	String filename = ui.patientName->text().toStdString();

	Video_Base.open("images\\" + filename + "_base.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(640,480), true);

}

void LSIProjectGUI::on_stopButton_clicked() {
	ui.button_test->setText("STOP!");
	timer->stop();
	port->setRequestToSend(false);
	save_init();
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

		List_Of_ROI.erase(List_Of_ROI.begin() + selectedROI); 
		delete ui.listROI->takeItem(selectedROI);

		// removes graph
		Multiple_ROI_Averages.erase(Multiple_ROI_Averages.begin() + selectedROI);

		ui.customPlot->removeGraph(selectedROI);
		ui.customPlot->replot();
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

		if (x_Start_Click_Coordinate >= x_videoLabel_Coordinate & y_Start_Click_Coordinate >= y_videoLabel_Coordinate & x_Start_Click_Coordinate <= ui.videoLabel->width() & y_Start_Click_Coordinate <= ui.videoLabel->height())

		{
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
		else
		{
			Is_ROI_Button_Is_Pressed = false;
		}
	}
}


void LSIProjectGUI::mouseMoveEvent(QMouseEvent *event)
{
	if (Is_ROI_Button_Is_Pressed)
	{
		temp_Main_Image = Main_Image;

		// same color vector as in update function
		QVector<QColor> ROI_Colors{QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };

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
			color_index = List_Of_ROI.at(f-1).ROI_Colour;
			pen.setBrush(ROI_Colors.at(color_index)); // sets new color for each ROI
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

		if (x_End_Click_Coordinate >= x_videoLabel_Coordinate & y_End_Click_Coordinate >= y_videoLabel_Coordinate & x_End_Click_Coordinate <= ui.videoLabel->width() & y_End_Click_Coordinate <= ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = x_End_Click_Coordinate - x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = y_End_Click_Coordinate - y_videoLabel_Coordinate;
		}

		else if (x_End_Click_Coordinate < x_videoLabel_Coordinate & y_End_Click_Coordinate >= y_videoLabel_Coordinate & y_End_Click_Coordinate <= ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = y_End_Click_Coordinate - y_videoLabel_Coordinate;
		}

		else if (x_End_Click_Coordinate > ui.videoLabel->width() & y_End_Click_Coordinate >= y_videoLabel_Coordinate & y_End_Click_Coordinate <= ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = ui.videoLabel->width();
			y_End_ROI_Coordinate = y_End_Click_Coordinate - y_videoLabel_Coordinate;
		}

		else if (x_End_Click_Coordinate >= x_videoLabel_Coordinate & x_End_Click_Coordinate <= ui.videoLabel->width() & y_End_Click_Coordinate < y_videoLabel_Coordinate)
		{
			x_End_ROI_Coordinate = x_End_Click_Coordinate - x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = y_videoLabel_Coordinate;
		}

		else if (x_End_Click_Coordinate >= x_videoLabel_Coordinate & x_End_Click_Coordinate <= ui.videoLabel->width() & y_End_Click_Coordinate > ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = x_End_Click_Coordinate - x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = ui.videoLabel->height();
		}


		else if (x_End_Click_Coordinate < x_videoLabel_Coordinate & y_End_Click_Coordinate > ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = ui.videoLabel->height();
		}

		else if (x_End_Click_Coordinate < x_videoLabel_Coordinate & y_End_Click_Coordinate < y_videoLabel_Coordinate)
		{
			x_End_ROI_Coordinate = x_videoLabel_Coordinate;
			y_End_ROI_Coordinate = y_videoLabel_Coordinate;
		}



		else if (x_End_Click_Coordinate > ui.videoLabel->width() & y_End_Click_Coordinate < y_videoLabel_Coordinate)
		{
			x_End_ROI_Coordinate = ui.videoLabel->width();
			y_End_ROI_Coordinate = y_videoLabel_Coordinate;
		}

		else //if (x_End_Click_Coordinate > ui.videoLabel->width() & y_End_Click_Coordinate > ui.videoLabel->height())
		{
			x_End_ROI_Coordinate = ui.videoLabel->width();
			y_End_ROI_Coordinate = ui.videoLabel->height();
		}


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
		

		// same color vector as in update function
		QVector<QColor> ROI_Colors{ QColor("red"), QColor("darkBlue"), QColor("Yellow"), QColor("cyan"), QColor("darkMagenta"), QColor("green"), QColor("darkRed"), QColor("blue"), QColor("darkYellow"), QColor("darkCyan"), QColor("magenta"), QColor("darkGreen") };
		
		// should give 1 to ROI_Colors.size() so we can loop through ROI_Colors vector but doesn't really work; crashes after last color
		//ROIcolor = i - ROI_Colors.size() * floor((i - 1) / ROI_Colors.size()); // floor = round down
		//

		// loops through color 1-11, even though there are 12 colors, but whatever
		ROIcolor++;
		if (ROIcolor == ROI_Colors.size())
		{
			ROIcolor = 1;
		}

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

		ROI ROI(ROIlocation, ROIregion, ROIcolor);
		List_Of_ROI.push_back(ROI);
		// selects first row by default (program crashes if we remove ROI when nothing is selected)
		ui.listROI->setCurrentRow(0);
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

void LSIProjectGUI::makePlot(QVector<qreal> a) // we don't use this function any more at the moment
{
	// generate some data:
	QVector<qreal> x(a.count()); 
	for (int i = 0; i<a.count(); ++i)
	{
		x[i] = i; 
	}
	ui.customPlot->addGraph();
	ui.customPlot->graph(0)->setData(x, a);
	ui.customPlot->replot();
	ui.customPlot->xAxis->setRange(x_min, x_max);

	if (a.count() >= 6 ) {
		x_min++;
		x_max++;
	}
		
	//ui.customPlot->xAxis->setRange(x_min, x_max);

}

void LSIProjectGUI::Add_Contrast_Image(Mat New_Cont_Image)
{
	Contrast_Images.push_back(New_Cont_Image);

	if (Contrast_Images.size() > 5) // Number of images to do temporal filtering over.
	{
		Contrast_Images.erase(Contrast_Images.begin());
	}
}

// Function used to generate the image to remove ambient light and unevenness in the camera.
Mat LSIProjectGUI::Help_Average_Images_RT(int Num_Images)
{
	//should_i_run = false;
	timer->stop();
	camera.Connect();
	Mat Ave_Image;
	Image rawImage_av;
	Image rgbImage_av;

	for (int i = 0; i < Num_Images; i++) {
		camera.RetrieveBuffer(&rawImage_av);

		rawImage_av.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage_av);
		unsigned int rowBytes = (double)rgbImage_av.GetReceivedDataSize() / (double)rgbImage_av.GetRows(); //Converts the Image to Mat
		Ave_Image = cv::Mat(rgbImage_av.GetRows(), rgbImage_av.GetCols(), CV_8UC3, rgbImage_av.GetData(), rowBytes) / Num_Images + Ave_Image;
	}
	//should_i_run = true;
	return(Ave_Image);
}

void LSIProjectGUI::on_AmbL_Button_clicked()
{
	//static_ambient_ligth = true; 
	//Raw_im = Help_Average_Images_RT(100);
	ambient_ligth_refresh_rate_count = ambient_ligth_refresh_rate;
	//imwrite("images//ambientBild.png", Raw_im);
	//ui.button_test->setText("Amb klart!");
}

void LSIProjectGUI::on_Dark_Button_clicked()
{
	Black_im = Help_Average_Images_RT(100);
	imwrite("images//morkerBild.png", Black_im);
	ui.button_test->setText("Klar mork!");
}

void LSIProjectGUI::on_laserButton_clicked()
{
	if (!should_i_run) //If since it may screw something up if allowed to swithc while running
	{
		port->setRequestToSend(laser_switch);
		laser_switch = !laser_switch;
	}
}

void LSIProjectGUI::laser_OF()
{
	laser_switch = true;
	port->setRequestToSend(laser_switch);
}
void LSIProjectGUI::laser_ON()
{
	laser_switch = false;
	port->setRequestToSend(laser_switch);
}


void LSIProjectGUI::on_Save_Im_clicked()
{
	ui.button_test->setText("save!");
	//string time = QTime::currentTime().toString().toStdString();
	String filename = ui.patientName->text().toStdString();
	string fname;

	fname = "images//" + filename + ".png"; 
	imwrite(fname, Main_Image_CV); //Main_Image_CV_divided
}


void LSIProjectGUI::on_CalibrateStill_Button_clicked()
{
	
	Mat Calib_Image_Still = Help_Average_Images_RT(100);
	if (!Black_im.empty()) // Removes the black image when taken.
	{
		absdiff(Calib_Image_Still, Black_im, Calib_Image_Still);
	}
	if (!Raw_im.empty()) // Removes the ambient light when image taken.
	{
		absdiff(Calib_Image_Still, Raw_im, Calib_Image_Still);
	}
	Calib_Image_Still = CalculateContrast2(Calib_Image_Still, lasca_area, 0, 0);
	Calib_Still = mean(Calib_Image_Still).val[0];
	save_init();
	ui.button_test->setText("still done!");
}

void LSIProjectGUI::on_CalibrateMoving_Button_clicked()
{

	Mat Calib_Image_Moving = Help_Average_Images_RT(100);
	if (!Black_im.empty()) // Removes the black image when taken.
	{
		absdiff(Calib_Image_Moving, Black_im, Calib_Image_Moving);
	}
	if (!Raw_im.empty()) // Removes the ambient light when image taken.
	{
		absdiff(Calib_Image_Moving, Raw_im, Calib_Image_Moving);
	}

	Calib_Image_Moving = CalculateContrast2(Calib_Image_Moving, lasca_area, 0, 0);
	Calib_Moving = mean(Calib_Image_Moving).val[0];
	save_init();
	ui.button_test->setText("moving done!");
}

void LSIProjectGUI::on_reset_Button_clicked()
{
	// byt till de värden vi vill ha!!
	Calib_Moving = 0.3;
	Calib_Still = 0.517;
	
	Mat Black_im_reset = imread("images//black.png");
	imwrite("images//morkerBild.png", Black_im);

	save_init();
}

void LSIProjectGUI::on_Amb_spinBox_valueChanged()
{
	int time = ui.Amb_spinBox->value();
	ambient_ligth_refresh_rate = time;
}