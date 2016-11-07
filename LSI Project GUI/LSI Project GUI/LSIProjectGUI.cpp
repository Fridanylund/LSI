#include "LSIProjectGUI.h"
#include "Test-function.h"

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void LSIProjectGUI::on_pushButton_clicked() {
	QPixmap bild;
	bild.load("3110_handwithlaser_1.png");
	ui.im_show->setPixmap(bild);
	ui.label_2->setText("Hellooo!");
}

void LSIProjectGUI::on_startButton_clicked() {
	ui.label_2->setText("START!");
	//stilltest();
}

void LSIProjectGUI::on_stopButton_clicked() {
	ui.label_2->setText("STOP!");
}

void LSIProjectGUI::on_createROIButton_clicked() {
	ui.label_2->setText("ROI!");
}

void LSIProjectGUI::on_removeROIButton_clicked() {
	ui.label_2->setText("DELETED!");
}