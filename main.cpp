#include "auth.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auth start;
    start.show();

    return a.exec();
}
