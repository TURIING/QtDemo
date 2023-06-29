//
// Created by TURIING on 2023/6/28.
//

#ifndef QTDEMO_MENUSWITCHER_H
#define QTDEMO_MENUSWITCHER_H
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>
#include <QtSvg/QSvgRenderer>
#include <QPixmap>

class MenuSwitcher: public QWidget{
    Q_OBJECT
    struct Item {
        QString text;
        QString iconActive;
        QString iconUnActive;
        QString iconHover;
    };
public:
    explicit MenuSwitcher(QWidget *_parent = Q_NULLPTR);
    void append(const QString &_text, const QString &_iconActive, const QString &_iconUnActive, const QString &_iconHover);
    void setDefaultItem(int _index);

protected:
    void paintEvent(QPaintEvent *_event) override;
    void enterEvent(QEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void leaveEvent(QEvent *_event) override;

private:
    void drawBorderBackground(QPainter &_painter) const;
    void drawHoverRect(QPainter &_painter) const;
    void drawIndicateBar(QPainter &_painter) const;
    void drawActiveRect(QPainter &_painter) const;
    void drawIcon(QPainter &_painter) const;
    void drawText(QPainter &_painter) const;

    QRect indexToRect(int _index) const;
    int mousePosToIndex() const;

    int averageRectHeight() const;

private:
    /* 逻辑相关 */
    QVector<Item> m_item;
    bool m_isHover;                                                                                 // 鼠标是否悬停
    QPoint m_mousePos;                                                                              // 用于记录鼠标在控件中的位置
    int m_currentItem = -1;                                                                         // 当前选中的项


    /* UI相关*/
    QColor m_indicateBarColor = QColor(255, 108, 55);                                       // 指示条颜色
    int m_indicateBarWidth = 2;                                                                      // 指示条宽度
    QColor m_unActiveBgColor = QColor(249, 249, 249);                                       // 未激活时的背景色
    QColor m_activeBgColor = QColor(230, 230, 230);                                         // 激活后的背景色
    QColor m_hoverBgColor = QColor(237, 237, 237);                                          // 鼠标悬停时的背景色
    QColor m_unActiveTextColor = QColor(107,107,107);                                       // 未激活时的文本色
    QColor m_activeTextColor = QColor(33, 33, 33);                                          // 激活后的文本色
    QColor m_hoverTextColor = QColor(33, 33, 33);                                           // 鼠标悬停时的文本色
public: signals:
    void indexChanged(int _index);
};


#endif //QTDEMO_MENUSWITCHER_H
