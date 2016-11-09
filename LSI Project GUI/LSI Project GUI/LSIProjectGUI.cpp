#include "LSIProjectGUI.h"
#include "Test-function.h"

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}


void LSIProjectGUI::on_startButton_clicked() {
	// Should, when it's ready, contain call to function Real_Time_Main in Free-Functions.
	ui.button_test->setText("START!");
	//stilltest();
	QPixmap bild;
	bild.load("3110_handwithlaser_1.png");
	ui.videoLabel->setPixmap(bild);

}

void LSIProjectGUI::on_stopButton_clicked() {
	ui.button_test->setText("STOP!");
}

void LSIProjectGUI::on_createROIButton_clicked() {
	ui.button_test->setText("ROI!");
}

void LSIProjectGUI::on_removeROIButton_clicked() {
	ui.button_test->setText("DELETED!");
}