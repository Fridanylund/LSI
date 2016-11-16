/*
This document contains functions not bound to a specific class.
*/
#pragma once

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>

#include "FlyCapture2.h" //This one will give errors unless camera thingy is fixed
#include "Free-Functions.h"

#include<iostream>
#include <chrono>
#include <time.h>
//#include <thread>
#include <windows.h>
#include<conio.h> 



using namespace std;
using namespace FlyCapture2;
using namespace cv;

//Substracts each pixel value in one images from the corresponding pixel value in another. Threshold is the lowset pixel value that is retained.
cv::Mat RemoveAmbientLight(cv::Mat baseimage, cv::Mat laserimage,int threshhold)
{
	cv::Mat result;

	result = laserimage - baseimage;
	threshold(result, result, threshhold, 0, THRESH_TOZERO);

	return result;
}

cv::Mat CalculateContrast(cv::Mat input, int lascaSize) //There is some(read alot) problems with the iteration 
{

	int H = input.rows/lascaSize; //Needs a way to make sure size is divisible by lascaSize
	int W = input.cols/lascaSize; //As of now these are a bit misleading

	cv::Mat perfusionimage = cv::Mat::ones(H, W, CV_8U); //CV_8U is imagetype, and in this case is black and white.

	cv::Scalar mean;
	cv::Scalar std;
	double contrast; 
	int k = 0;
	
	for (int width_it = 0; width_it <= W - 1; width_it++)
	{
		for (int height_it = 0; height_it <= H - 1; height_it++)
		{

			cv::Mat tempLascaArea(input, cv::Range(lascaSize*height_it, lascaSize*(1 + height_it)), cv::Range(lascaSize*width_it, lascaSize*(1 + width_it)));
			cv::meanStdDev(tempLascaArea, mean, std);
			contrast = std.val[0] / mean.val[0] * 255;
			perfusionimage.at<uchar>(height_it, width_it) = contrast;
		}

	}
	resize(perfusionimage, perfusionimage, cv::Size(input.cols, input.rows), 0, 0, cv::INTER_CUBIC);
	return perfusionimage;
}

cv::Mat CalculateContrast2(cv::Mat input, int lascaSize) //There is some(read alot) problems with the iteration 
{
	cv::cvtColor(input, input, CV_BGR2GRAY);
	int H = input.rows / lascaSize; 
	int W = input.cols / lascaSize; 

	cv::Mat perfusionimage = cv::Mat::ones(H, W, CV_8U);
	double contrast;
	uchar* p;
	uchar* p3 = input.ptr();
	double mean_value; 
	double mean_value_squared;
	double temp_value;
	int height_it, width_it,lasca_width_it, lasca_height_it;
	for (width_it = 0; width_it < H; width_it++)
	{
		p = perfusionimage.ptr<uchar>(width_it);
		for (height_it = 0; height_it < W ; height_it++)
		{
			for (lasca_width_it = 0; lasca_width_it < lascaSize; lasca_width_it++)
			{ 
				for (lasca_height_it = 0; lasca_height_it < lascaSize; lasca_height_it++)
				{
					temp_value = p3[lascaSize* input.cols*width_it + lasca_width_it*input.cols + lasca_height_it + height_it*lascaSize];
					mean_value += temp_value;
					mean_value_squared += temp_value*temp_value;
				}			
			}
			mean_value = mean_value / (lascaSize*lascaSize);
			mean_value_squared = mean_value_squared / (lascaSize*lascaSize); 
			p[height_it] = (sqrt(mean_value_squared - mean_value*mean_value) / mean_value) * 255;
			mean_value = 0;
			mean_value_squared = 0;
			
		}
	}
	resize(perfusionimage, perfusionimage, cv::Size(input.cols, input.rows), 0, 0, cv::INTER_CUBIC);
	return perfusionimage;
}



cv::Mat TemporalFiltering(vector<cv::Mat> input)
{

	Mat result;
	result = input[0]/ input.size();
	
	for (unsigned int k = 1; k <= input.size() -1 ; k++)
	{
		result = result + input[k]/ input.size();
	}
	return result;
}



vector<double> Calc_ROI_Average(Frame *Current_Working_Frame, vector<ROI> The_List_Of_ROIs) 
{
	Mat Perfusion_Image = Current_Working_Frame->Get_Perfusion_Image();
	vector<double> ROI_Averages;

	// Calculate the average of each ROI i in the vector.
	for (int i = 0; i <= The_List_Of_ROIs.size(); i++)
	{
		vector<int> Location = The_List_Of_ROIs.at(i).Get_ROI_Location();
		vector<int> Region = The_List_Of_ROIs.at(i).Get_ROI_Region();
		Mat ROI_Image = Perfusion_Image(Rect(Location.at(0), Location.at(1), Location.at(0) + Region.at(0), Location.at(1) + Region.at(1)));
		ROI_Averages.at(i) = mean(ROI_Image).val[0];
	}
	return(ROI_Averages);
}

/*
void Real_Time_Main(LSIProjectGUI* The_GUI) {
	Frame Working_Frame("LSI_Measurements", 640, 480, "Webcam", 5);
	
	while (The_GUI->Get_Run_Real_Time()) { // "Pointer to incomplete class type is not allowed."?
		cout << The_GUI->Get_Run_Real_Time() << endl;

		// Take images. Base image and laser images. And put these in the Frame object.
		// Preform all the calculations on the images.
		// Update the perfusion image shown in the GUI. Might have to send some input to the function for that?
		// Calculate the ROI averages and update them in the GUI.
	}
	// Check if the user wants to save the measurement files.
	// Remove frame and, if the user didn't want to save, remove the files.
} // I can't get it to work with the dependencies. The .h files include in a cycle.
*/

cv::Mat one_divided_by_kontrast(cv::Mat input)
{
	Mat temp = 1 / (input);
	return temp;
}

cv::Mat one_divided_by_kontrast_squared(cv::Mat input)
{
	Mat temp = 1 / (input ^ 2);
	return temp;
}

cv::Mat one_minus_kontrast(cv::Mat input)
{
	Mat temp = 1 - input;
	return temp;
}

cv::Mat kontrast_squared(cv::Mat input)
{
	Mat temp = input ^ 2;
	return temp;
}