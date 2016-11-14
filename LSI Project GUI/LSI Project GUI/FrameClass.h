/*
The Frame class and its public functions are declared here.
*/
#pragma once
#include <opencv/cv.h>
#include "FlyCapture2.h"
#include "Free-Functions.h"

using namespace std;
using namespace cv;
using namespace FlyCapture2;

class Frame {
private:
	vector<int> Exposure_Times;
	Mat Laser_Image;
	int Lasca_Area;
	vector<int> Dot_Position;
	Mat Base_Image;
	Mat Time_Averaged_Image;
	Mat Contrast_Image;
	Mat Perfusion_Image;
	int Filter_Window_Size;
	vector<Mat> Contrast_Images;
	string Averaged_Contrast_Filename;
	string Base_Filename;
	VideoWriter Video_Contrast;
	VideoWriter Video_Base;
	int Width;
	int Height;
	VideoCapture Web_Cam;
	Camera BW_Cam;
	string Which_Camera;
	Mat Temp_Matrix;
	Image rgbImage;
	Image rawImage;
	vector<Mat> Temporary_Contrasts;
	

public:
	void Set_Exposure_Times(vector<int>);
	void Set_Laser_Image(Mat);
	void Set_Time_Averaged_Image(Mat);
	void Set_Contrast_Image(Mat);
	void Set_Perfusion_Image(Mat);
	void Set_Lasca_Area(int);
	void Set_Dot_Position(vector<int>);
	void Set_Base_Image(Mat);
	Mat Get_Time_Averaged_Image();
	Mat Get_Contrast_Image();
	Mat Get_Perfusion_Image();
	Mat Get_Base_Image();
	Mat Get_Laser_Image();
	void Save_Frame();
	void Add_Contrast_Image(Mat Contrast_Image);
	void Set_Filter_Window_Size(int value);
	void Set_Filename(string File_Name);
	void Take_Picture(string Type);
	void open();


	//Constructor
	Frame(string File_Name, int Width, int Height, string Camera, int Lasca_Size);
	Frame();

	void operator=(Frame &arg);
};

