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

double IdentifierInfo::xCoord() const
{
    return m_xCoord;
}

void IdentifierInfo::setXCoord(double xCoord)
{
    m_xCoord = xCoord;
}

double IdentifierInfo::yCoord() const
{
    return m_yCoord;
}

void IdentifierInfo::setYCoord(double yCoord)
{
    m_yCoord = yCoord;
}
