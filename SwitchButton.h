//
// Created by TURIING on 2023/6/27.
//

#ifndef QTDEMO_SWITCHBUTTON_H
#define QTDEMO_SWITCHBUTTON_H

#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QVector>
#include <cassert>
#include <QMouseEvent>
#include <QDebug>

class SwitchButton: public QWidget{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *_parent = Q_NULLPTR);
    void setText(int _index, const QString &_text);
    void append(const QString &_text, int _width);
    void insert(int _index, const QString &_text, int _width);
    void remove(int _index);
    int getCurrentIndex() const { return m_currentItemIndex; };
    void setCurrentIndex(int _index);


protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void enterEvent(QEvent *_event) override;
    void leaveEvent(QEvent *_event) override;


private:
    QRect indexToRect(int _index) const;
    int mousePosToIndex(const QPoint &_point) const;
    void drawBackgroundRect(QPainter &_painter) const;
    void drawRectForIndex(QPainter &_painter, int _index, QBrush _brush) const;
    void drawText(QPainter &_painter) const;
private:
    /* 逻辑相关 */
    QPoint m_mouse = QPoint(-100, -100);
    QVector<QString> m_item;
    QVector<QSize> m_itemSize;                                                              // 每个item的尺寸
    int m_currentItemIndex = -1;
    bool m_isHover = false;                                                                 // 鼠标是否停留


    /* 界面相关 */
    uint m_borderRadius = 6;                                                                // 边框的圆角度数
    QColor m_unActiveColor = QColor(242, 242, 242);                                // 未激活背景色
    QColor m_ActiveColor = QColor(230, 230, 230);                                  // 激活背景色
    QColor m_unActiveTextColor = QColor(107,107,107);                              // 未激活文本颜色
    QColor m_activeTextColor = QColor(33, 33, 33);                                 // 激活文本颜色
    QColor m_hoverColor = QColor(93, 173, 226);                                    // 鼠标停留背景色
    int m_textSize = 13;                                                                    // 文本大小
public: signals:
    void indexChanged(int _currentIndex);
};


#endif //QTDEMO_SWITCHBUTTON_H
