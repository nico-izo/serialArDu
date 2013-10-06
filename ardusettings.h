#ifndef ARDUSETTINGS_H
#define ARDUSETTINGS_H

#include <QWidget>

namespace Ui {
class ArDuSettings;
}

class ArDuSettings : public QWidget
{
	Q_OBJECT
	
public:
	explicit ArDuSettings(QWidget *parent = 0);
	~ArDuSettings();
	
private:
	Ui::ArDuSettings *ui;
};

#endif // ARDUSETTINGS_H
