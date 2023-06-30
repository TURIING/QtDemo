//
// Created by TURIING on 2023/6/29.
//

#ifndef QTDEMO_PAGESWITCHER_H
#define QTDEMO_PAGESWITCHER_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>
#include <QPalette>
#include <QMouseEvent>

class PageSwitcher: public QWidget{
    Q_OBJECT
    struct Item {
        QString text;
        bool has_message = false;
    };
public:
    explicit PageSwitcher(QWidget *_parent = nullptr);
    void append(const QString &_text, bool _has_message = false);
    void setCurrentItem(int _index);
    void setMessageAlert(int _index, bool _has_message = true);
protected:
    void paintEvent(QPaintEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void enterEvent(QEvent *_event) override;
    void leaveEvent(QEvent *_event) override;
private:
    void drawText(QPainter &_painter) const;
    void drawBackground(QPainter &_painter) const;
    void drawIndicateBar(QPainter &_painter) const;
    void drawMessageAlert(QPainter &_painter) const;

    int indexToWidth(int _index) const;
    QRect indexToRect(int _index) const;
    int computeTextWidth(const QString &_text) const;
    int computeTotalWidth(int _index) const;
    int mousePosToIndex() const;
private:
    QVector<Item> m_item;
    int m_currentItemIndex = -1;                                                            // 选中的item
    QPoint m_mousePos;                                                                      // 鼠标在控件内的位置
    bool m_isHover = false;                                                                 // 鼠标是否悬停在控件上

    /* UI 相关*/
    QFont m_textFont;                                                                       // 文本所用的字体
    QColor m_unActiveTextColor = QColor(107, 107, 107);                            // 未激活时文本颜色
    QColor m_activeTextColor = QColor(0, 0, 0);                                    // 激活时文本颜色
    QColor m_unActiveBgColor = QColor(249, 249, 249);                              // 未激活时的背景色
    QColor m_indicateBarColor = QColor(255, 108, 55);                              // 指示条的颜色
    QColor m_messageAlertColor = QColor(12, 187, 82);                              // 消息提醒小圆点的颜色
    const int m_paddingForHorizon = 15;                                                     // 每个区块内左右两边的空白大小
    const int m_messageAlertDiameter = 7;                                                   // 消息提醒小圆点的直径
public: signals:
    void indexChanged(int _index);
};


#endif //QTDEMO_PAGESWITCHER_H
