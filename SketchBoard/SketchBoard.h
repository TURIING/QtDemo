//
// Created by TURIING on 2023/8/13.
//

#ifndef QTDEMO_SKETCHBOARD_H
#define QTDEMO_SKETCHBOARD_H
#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>

class SketchBoard: public QWidget {
    Q_OBJECT
private:
    QVector<QVector<QPoint>> m_lines;
public:
    SketchBoard(QWidget *_parent = Q_NULLPTR) : QWidget(_parent){
        this->setWindowTitle("手写画板（单击右键清空，双击左键保存）");
    }
protected:
    void mouseMoveEvent(QMouseEvent *_event) override {
        if(_event->button() == Qt::RightButton) return;

        auto &lastLine = m_lines.last();
        lastLine.append(_event->pos());
        this->update();
    }

    void mousePressEvent(QMouseEvent *_event) override {
        /* 单击右键清屏 */
        if(_event->button() == Qt::RightButton) {
            m_lines.clear();
            this->update();
            return;
        }
        /* 按住左键开始绘制 */
        QVector<QPoint> newLine;
        newLine.append(_event->pos());
        m_lines.append(newLine);
        this->update();
    }

    void paintEvent(QPaintEvent *_event) override {
        QPainter painter(this);
        QPen pen(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);

        for(auto &line: m_lines) {
            painter.drawPolyline(line.data(), line.size());
        }
    }

    /* 双击保存 */
    void mouseDoubleClickEvent(QMouseEvent *_event) {
        this->grab().save("./demo.png");
        QMessageBox::information(this, "info", "保存成功");
    }

};

#endif //QTDEMO_SKETCHBOARD_H
