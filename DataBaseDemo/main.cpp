#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //目的在与使设计师预览界面与运行界面一致
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
