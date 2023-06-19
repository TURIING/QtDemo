//
// Created by TURIING on 2023/6/18.
//

#include "Battery.h"

Battery::Battery(QWidget *_parent) : QWidget(_parent) {
    m_minValue = 0;
    m_maxValue = 100;
    m_targetValue = 0;
    m_currentValue = 0;
    m_alarmValue = 30;

    m_isEnableAnimation = true;
    m_animationStep = 0.5;

    m_borderWidth = 2;
    m_borderRadius = 8;
    m_bodyRadius = 5;
    m_headRadius = 3;

    m_borderColorStart = QColor(100, 100, 100);
    m_borderColorEnd = QColor(80, 80, 80);
    m_alarmColorStart = QColor(250, 118, 113);
    m_alarmColorEnd = QColor(204, 38, 38);
    m_normalColorStart = QColor(50, 205, 51);
    m_normalColorEnd = QColor(60, 179, 133);

    m_isForward = false;
    m_timer = new QTimer(this);
    m_timer->setInterval(10);
    connect(m_timer, &QTimer::timeout, this, &Battery::m_updateValue);
}

void Battery::m_updateValue() {
    if(m_isForward) {
        m_currentValue -= m_animationStep;
        if(m_currentValue <= m_targetValue) {
            m_currentValue = m_targetValue;
            m_timer->stop();
        }
    }
    else {
        m_currentValue += m_animationStep;
        if(m_currentValue >= m_targetValue) {
            m_currentValue = m_targetValue;
            m_timer->stop();
        }
    }

    this->update();
}

void Battery::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 开启反锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    m_drawBorder(painter);

    m_drawBody(painter);

    m_drawHead(painter);

}

/*
 * 绘制边框
 */
void Battery::m_drawBorder(QPainter &_painter) {
    _painter.save();

    qreal headWidth = this->width() / 15;
    qreal bodyWidth = this->width() - headWidth;

    QPointF pointTopLeft(m_borderWidth, m_borderWidth);
    QPointF pointBottomRight(bodyWidth, this->height() - m_borderWidth);
    m_batteryArea = QRectF(pointTopLeft, pointBottomRight);

    _painter.setPen(QPen(m_borderColorStart, m_borderWidth));
    _painter.setBrush(Qt::NoBrush);
    _painter.drawRoundedRect(m_batteryArea, m_borderRadius, m_borderRadius);

    _painter.restore();
}

/*
 * 绘制主体
 */
void Battery::m_drawBody(QPainter &_painter) {
    if(m_targetValue == m_minValue)
        return;

    _painter.save();

    /* 配置渐变 */
    QLinearGradient batteryBodyGradient(QPointF(0, 0), QPointF(0, this->height()));
    // 电量低于警戒值
    if(m_currentValue <= m_alarmValue) {
        // 设置渐变起始颜色
        batteryBodyGradient.setColorAt(0.0, m_alarmColorStart);
        // 设置渐变结束颜色
        batteryBodyGradient.setColorAt(1.0, m_alarmColorEnd);
    }
    // 电量处于正常范围
    else {
        batteryBodyGradient.setColorAt(0.0, m_normalColorStart);
        batteryBodyGradient.setColorAt(1.0, m_normalColorEnd);
    }

    int margin = qMin(this->width(), this->height()) / 20;
    qreal unit = (m_batteryArea.width() - (margin * 2)) / (m_maxValue - m_minValue);
    qreal width = m_currentValue * unit;
    QPointF pointTopLeft(m_batteryArea.topLeft().x() + margin, m_batteryArea.topLeft().y() + margin);
    QPointF pointBottomRight(width + margin + m_borderWidth, m_batteryArea.bottomRight().y() - margin);
    QRectF bodyRect(pointTopLeft, pointBottomRight);

    _painter.setPen(Qt::NoPen);
    _painter.setBrush(batteryBodyGradient);
    _painter.drawRoundedRect(bodyRect, m_bodyRadius, m_bodyRadius);

    _painter.restore();
}

void Battery::m_drawHead(QPainter &_painter) {
    _painter.save();

    QPointF pointTopLeft(m_batteryArea.topRight().x(), this->height() / 3);
    QPointF pointBottomRight(this->width(), this->height() - this->height() / 3);
    QRectF headRect(pointTopLeft, pointBottomRight);

    QLinearGradient batteryHeadGradient(headRect.topLeft(), headRect.bottomLeft());
    batteryHeadGradient.setColorAt(0.0, m_borderColorStart);
    batteryHeadGradient.setColorAt(1.0, m_borderColorEnd);

    _painter.setPen(Qt::NoPen);
    _painter.setBrush(batteryHeadGradient);
    _painter.drawRoundedRect(headRect, m_headRadius, m_headRadius);

    _painter.restore();
}

qreal Battery::getMinValue() const {
    return m_minValue;
}

qreal Battery::getMaxValue() const {
    return m_maxValue;
}

qreal Battery::getTargetValue() const {
    return m_targetValue;
}

qreal Battery::getAlarmValue() const {
    return m_alarmValue;
}

bool Battery::isEnableAnimation() const {
    return m_isEnableAnimation;
}

qreal Battery::getAnimationStep() const {
    return m_animationStep;
}



void Battery::setRange(qreal _minValue, qreal _maxValue) {
    if(_minValue > _maxValue)
        return;

    this->m_minValue = _minValue;
    this->m_maxValue = _maxValue;

    if(m_targetValue < _minValue)
        setTargetValue(_minValue);
    else if(m_targetValue > _maxValue)
        setTargetValue(_maxValue);

    this->update();
}

void Battery::setMinValue(qreal _minValue) {

}

void Battery::setMaxValue(qreal _maxValue) {

}

void Battery::setTargetValue(qreal _targetValue) {
    //值和当前值一致则无需处理
    if(m_targetValue == _targetValue)
        return;

    if(_targetValue < m_minValue)
        _targetValue = m_minValue;
    else if(_targetValue > m_maxValue)
        _targetValue = m_maxValue;

    if(_targetValue > m_currentValue)
        m_isForward = false;
    else if(_targetValue < m_currentValue)
        m_isForward = true;
    else {
        m_targetValue = _targetValue;
        this->update();
        return;
    }

    m_targetValue = _targetValue;
    emit valueChanged(_targetValue);
    if(m_isEnableAnimation) {
        m_timer->stop();
        m_timer->start();
    } else {
        m_currentValue = _targetValue;
        this->update();
    }
}

void Battery::setAlarmValue(qreal _alarmValue) {

}

void Battery::enableAnimation(bool _animation) {

}

void Battery::setAnimationStep(qreal _step) {

}




