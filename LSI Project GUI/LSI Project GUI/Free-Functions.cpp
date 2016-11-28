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

//cv::Mat CalculateContrast2(cv::Mat input, int lascaSize, double Calib_Still, double Calib_Moving) //There is some(read alot) problems with the iteration 
//{
//	cv::cvtColor(input, input, CV_BGR2GRAY);
//	int H = input.rows / lascaSize; 
//	int W = input.cols / lascaSize; 
//
//	cv::Mat perfusionimage = cv::Mat::ones(H, W, CV_8U);
//	double contrast;
//	uchar* p;
//	uchar* p3 = input.ptr();
//	double mean_value; 
//	double mean_value_squared;
//	double temp_value;
//	double temp_contrast;
//	int height_it, width_it,lasca_width_it, lasca_height_it;
//	for (width_it = 0; width_it < H; width_it++)
//	{
//		p = perfusionimage.ptr<uchar>(width_it);
//		for (height_it = 0; height_it < W ; height_it++)
//		{
//			for (lasca_width_it = 0; lasca_width_it < lascaSize; lasca_width_it++)
//			{ 
//				for (lasca_height_it = 0; lasca_height_it < lascaSize; lasca_height_it++)
//				{
//					temp_value = p3[lascaSize* input.cols*width_it + lasca_width_it*input.cols + lasca_height_it + height_it*lascaSize];
//					
//					//if (Calib_Still > 0 & Calib_Moving > 0)
//					//{
//					//	temp_value = (temp_value - Calib_Moving)/(Calib_Still - Calib_Moving); //(C - CMoving) / (CStill - CMoving)
//					//}
//
//					mean_value += temp_value;
//					mean_value_squared += temp_value*temp_value;
//				}			
//			}
//			mean_value = mean_value / (lascaSize*lascaSize);
//			mean_value_squared = mean_value_squared / (lascaSize*lascaSize); 
//			temp_contrast = (sqrt(mean_value_squared - mean_value*mean_value) / mean_value)* 255;
//			if (Calib_Still > 0 & Calib_Moving > 0)
//			{
//				//temp_contrast = (temp_contrast - Calib_Still) / (Calib_Moving - Calib_Still);
//				temp_contrast = 255*((temp_contrast - Calib_Moving) / (Calib_Still - Calib_Moving)); //(C - CMoving) / (CStill - CMoving)
//			}
//			//if (temp_contrast >= 230)
//			//{
//			//	temp_contrast = 0;
//			//}
//			p[height_it] = temp_contrast;
//			mean_value = 0;
//			mean_value_squared = 0;		
//		}
//	}
//	cvtColor(perfusionimage, perfusionimage, cv::COLOR_GRAY2BGR);
//	resize(perfusionimage, perfusionimage, cv::Size(input.cols, input.rows), 0, 0, cv::INTER_CUBIC);
//	return perfusionimage;
//}

cv::Mat CalculateContrast2(cv::Mat input, int lascaSize, double Calib_Still, double Calib_Moving) //There is some(read alot) problems with the iteration 
{
	cv::cvtColor(input, input, CV_BGR2GRAY);
	int H = input.rows / lascaSize;
	int W = input.cols / lascaSize;

	cv::Mat perfusionimage = cv::Mat::ones(H, W, CV_64F);
	double contrast;
	double* p;
	uchar* p3 = input.ptr();
	double mean_value;
	double mean_value_squared;
	//double temp_value;
	int temp_value;
	double temp_contrast;
	int height_it, width_it, lasca_width_it, lasca_height_it;
	for (width_it = 0; width_it < H; width_it++)
	{
		p = perfusionimage.ptr<double>(width_it);
		for (height_it = 0; height_it < W; height_it++)
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
			if (mean_value > 0)
			{
				mean_value = mean_value / (lascaSize*lascaSize);
				mean_value_squared = mean_value_squared / (lascaSize*lascaSize);
				temp_contrast = (sqrt(mean_value_squared - mean_value*mean_value) / mean_value);
			}
			else
			{
				temp_contrast = 0; //Vilket värde?
			}

			if (Calib_Still > 0 & Calib_Moving > 0 & temp_contrast > Calib_Moving) //Krav på temp_contrast?
			{
				//temp_contrast = (temp_contrast - Calib_Still) / (Calib_Moving - Calib_Still);
				temp_contrast =((temp_contrast - Calib_Moving) / (Calib_Still - Calib_Moving)); //(C - CMoving) / (CStill - CMoving)
			}
			if (isnan(temp_contrast)) //Sätta till vilket värde?
			{
				temp_contrast = 0;
			}
			if (temp_contrast < 0) //Kollar varför den blir negativ
			{
				cout << "asd";
			}
			p[height_it] = temp_contrast;//temp_contrast;
			mean_value = 0;
			mean_value_squared = 0;
		}
	}
	//cvtColor(perfusionimage, perfusionimage, cv::COLOR_GRAY2BGR);
	resize(perfusionimage, perfusionimage, cv::Size(input.cols, input.rows), 0, 0, cv::INTER_CUBIC);
	return perfusionimage;
}

