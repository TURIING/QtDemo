//
// Created by TURIING on 2023/6/21.
//

#ifndef QTDEMO_SPHERICALPROGRESSBAR_H
#define QTDEMO_SPHERICALPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <QMouseEvent>

class SphericalProgressBar: public QWidget{
    Q_OBJECT
public:
    explicit SphericalProgressBar(QWidget *_parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void mouseReleaseEvent(QMouseEvent *_event) override;
private:
    void drawBg(QPainter &_painter) const;
    void drawWave(QPainter &_painter);
    void drawText(QPainter &_painter) const;
private:
    int m_size = 100;                                           // Widget的尺寸
    qreal m_waterDensity = 5;                                   // 水波的密度
    qreal m_waterHeightRate = 0.03;                             // 水波波动的高度比率，水波的高度=高度比率*窗口高度
    qreal m_progressMax = 100;                                  // 进度最大值
    qreal m_progressMin = 0;                                    // 进度最小值
    qreal m_value = 0;                                          // 当前进度值
    qreal m_offset = 50;

    QColor m_waveBgColor = QColor(Qt::white);              // 水波背景色
    QColor m_waveFgColor = QColor(Qt::blue);               // 水波前景色

    /* 窗体移动相关 */
    bool m_isPressing = false;                                   // 窗体是否被按下
    QPoint m_pos;                                                // 窗体拖拽前的全局位置，即鼠标指针相对于整个屏幕的坐标
    QPoint m_originalPoint;                                      // 窗体拖拽前的左上角坐标
public slots:
    void start();
    void reset();
};


#endif //QTDEMO_SPHERICALPROGRESSBAR_H
