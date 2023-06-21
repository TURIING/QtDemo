//
// Created by TURIING on 2023/6/21.
//

#include "SphericalProgressBar.h"

SphericalProgressBar::SphericalProgressBar(QWidget *_parent): QWidget(_parent) {
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedSize(m_size, m_size);

}

void SphericalProgressBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBg(painter);

    drawWave(painter);

    drawText(painter);

    QWidget::paintEvent(event);
}

/*
 * 绘制透明背景
 */
void SphericalProgressBar::drawBg(QPainter &_painter) const {
    _painter.save();

    _painter.setPen(QColor(0, 0, 0, 1));
    _painter.setBrush(QColor(0, 0, 0, 1));
    _painter.drawRect(QRect(0, 0, m_size, m_size));

    _painter.restore();
}

void SphericalProgressBar::drawWave(QPainter &_painter) {
    _painter.save();

    /* 水波路径 */
    /* 正弦曲线公式 y = A * sin(ωx + φ) + k */
    // “1-”是因为坐标轴是从左上角开始的，所以此处的百分比不是进度，而是1-进度，从上开始往下绘制
    qreal progressPercent = 1 - (m_value - m_progressMin) / (m_progressMax - m_progressMin);
    // w 周期, 水波的个数
    qreal w = m_waterDensity * M_PI / m_size;
    // A 振幅,水波波动的高度
    qreal A = m_size * m_waterHeightRate;
    // k，进度改变时，向上的偏移
    qreal k = m_size * progressPercent;

    QPainterPath wavePath1, wavePath2;
    //移动到左上角起始点
    wavePath1.moveTo(0, m_size);
    wavePath2.moveTo(0, m_size);

    m_offset += 0.6;
    if(m_offset > (m_size / 2))
        m_offset = 0;

    for(int axis_x = 0; axis_x <= m_size; axis_x++) {
        qreal waveY1, waveY2;
        //如果当前值为最小值则Y轴为高度
        if(m_value == m_progressMin)
            waveY1 = waveY2 = m_size;
        //如果当前值为最大值则Y轴为0
        else if(m_value == m_progressMax)
            waveY1 = waveY2 = 0;
        else {
            waveY1 = (A * sin(w * axis_x + m_offset)) + k;
            waveY2 = (A * sin(w * axis_x + m_offset + (m_size / 2 * w))) + k;
        }

        wavePath1.lineTo(axis_x, waveY1);
        wavePath2.lineTo(axis_x, waveY2);
    }

    wavePath1.lineTo(m_size, m_size);
    wavePath2.lineTo(m_size, m_size);

    /* 整个窗体构成的大圆路径 */
    QPainterPath CirclePath;
    CirclePath.addEllipse(0, 0, m_size, m_size);

    /* 大圆与水波的路径取交集 */
    QPainterPath resultPath1, resultPath2;
    resultPath1 = CirclePath.intersected(wavePath1);
    resultPath2 = CirclePath.intersected(wavePath2);

    QColor waveColor1 = m_waveFgColor;
    waveColor1.setAlpha(100);
    QColor waveColor2 = m_waveFgColor;
    waveColor2.setAlpha(180);

    _painter.setPen(Qt::NoPen);
    _painter.setBrush(waveColor1);
    _painter.drawPath(resultPath1);
    _painter.setBrush(waveColor2);
    _painter.drawPath(resultPath2);

    _painter.restore();
}

/*
 * 绘制文字
 */
void SphericalProgressBar::drawText(QPainter &_painter) const {
    _painter.save();

    QFont font;
    font.setPixelSize(m_size / 5);
    _painter.setPen(Qt::black);
    _painter.setFont(font);
    _painter.drawText(this->rect(), Qt::AlignCenter, QString("%0%").arg(m_value));

    _painter.restore();
}

void SphericalProgressBar::timerEvent(QTimerEvent *_event) {
    if(m_value < m_progressMax)
        m_value++;
    this->update();

    QObject::timerEvent(_event);
}

void SphericalProgressBar::mousePressEvent(QMouseEvent *_event) {
    if(_event->button() == Qt::LeftButton){
        m_isPressing = true;
        m_pos = _event->globalPos();
        m_originalPoint = this->frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(_event);
}

void SphericalProgressBar::mouseMoveEvent(QMouseEvent *_event) {
    if(m_isPressing) {
        QPoint distance = _event->globalPos() - m_pos;
        this->move(m_originalPoint + distance);
    }
    QWidget::mouseMoveEvent(_event);
}

void SphericalProgressBar::mouseReleaseEvent(QMouseEvent *_event) {
    if(_event->button() == Qt::LeftButton)
        m_isPressing = false;
    QWidget::mouseReleaseEvent(_event);
}

void SphericalProgressBar::start() {
    this->startTimer(100);
}

void SphericalProgressBar::reset() {
    m_value = m_progressMin;
}
