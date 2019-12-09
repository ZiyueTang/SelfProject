#include <QApplication>
#include "cal.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	calculator cal;
	cal.show();
	return a.exec();
}
