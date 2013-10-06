#ifndef COMMANDINPUT_H
#define COMMANDINPUT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>


class CommandInput : public QLineEdit
{
	Q_OBJECT
public:
	explicit CommandInput(QWidget *parent = 0);
	
protected:
	virtual void keyPressEvent(QKeyEvent *e);

signals:
	void sendData(const QByteArray &data);
public slots:
	
};

#endif // COMMANDINPUT_H
