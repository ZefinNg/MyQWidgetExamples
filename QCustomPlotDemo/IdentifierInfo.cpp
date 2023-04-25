#include "IdentifierInfo.h"

IdentifierInfo::IdentifierInfo()
{

}

QString IdentifierInfo::text() const
{
    return m_text;
}

void IdentifierInfo::setText(const QString &text)
{
    m_text = text;
}

double IdentifierInfo::xEndCoord() const
{
    return m_xEndCoord;
}

void IdentifierInfo::setXEndCoord(double xEndCoord)
{
    m_xEndCoord = xEndCoord;
}

double IdentifierInfo::yEndCoord() const
{
    return m_yEndCoord;
}

void IdentifierInfo::setYEndCoord(double yEndCoord)
{
    m_yEndCoord = yEndCoord;
}

double IdentifierInfo::xStartCoord() const
{
    return m_xStartCoord;
}

void IdentifierInfo::setXStartCoord(double xStartCoord)
{
    m_xStartCoord = xStartCoord;
}

double IdentifierInfo::yStartCoord() const
{
    return m_yStartCoord;
}

void IdentifierInfo::setYStartCoord(double yStartCoord)
{
    m_yStartCoord = yStartCoord;
}

int IdentifierInfo::bracketStyle() const
{
    return m_bracketStyle;
}

void IdentifierInfo::setBracketStyle(int bracketStyle)
{
    m_bracketStyle = bracketStyle;
}
