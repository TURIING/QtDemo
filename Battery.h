//
// Created by TURIING on 2023/6/18.
//

#ifndef QTDEMO_BATTERY_H
#define QTDEMO_BATTERY_H

#include <QWidget>
#include <QtGlobal>
#include <QTimer>
#include <QPainter>
#include <QLinearGradient>

class Battery: public QWidget {
    Q_OBJECT

public:
    explicit Battery(QWidget *_parent = nullptr);
    /* getter */
    qreal getMinValue() const;
    qreal getMaxValue() const;
    qreal getTargetValue() const;
    qreal getAlarmValue() const;
    bool isEnableAnimation() const;
    qreal getAnimationStep() const;

    void setMinValue(qreal _minValue);
    void setMaxValue(qreal _maxValue);

    void setAlarmValue(qreal _alarmValue);
    void enableAnimation(bool _animation);
    void setAnimationStep(qreal _step);

    void setRange(qreal _minValue, qreal _maxValue);



protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void m_drawBorder(QPainter &_painter);
    void m_drawBody(QPainter &_painter);
    void m_drawHead(QPainter &_painter);
private:
    qreal m_minValue;                                       // 电量最小值
    qreal m_maxValue;                                       // 最大值
    qreal m_targetValue;                                    // 目标电量
    qreal m_currentValue;                                   // 当前电量
    qreal m_alarmValue;                                     // 电量警戒值

    bool m_isEnableAnimation;                               // 是否启用动画效果
    qreal m_animationStep;                                  // 动画显示的步长

    uint m_borderWidth;                                     // 边框宽度
    uint m_borderRadius;                                    // 边框圆角角度
    uint m_bodyRadius;                                      // 电量进度条圆角角度
    uint m_headRadius;                                      // 头部的圆角角度

    QColor m_borderColorStart;                              // 边框渐变开始时的颜色
    QColor m_borderColorEnd;                                // 边框渐变结束时的颜色
    QColor m_alarmColorStart;                               // 低电量时渐变开始的颜色
    QColor m_alarmColorEnd;                                 // 低电量时渐变结束的颜色
    QColor m_normalColorStart;                              // 电量正常时渐变开始的颜色
    QColor m_normalColorEnd;                                // 电量正常时渐变结束的颜色

    bool m_isForward;                                       // 是否往前移动
    QRectF m_batteryArea;                                   // 电池主体区域
    QTimer *m_timer;
public slots:
    void setTargetValue(qreal _targetValue);
private slots:
    void m_updateValue();
public: signals:
    void valueChanged(qreal _value);
};


#endif //QTDEMO_BATTERY_H
