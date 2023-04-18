#include "Widget.h"
#include "GlobalText.h"
#include <QApplication>
#include <QTranslator>

extern QTranslator *g_translator = NULL;
extern GlobalText *globalText = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    globalText = new GlobalText();

    /**
     * 可以将QTranslator处理为全局变量，并在main函数中初始化，
     * 加载默认qm文件
     */
    g_translator = new QTranslator(qApp);
    QObject::connect(globalText, &GlobalText::changeLang, &a, [&a, g_translator](int langIndex) {
        if (g_translator != NULL) {
            qApp->removeTranslator(g_translator);
            delete g_translator;
            g_translator = NULL;
        }
        g_translator = new QTranslator(qApp);

        QString qmPath;
        switch (langIndex) {
        case 0:
            qmPath = QApplication::applicationDirPath()+"/zh_CN.qm";
            break;
        case 1:
            qmPath = QApplication::applicationDirPath()+"/ru_RU.qm";
            break;
        case 2:
            qmPath = QApplication::applicationDirPath()+"/en.qm";
            break;
        default:
            break;
        }

        g_translator->load(qmPath);
        qApp->installTranslator(g_translator);

        emit globalText->langTokenChanged("");
    });

    QString qmPath = QApplication::applicationDirPath()+"/ru_RU.qm";
    g_translator->load(qmPath);
    qApp->installTranslator(g_translator);

    Widget w;
    w.show();

    return a.exec();
}
