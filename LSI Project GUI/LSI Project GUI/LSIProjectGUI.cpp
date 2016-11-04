#include "LSIProjectGUI.h"

LSIProjectGUI::LSIProjectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void LSIProjectGUI::on_push_button_clicked() {
	QPixmap bild;
	bild.load("3110_handwithlaser_1.png");

	
	//ui.im_show->setPixmap(bild);
}