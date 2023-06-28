//
// Created by TURIING on 2023/6/26.
//

#include "Marquee.h"

Marquee::Marquee(QWidget *_parent): QLabel(_parent) {
    connect(&m_timer, &QTimer::timeout, this, [=]{
        if(this->isVisible()) {
            m_posX -= 1;
            if(_parent)
                _parent->update();
            else
                this->update();
        }
    });
}

void Marquee::paintEvent(QPaintEvent *_event) {
    QTextDocument doc;
    doc.setHtml(this->text());

    int left = doc.documentLayout()->documentSize().width();
    if(m_posX <= -left)
        m_posX = this->width();
    int height = doc.documentLayout()->documentSize().height();
    int y = (this->height() - height) / 2;

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    painter.translate(m_posX, y);

    doc.drawContents(&painter);
}

void Marquee::setText(const QString &_text) {
    this->clear();
    QString content = QStringLiteral("<font style='font-family:MicrosoftYaHei;font-size:14px;color: #01EEC3;'>%1</font>").arg(_text);
    m_timer.start(10);
    QLabel::setText(content);
//    this->adjustSize();
    m_posX = this->width();
}

void Marquee::clear() {
    m_timer.stop();
    m_posX = ORIGIN_X;
    QLabel::clear();
}
