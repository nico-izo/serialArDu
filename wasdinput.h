#ifndef WASDINPUT_H
#define WASDINPUT_H

#include <QLineEdit>
#include <QPushButton>

class WasdInput : public QLineEdit
{
	Q_OBJECT

signals:
	void sendData(const QByteArray &data);

public:
	explicit WasdInput(QWidget *parent = 0);
	void setButtons(QPushButton *W, QPushButton *A, QPushButton *S, QPushButton *D);
signals:
	
public slots:
	
protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void keyReleaseEvent(QKeyEvent *e);

private:
	QPushButton *_W;
	QPushButton *_A;
	QPushButton *_S;
	QPushButton *_D;
};

#endif // WASDINPUT_H
