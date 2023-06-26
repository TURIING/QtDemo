//
// Created by TURIING on 2023/6/26.
//

#ifndef QTDEMO_MARQUEE_H
#define QTDEMO_MARQUEE_H
#include <QLabel>
#include <QTimer>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QStyleOption>
#include <QPainter>

constexpr int ORIGIN_X = 5;

class Marquee: public QLabel {
    Q_OBJECT
public:
    explicit Marquee(QWidget *_parent = nullptr);
    void setText(const QString &_text);
protected:
    void paintEvent(QPaintEvent *_event);
private:
    void clear();

private:
    QTimer m_timer;
    int m_posX = ORIGIN_X;
};


#endif //QTDEMO_MARQUEE_H
