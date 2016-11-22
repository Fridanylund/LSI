/*
The Frame class and its functions are written here. 
*/
#pragma once
#include <iostream>
#include "FrameClass.h"
#include <opencv/cv.h>


using namespace std;
using namespace cv;


// Set functions
void Frame::Set_Exposure_Times(vector<int> New_Exposure_Times) {
	Exposure_Times = New_Exposure_Times;
}

void Frame::Set_Base_Image(Mat New_Base_Image) {
	Base_Image = New_Base_Image;
}

void Frame::Set_Laser_Image(Mat New_Laser_Image) {
	Laser_Image = New_Laser_Image;
}

void Frame::Set_Contrast_Image(Mat New_Contrast_Image) {
	Contrast_Image = New_Contrast_Image;
}

void Frame::Set_Time_Averaged_Image(Mat New_Time_Averaged_Image) {
	Time_Averaged_Image = New_Time_Averaged_Image;
}

void Frame::Set_Perfusion_Image(Mat New_Perfusion_Image) {
	Perfusion_Image = New_Perfusion_Image;
}

void Frame::Set_Lasca_Area(int New_Lasca_Area) {
	Lasca_Area = New_Lasca_Area;
}

void Frame::Set_Dot_Position(vector<int> New_Dot_Position) {
	Dot_Position = New_Dot_Position;
}

void Frame::Add_Contrast_Image(Mat Input)
{
	Contrast_Images.push_back(Input);

	if (Contrast_Images.size() > Filter_Window_Size)
	{
		Contrast_Images.erase(Contrast_Images.begin()+0);
	}
}

void Frame::Set_Filter_Window_Size(int value)
{
	Filter_Window_Size = value;
}
// Get functions
Mat Frame::Get_Base_Image() {
	return(Base_Image);
}

Mat Frame::Get_Laser_Image() {
	return(Laser_Image);
}

Mat Frame::Get_Contrast_Image() {
	for (int k = 0; k < Contrast_Images.size(); k++)
	{
		//Temporary_Contrasts.push_back(CalculateContrast2(Contrast_Images[k], Lasca_Area));
	}

	Contrast_Image = Temporary_Contrasts[0]; //TemporalFiltering(Temporary_Contrasts);
	Temporary_Contrasts.clear();
	return Contrast_Image;
}

Mat Frame::Get_Time_Averaged_Image() {
	return(Time_Averaged_Image);
}

Mat Frame::Get_Perfusion_Image() {
	return(Perfusion_Image);
}

void Frame::Set_Filename(string File_Name)
{
	"Averaged_Contrast_" + File_Name;
	"Base_Filename_" + File_Name;

	Video_Contrast.open("images\\" + Averaged_Contrast_Filename + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);
	Video_Base.open("images\\" + Base_Filename + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);
	
}

void Frame::Save_Frame()
{
	Video_Base.write(Base_Image);
//	Video_Contrast.write(Contrast_Image);
}

void Frame::Take_Picture(string Type)
{
	if (Which_Camera == "Webcam")
	{

		Web_Cam >> Temp_Matrix; //Double since it interacts wierdly with pauses.
		Web_Cam >> Temp_Matrix;
		if (Type == "BaseImage")
		{
			Base_Image = Temp_Matrix;
		}
		else if (Type == "LaserImage")
		{
			//Temp_Matrix = RemoveAmbientLight(Base_Image, Temp_Matrix, 0); //Don't know why this doesn't works right now
			//Temp_Matrix = CalculateContrast2(Temp_Matrix, Lasca_Area);
			Add_Contrast_Image(Temp_Matrix);
		}
	}
	else if (Which_Camera == "Fly") //This is untested. It alsod needs some renaming.
	{
		BW_Cam.StartCapture();
		//Image rawImage;
		BW_Cam.RetrieveBuffer(&rawImage);
		rawImage.Convert(FlyCapture2::PIXEL_FORMAT_BGR, &rgbImage);
		unsigned int rowBytes = (double)rgbImage.GetReceivedDataSize() / (double)rgbImage.GetRows(); //Converts the Image to Mat
		cv::Mat image = cv::Mat(rgbImage.GetRows(), rgbImage.GetCols(), CV_8UC3, rgbImage.GetData(), rowBytes);

		cv::Mat smallimage; //To resize the image, until we figure out how to take smaller pictures 
		cv::resize(image, smallimage, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);
		Temp_Matrix = smallimage;
		if (Type =="BaseImage")
		{ 
			Base_Image = Temp_Matrix;
		}
		else if (Type == "LaserImage")
		{ 
			//Temp_Matrix = RemoveAmbientLight(Base_Image, Temp_Matrix, 0); //Don't know why this doesn't works right now
			//Temp_Matrix = CalculateContrast(Temp_Matrix, Lasca_Area);
			Add_Contrast_Image(Temp_Matrix);
		}

	}
	else 
	{
		Web_Cam >> Temp_Matrix; //Double since it interacts wierdly with pauses.
		Web_Cam >> Temp_Matrix;
		if (Type == "BaseImage")
		{
			Web_Cam >> Base_Image;
			Web_Cam >> Base_Image;
		}
		else if (Type == "LaserImage")
		{
			//Temp_Matrix = RemoveAmbientLight(Base_Image, Temp_Matrix, 0); //Don't know why this doesn't works right now
			//Temp_Matrix = CalculateContrast(Temp_Matrix, Lasca_Area);
			Add_Contrast_Image(Temp_Matrix);
		}
	}
}
void Frame::open()
{
	Web_Cam.open(0);
}

//Constructos
Frame::Frame()
{}
Frame::Frame(string File_Name, int Width, int Height, string Camera, int Lasca_Size)
{
	Lasca_Area = Lasca_Size;
	
	Filter_Window_Size = 2;
	Averaged_Contrast_Filename = "Averaged_Contrast_" + File_Name;
	Base_Filename = "Base_Filename_" + File_Name;
	Video_Contrast.open("images\\" + Averaged_Contrast_Filename +".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);
	Video_Base.open("images\\" + Base_Filename +".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);

	Which_Camera = Camera;

	if (Camera == "Webcam")
	{ 
		VideoCapture temp(0);
		Web_Cam = temp;
	}
	else if (Camera == "Fly") //Untested
	{
		BW_Cam.Connect(0);
		BW_Cam.StartCapture();
	}
	else
	{
		VideoCapture temp(Camera + ".avi");
		Web_Cam = temp;
	}
}


void Frame::operator=(Frame &arg)
{
	Lasca_Area = arg.Lasca_Area;

	Filter_Window_Size = 2;

	Averaged_Contrast_Filename = arg.Averaged_Contrast_Filename;
	Base_Filename = arg.Base_Filename;
	Video_Contrast.open("images\\" + Averaged_Contrast_Filename + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);
	Video_Base.open("images\\" + Base_Filename + ".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, cv::Size(Width, Height), true);

	Which_Camera = arg.Which_Camera;

	if (Which_Camera == "Webcam")
	{
		VideoCapture temp(0);
		Web_Cam = temp;
	}
	else if (Which_Camera == "Fly") //Untested
	{
		BW_Cam.Connect(0);
		BW_Cam.StartCapture();
	}
	else
	{
		VideoCapture temp(Which_Camera + ".avi");
		Web_Cam = temp;
	}

}