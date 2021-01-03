#include "Application.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

    int err = a.exec();
    w.Cleanup(err);
    return err;
}
