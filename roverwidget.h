#ifndef ROVERWIDGET_H
#define ROVERWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

class RoverWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit RoverWidget(QWidget *parent = 0);
	void rotateModel(const QQuaternion &quat);
	
signals:
	
public slots:

protected:
   void initializeGL();
   void paintGL();
   void resizeGL (int width, int height);
private:
   QMatrix4x4 rot;
	
};

#endif // ROVERWIDGET_H
