#include "TransUnit.h"

TransUnit::TransUnit()
{
    m_unitType = NONE_TYPE;
    m_byteArray.clear();
}

TransUnit::~TransUnit()
{

}

TransUnit::UNIT_QUERY_TYPE TransUnit::unitType() const
{
    return m_unitType;
}

void TransUnit::setUnitType(const UNIT_QUERY_TYPE &unitType)
{
    m_unitType = unitType;
}

QByteArray TransUnit::byteArray() const
{
    return m_byteArray;
}

void TransUnit::setByteArray(const QByteArray &byteArray)
{
    m_byteArray = byteArray;
}

bool TransUnit::isQueryCmd()
{
    if (m_unitType == QUERY_STATUS || m_unitType == QUERY_OFFLINE ||
            m_unitType == QUERY_ERROR || m_unitType == QUERY_PAPER)
        return true;

    return false;
}
