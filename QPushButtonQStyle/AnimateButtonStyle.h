#ifndef ANIMATEBUTTONSTYLE_H
#define ANIMATEBUTTONSTYLE_H

#include <QObject>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>
#include <QColor>
#include <QVariantAnimation>
#include <QMap>

// 动画数据结构
struct AnimationData {
    QVariantAnimation* ani;
    QColor color;
};

class AnimateButtonStyle : public QProxyStyle
{
    Q_OBJECT
public:
    AnimateButtonStyle(QStyle *style);
    AnimateButtonStyle(const QString& key);
    ~AnimateButtonStyle();

public:
    // 重写QStyle接口
    void polish(QWidget *widget) override;
    void unpolish(QWidget *widget) override;
    void drawControl(ControlElement element, const QStyleOption *opt,
                     QPainter *painter, const QWidget *w) const override;

private:
    // 存储widget对应的动画数据
    mutable QMap<const QWidget*, AnimationData*> animations_;
};

#endif // ANIMATEBUTTONSTYLE_H
