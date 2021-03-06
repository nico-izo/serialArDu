#include "roverwidget.h"

#include <QQuaternion>
#include <QMatrix4x4>

RoverWidget::RoverWidget(QWidget *parent) :
	QGLWidget(parent)
{
}

void RoverWidget::initializeGL(){
	glEnable(GL_DEPTH_TEST);
	rot = QMatrix4x4();
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_LINE_SMOOTH);
}


void RoverWidget::resizeGL (int width, int height){
	glViewport( 0, 0, (GLint)width, (GLint)height );

	/* create viewing cone with near and far clipping planes */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

	glMatrixMode( GL_MODELVIEW );
}

void RoverWidget::paintGL(){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-20.0f);
		glMultMatrixf(rot.constData());

	/* Cube. TODO: model */
	glBegin(GL_QUADS);

		//front
		glColor3f(1.0,0.0,0.0);

		glVertex3f(1.0,1.0,1.0);
		glVertex3f(-1.0,1.0,1.0);
		glVertex3f(-1.0,-1.0,1.0);
		glVertex3f(1.0,-1.0,1.0);


		//back

		glColor3f(0.0,1.0,0.0);

		glVertex3f(1.0,1.0,-1.0);
		glVertex3f(-1.0,1.0,-1.0);
		glVertex3f(-1.0,-1.0,-1.0);
		glVertex3f(1.0,-1.0,-1.0);


		//top
		glColor3f(0.0,0.0,1.0);

		glVertex3f(-1.0,1.0,1.0);
		glVertex3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,-1.0);
		glVertex3f(-1.0,1.0,-1.0);


		//bottom
		glColor3f(0.0,1.0,1.0);

		glVertex3f(1.0,-1.0,1.0);
		glVertex3f(1.0,-1.0,-1.0);
		glVertex3f(-1.0,-1.0,-1.0);
		glVertex3f(-1.0,-1.0,1.0);

		//right
		glColor3f(1.0,0.0,1.0);

		glVertex3f(1.0,1.0,1.0);
		glVertex3f(1.0,-1.0,1.0);
		glVertex3f(1.0,-1.0,-1.0);
		glVertex3f(1.0,1.0,-1.0);


		//left
		glColor3f(1.0,1.0,0.0);

		glVertex3f(-1.0,1.0,1.0);
		glVertex3f(-1.0,-1.0,1.0);
		glVertex3f(-1.0,-1.0,-1.0);
		glVertex3f(-1.0,1.0,-1.0);


	glEnd();

}

void RoverWidget::rotateModel(const QQuaternion &quat)
{
	rot = QMatrix4x4();
	rot.rotate(quat);
	updateGL();
}
