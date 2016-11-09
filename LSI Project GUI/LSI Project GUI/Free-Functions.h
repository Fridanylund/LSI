#pragma once
/*
This document contains declarations of all functions not bound to a specific class.
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>

#include <iostream>
#include <chrono>
#include <time.h>
#include <thread>
#include <windows.h>
#include <conio.h> 
#include <vector>

#include "FlyCapture2.h" //This one will give errors unless camera thingy is fixed
#include "Test-Function.h"
//#include "FrameClass.h"
#include "ROIclass.h"
//#include "LSIProjectGUI.h" // Gives cycle.

//using namespace std;
//using namespace FlyCapture2;


cv::Mat RemoveAmbientLight(cv::Mat baseimage, cv::Mat laserimage, int threshhold);

cv::Mat CalculateContrast(cv::Mat input, int lascaSize);

cv::Mat CalculateContrast2(cv::Mat input, int lascaSize);

cv::Mat TemporalFiltering(vector<cv::Mat> input);

class Frame; // Forward declaration, part of getting rid of cycle includes.
std::vector<double> Calc_ROI_Average(Frame *Current_Working_Frame, std::vector<ROI> The_List_Of_ROIs);

/*class LSIProjectGUI;
void Real_Time_Main(LSIProjectGUI* The_GUI);*/