cv::Mat Convert_From_Double2Int(cv::Mat input)
{
	//int H = input.rows;
	//int W = input.cols;
	//Mat output = cv::Mat::ones(H, W, CV_8U)*255;
	//double* input_pointer = input.ptr<double>();
	//int* output_pointer = output.ptr<int>();
	//int image_size = H*W;//sizeof(input_pointer);

	//for (unsigned int p = 0; p < image_size-1; p++)
	//{
	//	double o = input_pointer[p];
	//	double i = input_pointer[p] * 255;
	//	output_pointer[p] = input_pointer[p]*255;
	//}
	return input*255;
}


//cv::Mat TemporalFiltering(vector<cv::Mat> input) //Needs to be redone to handle double instead of int
//{
//	int H = input[0].rows;
//	int W = input[0].cols;
//	int number_of_images = input.size();
//	Mat result = cv::Mat::zeros(H, W, CV_64F);
//	uchar* input_pointer;
//	uchar* output_pointer = result.ptr();
//	int image_size = sizeof(output_pointer);
//	
//		
//	for (unsigned int k = 0; k <= number_of_images - 1; k++)
//	{
//		input_pointer = input[k].ptr();
//		for (unsigned int p = 0; p < image_size; p++)
//		{
//			output_pointer[p] = output_pointer[p] + input_pointer[p] / number_of_images;
//
//		}
//	}
//	return result;
//}
cv::Mat TemporalFiltering(vector<cv::Mat> input) //Needs to be redone to handle double instead of int
{
	int H = input[0].rows;
	int W = input[0].cols;
	int number_of_images = input.size();
	Mat result = cv::Mat::zeros(H, W, CV_64F);
	double* input_pointer;
	double* output_pointer = result.ptr<double>();
	int image_size = sizeof(output_pointer);


	for (unsigned int k = 0; k <= number_of_images - 1; k++)
	{
		input_pointer = input[k].ptr<double>();
		for (unsigned int p = 0; p < H*W; p++)
		{
			double a = output_pointer[p];
			double b = input_pointer[p];
			output_pointer[p] = output_pointer[p] + input_pointer[p] / number_of_images;

		}
	}
	return result;
}



QVector<double> Calc_ROI_Average(cv::Mat Perfusion_Image, vector<ROI> The_List_Of_ROIs)
{
	QVector<double> ROI_Averages;

	// Calculate the average of each ROI i in the vector.
	for (int i = 0; i < The_List_Of_ROIs.size(); i++)
	{
		vector<int> Location = The_List_Of_ROIs.at(i).Get_ROI_Location();
		vector<int> Region = The_List_Of_ROIs.at(i).Get_ROI_Region();
		Mat ROI_Image = Perfusion_Image(Rect(Location.at(0), Location.at(1), Region.at(0), Region.at(1)));
		ROI_Averages.append(mean(ROI_Image).val[0]);
	}
	return(ROI_Averages);
}

cv::Mat one_divided_by_kontrast(cv::Mat input)
{
	Mat temp = 255 / (input);
	return temp;
}

cv::Mat one_divided_by_kontrast_squared(cv::Mat input, bool log_it)
{
	int H = input.rows;
	int W = input.cols;
	Mat output = cv::Mat::zeros(H, W, CV_64F);
	double* input_pointer = input.ptr<double>();
	double* output_pointer = output.ptr<double>();
	uchar* temp = input.ptr();
	int image_size = W*H;//sizeof(input_pointer);

	for (unsigned int p = 0; p < image_size; p++)
	{
		double a = temp[0];
		double o = input_pointer[p];
		double i = 1/input_pointer[p];
		double u = i*i;
		if (log_it)
		{
			if (u <= 0) //För att se vad som ger "abnormala" värden. Och för att sätta en övre gräns
			{
				output_pointer[p] = 0;
			}
			else {
				output_pointer[p] = log(u);
			}
		
		}
		else {
			if (u > 1500) //För att se vad som ger "abnormala" värden. Och för att sätta en övre gräns
			{
				output_pointer[p] = 1500;
			}
			else {
				output_pointer[p] = u;
			}
		}
	}
	return output;
}
