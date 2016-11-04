/*
This is the ROI class and its functions.
*/
#include "ROIclass.h"

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