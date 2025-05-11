#include "MainWidget.h"
#include <QApplication>
#include <QFontDatabase>
#include "DatabaseManager/DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置字体
    int fontId = QFontDatabase::addApplicationFont(":/res/fonts/wqydkht_11958.ttf");
    QFont appFont(QFontDatabase::applicationFontFamilies(fontId).at(0));
    a.setFont(appFont);

    // a.setWindowIcon(QIcon("://app.ico"));

    MainWidget w;
    w.setWindowIcon(QIcon("://app.ico"));
    DatabaseManager::getInstance();

    w.show();

    return a.exec();
}
