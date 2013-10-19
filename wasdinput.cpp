#include "wasdinput.h"
#include <QKeyEvent>

WasdInput::WasdInput(QWidget *parent) :
	QLineEdit(parent)
{
}

void WasdInput::keyPressEvent(QKeyEvent *e)
{
	switch(e->key()) {
		case Qt::Key_W:
		case Qt::Key_Up:
			_W->animateClick();
			emit sendData("w");
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			_A->animateClick();
			emit sendData("a");
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			_S->animateClick();
			emit sendData("s");
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			_D->animateClick();
			emit sendData("d");
			break;
	}
}

void WasdInput::keyReleaseEvent(QKeyEvent *e)
{
	//_W->setFlat(false);
	Q_UNUSED(e);
}

void WasdInput::setButtons(QPushButton *W, QPushButton *A, QPushButton *S, QPushButton *D)
{
	_W = W;
	_A = A;
	_S = S;
	_D = D;
}
