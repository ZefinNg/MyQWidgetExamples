#ifndef GLOBALTEXT_H
#define GLOBALTEXT_H

#include <QObject>

class GlobalText : public QObject
{
    Q_OBJECT
public:
    explicit GlobalText(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GLOBALTEXT_H