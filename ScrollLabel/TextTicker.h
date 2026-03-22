#ifndef TEXTTICKER_H
#define TEXTTICKER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class TextTicker : public QWidget
{
    Q_OBJECT

public:
    TextTicker(QWidget *parent = 0);
    ~TextTicker();

private:
    void showTicker();

    int m_curIndex;
    QLabel *m_label;
    QString m_showText;
};

#endif // TEXTTICKER_H
