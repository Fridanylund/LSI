#pragma once
/*
This document contains declarations of all functions not bound to a specific class.
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>

#include <QVector>
#include <iostream>
#include <chrono>
#include <time.h>
#include <thread>
#include <windows.h>
#include <conio.h> 
#include <vector>

#include "FlyCapture2.h" //This one will give errors unless camera thingy is fixed
#include "Test-Function.h"
#include "ROIclass.h"


cv::Mat RemoveAmbientLight(cv::Mat baseimage, cv::Mat laserimage, int threshhold);

cv::Mat CalculateContrast(cv::Mat input, int lascaSize);

cv::Mat CalculateContrast2(cv::Mat input, int lascaSize, double Calib_Still, double Calib_Moving);

cv::Mat TemporalFiltering(vector<cv::Mat> input);

QVector<double> Calc_ROI_Average(Mat Perfusion_Image, std::vector<ROI> The_List_Of_ROIs);

cv::Mat one_divided_by_kontrast(cv::Mat input);

cv::Mat one_divided_by_kontrast_squared(cv::Mat input);

cv::Mat one_minus_kontrast(cv::Mat input);

cv::Mat kontrast_squared(cv::Mat input);