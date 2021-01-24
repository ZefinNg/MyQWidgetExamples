#ifndef HEROINFO_H
#define HEROINFO_H

#include <QString>

class HeroInfo
{
public:
    HeroInfo();

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString styleName() const;
    void setStyleName(const QString &styleName);

    QString faction() const;
    void setFaction(const QString &faction);

    QString position() const;
    void setPosition(const QString &position);

    QString mount() const;
    void setMount(const QString &mount);

    QString weapon() const;
    void setWeapon(const QString &weapon);

    QString birthAndDeathTime() const;
    void setBirthAndDeathTime(const QString &birthAndDeathTime);

    QString posthumounsTitle() const;
    void setPosthumounsTitle(const QString &posthumounsTitle);

    QString allusion() const;
    void setAllusion(const QString &allusion);

    QString tips() const;
    void setTips(const QString &tips);

private:
    int     m_id;
    QString m_name;
    QString m_styleName;
    QString m_faction;
    QString m_position;
    QString m_mount;
    QString m_weapon;
    QString m_birthAndDeathTime;
    QString m_posthumounsTitle;
    QString m_allusion;
    QString m_tips;
};

#endif // HEROINFO_H
