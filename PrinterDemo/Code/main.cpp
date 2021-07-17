#include "Views/MainWidget.h"
#include <QApplication>
#include <QWSServer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
#ifdef __arm__
    w.showFullScreen();

    //设置程序的编码格式，否则打印时转码为gb2312会混乱
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");             //GB2312 for window; UTF-8 for linux
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    QWSServer::setCursorVisible(false);
#else
    w.show();
#endif

    return a.exec();
}
