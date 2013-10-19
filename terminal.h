#ifndef TERMINAL_H
#define TERMINAL_H

#include <QPlainTextEdit>

class Terminal : public QPlainTextEdit
{
	Q_OBJECT

signals:
	void sendData(const QByteArray &data);

public:
	explicit Terminal(QWidget *parent = 0);
	void putData(const QByteArray &data, bool external);
	
protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *e);
	virtual void contextMenuEvent(QContextMenuEvent *e);

signals:
	
public slots:
	
};

#endif // TERMINAL_H
