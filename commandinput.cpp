#include "commandinput.h"

CommandInput::CommandInput(QWidget *parent) :
	QLineEdit(parent)
{
}

void CommandInput::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
		case Qt::Key_Return:
		case Qt::Key_Enter:
			emit sendData(this->text().toLocal8Bit());
			this->setText("");
			break;

		default:
		QLineEdit::keyPressEvent(e);
	}
}
