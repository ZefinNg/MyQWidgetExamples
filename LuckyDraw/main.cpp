#include "LuckyDrawWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LuckyDrawWidget w;
    w.show();

    return a.exec();
}
