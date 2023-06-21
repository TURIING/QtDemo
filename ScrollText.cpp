//
// Created by TURIING on 2023/6/20.
//

#include "ScrollText.h"

ScrollText::ScrollText(QWidget *_parent): QWidget(_parent) {
    m_labelTop = new QLabel(this);
    m_labelTop->hide();

    m_labelCurrent = new QLabel(this);
    m_labelCurrent->hide();

    m_propertyAnimationTop = new QPropertyAnimation(this);
    m_propertyAnimationTop->setTargetObject(m_labelTop);
    m_propertyAnimationTop->setPropertyName("geometry");
    m_propertyAnimationTop->setDuration(700);

    m_propertyAnimationCurrent = new QPropertyAnimation(this);
    m_propertyAnimationCurrent->setTargetObject(m_labelCurrent);
    m_propertyAnimationCurrent->setPropertyName("geometry");
    m_propertyAnimationCurrent->setDuration(700);
}

void ScrollText::setText(QString _text) {
    m_labelTop->setText(_text);
    if(m_labelCurrent->text().isEmpty()) {
        m_labelCurrent->setGeometry(0, 0, this->width(), this->height());
        m_labelCurrent->setText(_text);
        m_labelTop->setText(_text);
        if(m_labelCurrent->isHidden())
            m_labelCurrent->show();
    }else {
        m_labelTop->setText(m_labelCurrent->text());
        m_labelCurrent->setText(_text);
        if(m_labelCurrent->isHidden())
            m_labelCurrent->show();
        if(m_labelTop->isHidden())
            m_labelTop->show();

        m_propertyAnimationTop->stop();
        m_propertyAnimationTop->start();

        m_propertyAnimationCurrent->stop();
        m_propertyAnimationCurrent->start();
    }
}

void ScrollText::resizeEvent(QResizeEvent *_event) {
    auto width = _event->size().width();
    auto height = _event->size().height();

    m_propertyAnimationTop->setStartValue(QRect(0, 0, width, height));
    m_propertyAnimationTop->setEndValue(QRect(0, -height, width, height));

    m_propertyAnimationCurrent->setStartValue(QRect(0, height * 2, width, height));
    m_propertyAnimationCurrent->setEndValue(QRect(0, 0, width, height));

    QWidget::resizeEvent(_event);
}