#include "AnimateButtonStyle.h"
#include "qpushbutton.h"


// 颜色常量
constexpr const char* Normal_COLOR = "#83d94c";
constexpr const char* Hover_COLOR = "#2cafff";

AnimateButtonStyle::AnimateButtonStyle(QStyle *style) : QProxyStyle(style)
{

}

AnimateButtonStyle::AnimateButtonStyle(const QString &key) : QProxyStyle(key)
{

}

AnimateButtonStyle::~AnimateButtonStyle()
{
    for (auto it = animations_.begin(); it != animations_.end(); ++it) {
        it.value()->ani->deleteLater();
        delete it.value();
    }
    animations_.clear();
}

void AnimateButtonStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)) {
        // 设置鼠标悬停属性
        widget->setAttribute(Qt::WA_Hover, true);

        AnimationData* data = new AnimationData{new QVariantAnimation, QColor(Normal_COLOR)};
        animations_[widget] = data;

        data->ani->setStartValue(QColor(Normal_COLOR));
        data->ani->setEndValue(QColor(Hover_COLOR));
        data->ani->setDuration(800);

        // 连接动画值变化信号
        connect(data->ani, &QVariantAnimation::valueChanged, this,
                [this, widget](const QVariant &value) {
                    if (animations_.contains(widget)) {
                        animations_[widget]->color = value.value<QColor>();
                        widget->update(); // 触发重绘
                    }
                });
    }
    QProxyStyle::polish(widget);
}

void AnimateButtonStyle::unpolish(QWidget *widget)
{
    if (animations_.contains(widget)) {
        AnimationData* data = animations_.take(widget);
        data->ani->stop();
        data->ani->deleteLater();
        delete data;
    }
    QProxyStyle::unpolish(widget);
}

void AnimateButtonStyle::drawControl(ControlElement element, const QStyleOption *opt, QPainter *painter, const QWidget *w) const
{
    if (element == CE_PushButton)
    {
        painter->save();
        // 复制选项，准备修改颜色
        QStyleOptionButton btnOpt = *qstyleoption_cast<const QStyleOptionButton *>(opt);
        painter->setBrush(QColor(Normal_COLOR));
        painter->setPen(Qt::NoPen);
        if(btnOpt.state & State_MouseOver)
        {
            if(animations_[w]->ani->startValue() != QColor(Normal_COLOR))
            {
                QVariantAnimation* anima = animations_[w]->ani;
                anima->stop();
                anima->setParent((QObject*)w);
                anima->setStartValue(QColor(Normal_COLOR));
                anima->setEndValue(QColor(Hover_COLOR));
                anima->setDuration(800);
                anima->start();
            }
            painter->setBrush(animations_[w]->color);
        }
        else if((btnOpt.state & State_MouseOver) == 0)
        {
            if(animations_[w]->ani->startValue() != QColor(Hover_COLOR))
            {
                QVariantAnimation* anima = animations_[w]->ani;
                anima->stop();
                anima->setParent((QObject*)w);
                anima->setStartValue(QColor(Hover_COLOR));
                anima->setEndValue(QColor(Normal_COLOR));
                anima->setDuration(800);
                anima->start();
            }
            painter->setBrush(animations_[w]->color);
        }
        painter->drawRoundedRect(btnOpt.rect, 4, 4);
        painter->setPen(Qt::white);
        painter->drawText(btnOpt.rect, Qt::AlignCenter, btnOpt.text);
        painter->restore();
    }
    else
    {
        QProxyStyle::drawControl(element, opt, painter, w);
    }
}
