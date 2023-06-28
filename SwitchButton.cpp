//
// Created by TURIING on 2023/6/27.
//

#include "SwitchButton.h"

SwitchButton::SwitchButton(QWidget *_parent): QWidget(_parent) {
    this->setMouseTracking(true);

    QPalette palette = this->palette();
    // 背景颜色
    palette.setColor(QPalette::Window, m_unActiveColor);
    // 选中颜色
    palette.setColor(QPalette::Highlight, m_ActiveColor);
    // 未激活文本颜色
    palette.setColor(QPalette::WindowText, m_unActiveTextColor);
    // 鼠标悬停文本颜色
    palette.setColor(QPalette::HighlightedText, m_activeTextColor);
    // 鼠标悬浮颜色
    palette.setColor(QPalette::Light, m_hoverColor);
    this->setPalette(palette);

    /* 字体 */
    QFont font = this->font();
    font.setPixelSize(m_textSize);
    this->setFont(font);
}

void SwitchButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    /* 绘制背景圆角矩形 */
    drawBackgroundRect(painter);
    /* 绘制选中块 */
    drawRectForIndex(painter, m_currentItemIndex, palette().highlight());
    /* 绘制文本 */
    drawText(painter);
}

/*
 * 返回每个按钮索引对应的矩形区域
 */
QRect SwitchButton::indexToRect(int _index) const {
    int rectWidth = m_itemSize.at(_index).width();

    int rectWidthGlobal = 0;
    for(auto i = 0; i < _index; i++) {
        rectWidthGlobal += m_itemSize.at(i).width();
    }

    return QRect(rectWidthGlobal, 0, rectWidth, this->height());
}

/*
 * 返回鼠标位置对应的矩形区域索引
 */
int SwitchButton::mousePosToIndex(const QPoint &_point) const {
    for(auto i = 0, widthGlobal = 0; i < m_itemSize.count(); i++) {
        widthGlobal += m_itemSize.at(i).width();
        if(widthGlobal >= _point.x())
            return i;
    }
}


void SwitchButton::drawRectForIndex(QPainter &_painter, int _index, QBrush _brush) const {
    assert(_index >= 0);
    assert(_index < m_item.count());

    _painter.save();

    _painter.setBrush(_brush);
    // 如果是中间的区域
    if(_index > 0 && _index < m_item.count() - 1) {
        _painter.drawRect(indexToRect(_index));
        // 如果是第一个区域
    }else if(_index == 0) {
        // 由于不提供绘制只有一边是圆角的矩形，故先绘制一个圆角小矩形，再用一个非圆角的矩形盖住其一半
        _painter.drawRoundedRect(0, 0, m_borderRadius * 2, this->height(), m_borderRadius, m_borderRadius);
        _painter.drawRect(QRect(QPoint(m_borderRadius, 0), QPoint(indexToRect(0).width(), this->height())));
    }
    // 如果是最后一个区域
    else if(_index == m_item.count() - 1) {
        QRect lastRect = indexToRect(m_item.count() - 1);
        _painter.drawRoundedRect(lastRect.width() + lastRect.x() - m_borderRadius * 2, 0, m_borderRadius * 2, this->height(), m_borderRadius, m_borderRadius);
        _painter.drawRect(QRect(lastRect.x(), 0, lastRect.width() - m_borderRadius, this->height()));
    }

    _painter.restore();
}

/*
 * 绘制文本
 */
void SwitchButton::drawText(QPainter &_painter) const {
    _painter.save();

    QFont font = this->font();
    font.setWeight(QFont::Medium);
//    font.setStyleStrategy(QFont::PreferAntialias);
    font.setFamily("微软雅黑");
    _painter.setFont(font);


    QRect itemRect;
    auto index = mousePosToIndex(m_mouse);
    for(auto i = 0; i < m_item.count(); i++) {
        if((m_isHover && index == i) || i == m_currentItemIndex) {
            _painter.setPen(palette().highlightedText().color());
        }else {
            _painter.setPen(palette().windowText().color());
        }

        itemRect = indexToRect(i);
        _painter.drawText(itemRect, Qt::AlignCenter, m_item.at(i));
    }

    _painter.restore();
}

void SwitchButton::setText(int _index, const QString &_text) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    m_item[_index] = _text;
}

void SwitchButton::setCurrentIndex(int _index) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    if(_index != m_currentItemIndex){
        m_currentItemIndex = _index;
        update();
        emit indexChanged(m_currentItemIndex);
    }
}

void SwitchButton::insert(int _index, const QString &_text, int _width) {
    assert(_index >= 0);
    assert(_index < m_item.count());
    assert(_width > 0);

    m_item.insert(_index, _text);
    m_itemSize.insert(_index, QSize(_width, this->height()));
}

void SwitchButton::remove(int _index) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    m_item.remove(_index);
    m_item.remove(_index);
}

void SwitchButton::mousePressEvent(QMouseEvent *_event) {
    if(_event->button() == Qt::LeftButton) {
        setCurrentIndex(mousePosToIndex(_event->pos()));
    }
    QWidget::mousePressEvent(_event);
}

void SwitchButton::mouseMoveEvent(QMouseEvent *_event) {
    m_mouse = _event->pos();
    update();
    QWidget::mouseMoveEvent(_event);
}

void SwitchButton::enterEvent(QEvent *_event) {
    m_isHover = true;
    update();
    QWidget::enterEvent(_event);
}

void SwitchButton::leaveEvent(QEvent *_event) {
    m_isHover = false;
    update();
    QWidget::leaveEvent(_event);
}

void SwitchButton::append(const QString &_text, int _width) {
    assert(_width > 0);

    m_item.append(_text);
    m_itemSize.append(QSize(_width, this->height()));
}

void SwitchButton::drawBackgroundRect(QPainter &_painter) const {
    _painter.save();

    int widthTotal = 0;
    foreach(auto size, m_itemSize) {
        widthTotal += size.width();
    }

    _painter.setBrush(this->palette().window());
    _painter.drawRoundedRect(0, 0, widthTotal, this->height(), m_borderRadius, m_borderRadius);

    _painter.restore();
}

