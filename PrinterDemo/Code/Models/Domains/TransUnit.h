#ifndef TRANSUNIT_H
#define TRANSUNIT_H

#include <QByteArray>

class TransUnit
{
public:
    enum UNIT_QUERY_TYPE {
        NONE_TYPE = -1,
        QUERY_STATUS = 0,
        QUERY_OFFLINE,
        QUERY_ERROR,
        QUERY_PAPER,
        CONFIG_FORMAT,
        PAPER_FEED,
        SNED_DATA
    };

    TransUnit();
    ~TransUnit();

    UNIT_QUERY_TYPE unitType() const;
    void setUnitType(const UNIT_QUERY_TYPE &unitType);

    QByteArray byteArray() const;
    void setByteArray(const QByteArray &byteArray);

    bool isQueryCmd();

    int resendTimes() const;
    void setResendTimes(int resendTimes);

private:
    UNIT_QUERY_TYPE m_unitType;
    QByteArray m_byteArray;
    int m_resendTimes;
};

#endif // TRANSUNIT_H
