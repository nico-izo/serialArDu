#ifndef ARDUSETTINGS_H
#define ARDUSETTINGS_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class ArDuSettings;
}

class ArDuSettings : public QDialog
{
	Q_OBJECT
	
public:
	explicit ArDuSettings(QWidget *parent = 0);
	~ArDuSettings();

	struct Settings {
		QString name;
		qint32 baudRate;
		QString stringBaudRate;
		QSerialPort::DataBits dataBits;
		QString stringDataBits;
		QSerialPort::Parity parity;
		QString stringParity;
		QSerialPort::StopBits stopBits;
		QString stringStopBits;
		QSerialPort::FlowControl flowControl;
		QString stringFlowControl;
		bool localEchoEnabled;
	};

	Settings settings() const;
public slots:
	void show();
private:
	Ui::ArDuSettings *ui;
	void fillPortsParams();
	void fillPortsInfo();
	Settings currentSettings;
	void updateSettings();

private slots:
	void apply();

};

#endif // ARDUSETTINGS_H
