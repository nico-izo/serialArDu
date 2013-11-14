#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QMessageBox>
#include "terminal.h"
#include "commandinput.h"
#include "wasdinput.h"
#include "ardusettings.h"

#include "roverwidget.h"

namespace Ui {
class MainWindow;
}

class Terminal;
class CommandInput;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Terminal *terminal;
	CommandInput *commandInput;
	WasdInput *wasdInput;
	Ui::MainWindow *ui;
	ArDuSettings *settings;
	RoverWidget *rovermodel;
	void initSignals();
	QSerialPort *serial;
	void disableWasd();
	void enableWasd();
	QString rotation;
	void updateRotation();
	QMessageBox *_error;

private slots:
	void writeData(const QByteArray &data);
	void writeQuietData(const QByteArray &data);
	void readData();
	void handleError(QSerialPort::SerialPortError error);
	void openSerialPort();
	void closeSerialPort();
	void open3Dmodel();

};

#endif // MAINWINDOW_H
