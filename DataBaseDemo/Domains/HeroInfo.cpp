#include "HeroInfo.h"

HeroInfo::HeroInfo()
{
    m_id                = 0;
    m_name              = "";
    m_styleName         = "";
    m_faction           = "";
    m_position          = "";
    m_mount             = "";
    m_weapon            = "";
    m_birthAndDeathTime = "";
    m_posthumounsTitle  = "";
    m_allusion          = "";
    m_tips              = "";
}

int HeroInfo::id() const
{
    return m_id;
}

void HeroInfo::setId(int id)
{
    m_id = id;
}

QString HeroInfo::name() const
{
    return m_name;
}

void HeroInfo::setName(const QString &name)
{
    m_name = name;
}

QString HeroInfo::styleName() const
{
    return m_styleName;
}

void HeroInfo::setStyleName(const QString &styleName)
{
    m_styleName = styleName;
}

QString HeroInfo::faction() const
{
    return m_faction;
}

void HeroInfo::setFaction(const QString &faction)
{
    m_faction = faction;
}

QString HeroInfo::position() const
{
    return m_position;
}

void HeroInfo::setPosition(const QString &position)
{
    m_position = position;
}

QString HeroInfo::mount() const
{
    return m_mount;
}

void HeroInfo::setMount(const QString &mount)
{
    m_mount = mount;
}

QString HeroInfo::weapon() const
{
    return m_weapon;
}

void HeroInfo::setWeapon(const QString &weapon)
{
    m_weapon = weapon;
}

QString HeroInfo::birthAndDeathTime() const
{
    return m_birthAndDeathTime;
}

void HeroInfo::setBirthAndDeathTime(const QString &birthAndDeathTime)
{
    m_birthAndDeathTime = birthAndDeathTime;
}

QString HeroInfo::posthumounsTitle() const
{
    return m_posthumounsTitle;
}

void HeroInfo::setPosthumounsTitle(const QString &posthumounsTitle)
{
    m_posthumounsTitle = posthumounsTitle;
}

QString HeroInfo::allusion() const
{
    return m_allusion;
}

void HeroInfo::setAllusion(const QString &allusion)
{
    m_allusion = allusion;
}

QString HeroInfo::tips() const
{
    return m_tips;
}

void HeroInfo::setTips(const QString &tips)
{
    m_tips = tips;
}

