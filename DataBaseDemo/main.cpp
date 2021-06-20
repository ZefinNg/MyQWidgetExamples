#include "widget.h"
#include <QApplication>
#include <QDateTime>
#include <QMutex>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <stdio.h>
#include <stdlib.h>

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QString prefixString = "";
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        prefixString = "[Debug]";
        break;
    case QtInfoMsg:
        prefixString = "[Info]";
        break;
    case QtWarningMsg:
        prefixString = "[Warning]";
        break;
    case QtCriticalMsg:
        prefixString = "[Critical]";
        break;
    case QtFatalMsg:
        prefixString = "[Fatal]";
        abort();
    }

    QString dateString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString logString = prefixString + QString("[%1]%2 File:%3 Line:%4 Function:%5")
            .arg(dateString).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);

    fprintf(stderr, logString.toLatin1());

    QString logDirPath = QCoreApplication::applicationDirPath() + "/" +"LogDir";
    QDir logDir(logDirPath);
    if (!logDir.exists()) {
        logDir.mkdir(logDirPath);
    }

    // 输出信息至文件中（读写、追加形式）
    QString logFilePath = QDate::currentDate().toString("yyyy-MM-dd") + ".log";
    QFile file(logDirPath + "/" + logFilePath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << logString << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    //目的在与使设计师预览界面与运行界面一致
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    qInstallMessageHandler(myMessageHandler);

    Widget w;
    w.show();

    return a.exec();
}
