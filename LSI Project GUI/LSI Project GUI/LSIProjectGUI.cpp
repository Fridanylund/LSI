#include "LSIProjectGUI.h"
#include "Test-function.h"
#include <QDebug>

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}


void LSIProjectGUI::on_startButton_clicked() {
	// Should, when it's ready, contain call to function Real_Time_Main in Free-Functions.
	/*Run_Real_Time = true;
	Real_Time_Main(this);*/

	ui.button_test->setText("START!");
	//stilltest();
	QPixmap bild;
	bild.load("3110_handwithlaser_1.png");
	ui.videoLabel->setPixmap(bild);

}

void LSIProjectGUI::on_stopButton_clicked() {
	// To stop the Real_Time_Main()
	// Run_Real_Time = false;

	ui.button_test->setText("STOP!");
}

void LSIProjectGUI::on_createROIButton_clicked() {
	ui.button_test->setText("ROI!");
}

void LSIProjectGUI::on_removeROIButton_clicked() {
	ui.button_test->setText("DELETED!");
}

void LSIProjectGUI::mousePressEvent(QMouseEvent *ev) {
	QString x = QString::number(ev->x());
	QString y = QString::number(ev->y());
	qDebug() << x << "," << y;
}
