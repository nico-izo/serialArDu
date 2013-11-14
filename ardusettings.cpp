#include "ardusettings.h"
#include "ui_ardusettings.h"

#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

ArDuSettings::ArDuSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ArDuSettings)
{
	ui->setupUi(this);


	connect(ui->applyButton, SIGNAL(clicked()),
			this, SLOT(apply()));
	fillPortsParams();
	fillPortsInfo();

	updateSettings();
}

ArDuSettings::~ArDuSettings()
{
	delete ui;
}

void ArDuSettings::fillPortsParams()
{
	ui->baudRate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
	ui->baudRate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
	ui->baudRate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
	ui->baudRate->addItem(QLatin1String("57600"), QSerialPort::Baud57600);
	ui->baudRate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
	ui->baudRate->addItem(QLatin1String("Custom"));

	ui->dataBits->addItem(QLatin1String("5"), QSerialPort::Data5);
	ui->dataBits->addItem(QLatin1String("6"), QSerialPort::Data6);
	ui->dataBits->addItem(QLatin1String("7"), QSerialPort::Data7);
	ui->dataBits->addItem(QLatin1String("8"), QSerialPort::Data8);
	ui->dataBits->setCurrentIndex(3);

	ui->parity->addItem(QLatin1String("None"), QSerialPort::NoParity);
	ui->parity->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
	ui->parity->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
	ui->parity->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
	ui->parity->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);

	ui->stopBits->addItem(QLatin1String("1"), QSerialPort::OneStop);
	ui->stopBits->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
	ui->stopBits->addItem(QLatin1String("2"), QSerialPort::TwoStop);

	ui->flowControl->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
	ui->flowControl->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
	ui->flowControl->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);
}

ArDuSettings::Settings ArDuSettings::settings() const
{
	return currentSettings;
}

void ArDuSettings::fillPortsInfo()
{
	ui->serialPortInfoList->clear();
	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		QStringList list;
		list << info.portName()
			 << info.description()
			 << info.manufacturer()
			 << info.systemLocation()
			 << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())
			 << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());

		ui->serialPortInfoList->addItem(list.first(), list);
	}
}


void ArDuSettings::updateSettings()
{
	currentSettings.name = ui->serialPortInfoList->currentText();

	// Baud Rate
	if (ui->baudRate->currentIndex() == 4) {
		// custom baud rate
		currentSettings.baudRate = ui->baudRate->currentText().toInt();
	} else {
		// standard baud rate
		currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
					ui->baudRate->itemData(ui->baudRate->currentIndex()).toInt());
	}
	currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

	// Data bits
	currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
				ui->dataBits->itemData(ui->dataBits->currentIndex()).toInt());
	currentSettings.stringDataBits = ui->dataBits->currentText();

	// Parity
	currentSettings.parity = static_cast<QSerialPort::Parity>(
				ui->parity->itemData(ui->parity->currentIndex()).toInt());
	currentSettings.stringParity = ui->parity->currentText();

	// Stop bits
	currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
				ui->stopBits->itemData(ui->stopBits->currentIndex()).toInt());
	currentSettings.stringStopBits = ui->stopBits->currentText();

	// Flow control
	currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
				ui->flowControl->itemData(ui->flowControl->currentIndex()).toInt());
	currentSettings.stringFlowControl = ui->flowControl->currentText();
}

void ArDuSettings::apply()
{
	updateSettings();
	hide();
}

void ArDuSettings::show()
{
	QDialog::show();

	fillPortsParams();
	fillPortsInfo();
}

