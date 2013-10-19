#include "terminal.h"
#include <QScrollBar>

Terminal::Terminal(QWidget *parent) :
	QPlainTextEdit(parent)
{
	//this->setEnabled(false);
	this->setReadOnly(true);
}

void Terminal::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Backspace:
	case Qt::Key_Left:
	case Qt::Key_Right:
	case Qt::Key_Up:
	case Qt::Key_Down:
		// skip processing
		break;
	default:
		QPlainTextEdit::keyPressEvent(e);
	}
}

void Terminal::mousePressEvent(QMouseEvent *e)
{
	Q_UNUSED(e)
	setFocus();
}

void Terminal::mouseDoubleClickEvent(QMouseEvent *e)
{
	Q_UNUSED(e)
}

void Terminal::contextMenuEvent(QContextMenuEvent *e)
{
	Q_UNUSED(e)
}

void Terminal::putData(const QByteArray &data, bool external)
{
	insertPlainText(QString(data));

	//QScrollBar *bar = verticalScrollBar();
	//bar->setValue(bar->maximum());
}
