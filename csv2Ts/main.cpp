#include <QCoreApplication>
#include "CSV2Ts.h"
#include "TsParser.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    TsParser tsParser;
    tsParser.setFilePath("/home/feng/Desktop/french.ts");

//    return a.exec();
}
