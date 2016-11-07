#include "LSIProjectGUI.h"
#include "Test-function.h"
#include "qcustomplot.h"

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	LSIProjectGUI::makePlot();
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

void LSIProjectGUI::makePlot()
{
	QVector<double> x(101), y(101); // initialize with entries 0..100
	for (int i = 0; i<101; ++i)
	{
		x[i] = i / 50.0 - 1; // x goes from -1 to 1
		y[i] = x[i] * x[i]; // let's plot a quadratic function
	}
	// create graph and assign data to it:
	ui.customPlot->addGraph();
	ui.customPlot->graph(0)->setData(x, y);
	// give the axes some labels:
	ui.customPlot->xAxis->setLabel("x");
	ui.customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	ui.customPlot->xAxis->setRange(-1, 1);
	ui.customPlot->yAxis->setRange(0, 1);
	ui.customPlot->replot();
}