#include "StudentAttendanceGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StudentAttendanceGUI window;
    window.show();
    return app.exec();
}
