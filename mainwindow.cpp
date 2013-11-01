#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	rotation = "";
	terminal = new Terminal(this);
	commandInput = new CommandInput(this);
	wasdInput = new WasdInput(this);
	settings = new ArDuSettings(this);
	serial = new QSerialPort(this);

	rovermodel = new RoverWidget();

	ui->setupUi(this);
	wasdInput->setButtons(ui->W, ui->A, ui->S, ui->D);
	ui->grid->addWidget(terminal, 0, 0, 1, 0);
	ui->grid->addWidget(commandInput, 1, 0, 2, 1);
	ui->grid2->addWidget(wasdInput, 2, 0, 2, 3);


	connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
			SLOT(handleError(QSerialPort::SerialPortError)));
	connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(commandInput, SIGNAL(sendData(QByteArray)), this, SLOT(writeData(QByteArray)));
	connect(wasdInput, SIGNAL(sendData(QByteArray)), this, SLOT(writeQuietData(QByteArray)));

	initSignals();

	ui->actionDisconnect->setEnabled(false);
	disableWasd();
	commandInput->setEnabled(false);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete terminal;
	delete commandInput;
	delete wasdInput;
}

void MainWindow::initSignals()
{
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->actionSettings, SIGNAL(triggered()), settings, SLOT(show()));
	connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
	connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui->actionClear, SIGNAL(triggered()), terminal, SLOT(clear()));
	connect(ui->actionOpen3D, SIGNAL(triggered()), this, SLOT(open3Dmodel()));
	//connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::writeData(const QByteArray &data)
{
	serial->write(data);
	terminal->putData(data, false);
}

void MainWindow::writeQuietData(const QByteArray &data)
{
	serial->write(data);
}

void MainWindow::closeSerialPort()
{
	serial->close();
	ui->actionConnect->setEnabled(true);
	ui->actionDisconnect->setEnabled(false);
	ui->actionSettings->setEnabled(true);
	ui->statusBar->showMessage(tr("Disconnected"));
	disableWasd();
}

void MainWindow::disableWasd()
{
	ui->W->setDisabled(true);
	ui->A->setDisabled(true);
	ui->S->setDisabled(true);
	ui->D->setDisabled(true);
	wasdInput->setDisabled(true);
	commandInput->setEnabled(false);
}

void MainWindow::enableWasd()
{
	ui->W->setDisabled(false);
	ui->A->setDisabled(false);
	ui->S->setDisabled(false);
	ui->D->setDisabled(false);
	wasdInput->setDisabled(false);
}

void MainWindow::readData()
{
	QByteArray data = serial->readAll();
	if(data.contains('^') || !rotation.isEmpty())
	{
		if(data.contains('^'))
			for(int i = data.indexOf('^'); i < data.length(); ++i)
			{
				if(data[i] == '^')
					continue;
				if(data[i] == '#')
				{
					updateRotation();
					break;
				}

				rotation += data[i];
			}
		else if(!rotation.isEmpty())
			for(int i = 0; i < data.length(); ++i)
			{
				if(data[i] == '#')
				{
					updateRotation();
					break;
				}

				rotation += data[i];
			}
	}

	terminal->putData(data, true);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
	if (error == QSerialPort::ResourceError) {
		QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
		closeSerialPort();
	}
}

void MainWindow::openSerialPort()
{
	ArDuSettings::Settings p = settings->settings();
	serial->setPortName(p.name);
	if (serial->open(QIODevice::ReadWrite)) {
		if (serial->setBaudRate(p.baudRate)
				&& serial->setDataBits(p.dataBits)
				&& serial->setParity(p.parity)
				&& serial->setStopBits(p.stopBits)
				&& serial->setFlowControl(p.flowControl)) {
			ui->actionConnect->setEnabled(false);
			ui->actionDisconnect->setEnabled(true);
			ui->actionSettings->setEnabled(false);
			ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
									   .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
									   .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

			enableWasd();
			commandInput->setEnabled(true);

		} else {
			serial->close();
			QMessageBox::critical(this, tr("Error"), serial->errorString());

			ui->statusBar->showMessage(tr("Open error"));
		}
	} else {
		QMessageBox::critical(this, tr("Error"), serial->errorString());

		ui->statusBar->showMessage(tr("Configure error"));
	}
}

void MainWindow::open3Dmodel()
{
	rovermodel->resize(800, 600);
	rovermodel->show();
}

void MainWindow::updateRotation()
{
	qDebug() << rotation;
	QStringList params = rotation.split(" ");
	//qDebug() << params[2].toDouble() << "HEY NANA \n";
	QQuaternion quat(params[2].toDouble(), params[3].toDouble(), params[4].toDouble(), params[5].toDouble());
	rovermodel->rotateModel(quat);
	rotation = "";
}
