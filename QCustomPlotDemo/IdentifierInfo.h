#ifndef IDENTIFIERINFO_H
#define IDENTIFIERINFO_H

#include <QString>

class IdentifierInfo
{
public:
    IdentifierInfo();

    QString text() const;
    void setText(const QString &text);

    double xCoord() const;
    void setXCoord(double xCoord);

    double yCoord() const;
    void setYCoord(double yCoord);

private:
    QString m_text;
    double m_xCoord;
    double m_yCoord;
};

#endif // IDENTIFIERINFO_H
