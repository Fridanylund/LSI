#pragma once
/*
This is where the Button class is declared.
*/
#pragma once
#include <opencv/cv.h>
#include <thread>
using namespace std;
using namespace cv;

class Button {
private:
	string Name;
	int Height;
	int Width;
	vector<int> Position;

public:
	function<void()> Button_Function; // Variable containing the button specific function.

	void Set_Name(string);
	void Set_Height(int);
	void Set_Width(int);
	void Set_Position(vector<int>);
	void Set_Button_Function(function<void()>);	 //void Set_Button_Function(Function);

	// Constructors
	Button(string Name, int Height, int Width, vector<int> Position, function<void()> Button_Func);
	Button();
};