#ifndef GLOBALTEXT_H
#define GLOBALTEXT_H

#include <QObject>

class GlobalText : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString langToken READ langToken NOTIFY langTokenChanged)

    explicit GlobalText();

    QString langToken() const;

signals:
    void langTokenChanged(QString langToken);
    void changeLang(int langIndex);

private:
    QString m_langToken;
};

#endif // GLOBALTEXT_H
