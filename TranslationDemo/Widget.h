#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QTranslator>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    enum LANGUAGE_TYPE {
        EN = 0,
        CH_ZN,
        RU
    };

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onLanguageChanged(int languageIndex);

private:
    Ui::Widget  *ui;
    QLabel      *m_label;
    QComboBox   *m_languageComboBox;
    QTranslator *m_translator;
};

#endif // WIDGET_H
