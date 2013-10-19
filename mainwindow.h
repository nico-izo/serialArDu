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
	void initSignals();
	QSerialPort *serial;
	void disableWasd();
	void enableWasd();

private slots:
	void writeData(const QByteArray &data);
	void writeQuietData(const QByteArray &data);
	void readData();
	void handleError(QSerialPort::SerialPortError error);
	void openSerialPort();
	void closeSerialPort();

};

#endif // MAINWINDOW_H
