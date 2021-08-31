#ifndef TSREADWRITER_H
#define TSREADWRITER_H

#include <QObject>

class TsReadWriter : public QObject
{
    Q_OBJECT
public:
    explicit TsReadWriter(QObject *parent = nullptr);

signals:

};

#endif // TSREADWRITER_H
