#include "ardusettings.h"
#include "ui_ardusettings.h"

ArDuSettings::ArDuSettings(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ArDuSettings)
{
	ui->setupUi(this);
}

ArDuSettings::~ArDuSettings()
{
	delete ui;
}
