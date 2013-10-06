#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	terminal = new Terminal(this);
	commandInput = new CommandInput(this);
	ui->setupUi(this);
	ui->grid->addWidget(terminal, 0, 0, 1, 0);
	ui->grid->addWidget(commandInput, 1, 0, 2, 1);

	connect(commandInput, SIGNAL(sendData(QByteArray)), this, SLOT(writeData(QByteArray)));
}

MainWindow::~MainWindow()
{
	delete ui;
}
