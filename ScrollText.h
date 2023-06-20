//
// Created by TURIING on 2023/6/20.
//

#ifndef QTDEMO_SCROLLTEXT_H
#define QTDEMO_SCROLLTEXT_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QDebug>

class ScrollText: public QWidget {
    Q_OBJECT
public:
    explicit ScrollText(QWidget *_parent = nullptr);

    void setText(QString _text);

protected:
    void resizeEvent(QResizeEvent *_event) override;
private:
    QLabel *m_labelTop = nullptr;
    QLabel *m_labelCurrent = nullptr;

    QPropertyAnimation *m_propertyAnimationTop = nullptr;
    QPropertyAnimation *m_propertyAnimationCurrent = nullptr;
};




#endif //QTDEMO_SCROLLTEXT_H
