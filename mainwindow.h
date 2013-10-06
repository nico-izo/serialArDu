#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include "terminal.h"
#include "commandinput.h"

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
	Ui::MainWindow *ui;
	Terminal *terminal;
	CommandInput *commandInput;

private slots:
	void writeData(const QByteArray &data);

};

#endif // MAINWINDOW_H
