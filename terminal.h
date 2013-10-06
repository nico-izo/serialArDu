#ifndef TERMINAL_H
#define TERMINAL_H

#include <QPlainTextEdit>

class Terminal : public QPlainTextEdit
{
	Q_OBJECT
public:
	explicit Terminal(QWidget *parent = 0);
	
protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *e);
	virtual void contextMenuEvent(QContextMenuEvent *e);

signals:
	
public slots:
	
};

#endif // TERMINAL_H
