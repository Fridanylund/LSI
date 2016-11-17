/*
This is the ROI class and its functions.
*/
#include "ROIclass.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <chrono>

using namespace cv;

void ROI::Set_ROI_Location(vector<int> New_ROI_Location) {
	ROI_Location = New_ROI_Location;
}

void ROI::Set_ROI_Region(vector<int> New_ROI_Region) {
	ROI_Region = New_ROI_Region;
}

vector<int> ROI::Get_ROI_Location() {
	return(ROI_Location);
}

vector<int> ROI::Get_ROI_Region() {
	return(ROI_Region);
}

Mat ROI::Set_ROI(Mat Perfusion_Image)
{
	Mat ROI = Perfusion_Image(Rect(ROI_Location.at(0), ROI_Location.at(1), ROI_Region.at(0), ROI_Region.at(1)));
	return ROI;
}


//Constructor
ROI::ROI(vector<int> Location, vector<int> Region)
{
	ROI_Location = Location;
	ROI_Region = Region;
	ROI_Colour = 7;
}

ROI::ROI(vector<int> Location, vector<int> Region, int Colour)
{
	ROI_Location = Location;
	ROI_Region = Region;
	ROI_Colour = Colour;
}