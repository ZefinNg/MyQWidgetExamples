#ifndef IDENTIFIERINFO_H
#define IDENTIFIERINFO_H

#include <QString>

class IdentifierInfo
{
public:
    IdentifierInfo();

    QString text() const;
    void setText(const QString &text);

    double xEndCoord() const;
    void setXEndCoord(double xEndCoord);

    double yEndCoord() const;
    void setYEndCoord(double yEndCoord);

    double xStartCoord() const;
    void setXStartCoord(double xStartCoord);

    double yStartCoord() const;
    void setYStartCoord(double yStartCoord);

    int bracketStyle() const;
    void setBracketStyle(int bracketStyle);

private:
    int m_bracketStyle;
    QString m_text;
    double m_xStartCoord;
    double m_yStartCoord;
    double m_xEndCoord;
    double m_yEndCoord;
};

#endif // IDENTIFIERINFO_H
