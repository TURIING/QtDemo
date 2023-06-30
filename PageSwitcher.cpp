//
// Created by TURIING on 2023/6/29.
//

#include "PageSwitcher.h"

PageSwitcher::PageSwitcher(QWidget *_parent): QWidget(_parent) {
    m_textFont = this->font();
    m_textFont.setFamily("微软雅黑");
    m_textFont.setPixelSize(14);

    this->setCursor(Qt::PointingHandCursor);
    this->setMouseTracking(true);

    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, m_unActiveTextColor);
    palette.setColor(QPalette::HighlightedText, m_activeTextColor);
    palette.setColor(QPalette::Window, m_unActiveBgColor);
    palette.setColor(QPalette::Highlight, m_indicateBarColor);
    palette.setColor(QPalette::ToolTipBase, m_messageAlertColor);
    this->setPalette(palette);
}

void PageSwitcher::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    drawBackground(painter);

    drawIndicateBar(painter);

    drawText(painter);

    drawMessageAlert(painter);
}

void PageSwitcher::append(const QString &_text, bool _has_message) {
    assert(_text.isEmpty() != true);

    m_item.append(Item { _text, _has_message } );

    this->resize(computeTotalWidth(m_item.count()), this->height());
}

/*
 * 绘制文本
 */
void PageSwitcher::drawText(QPainter &_painter) const {
    _painter.save();

    _painter.setFont(m_textFont);

    for(auto i = 0; i < m_item.count(); i++) {
        if((i == mousePosToIndex() && m_isHover) || m_currentItemIndex == i)
            _painter.setPen(palette().highlightedText().color());
        else
            _painter.setPen(palette().windowText().color());

        _painter.drawText(indexToRect(i), Qt::AlignCenter, m_item.at(i).text);
    }

    _painter.restore();
}

/*
 * 返回索引对应的item宽度
 */
int PageSwitcher::indexToWidth(int _index) const {
    assert(_index >= 0);
    assert(_index < m_item.count());


    auto textWidth = computeTextWidth(m_item.at(_index).text);

    return m_paddingForHorizon * 2 + textWidth;
}

/*
 * 返回索引对应的item区域
 */
QRect PageSwitcher::indexToRect(int _index) const {
    assert(_index >= 0);
    assert(_index < m_item.count());

    return QRect(computeTotalWidth(_index), 0, indexToWidth(_index), this->height());
}

/*
 * 计算文本的宽度占用的像素
 */
int PageSwitcher::computeTextWidth(const QString &_text) const {
    QFontMetrics fontMetrics(m_textFont);
    return fontMetrics.horizontalAdvance(_text);
}

/*
 * 绘制背景
 */
void PageSwitcher::drawBackground(QPainter &_painter) const {
    _painter.save();

    _painter.setPen(Qt::NoPen);
    _painter.setBrush(palette().window());
    _painter.drawRect(this->rect());

    _painter.restore();
}

/*
 * 返回给定索引所指区块的横坐标，即该区块之前的所有区块的宽度和
 */
int PageSwitcher::computeTotalWidth(int _index) const {
    assert(_index >= 0);
    assert(_index <= m_item.count());

    int widthCumulate = 0;
    for(auto i = 0; i < _index; i++)
        widthCumulate += indexToWidth(i);
    return widthCumulate;
}

/*
 * 绘制指示条
 */
void PageSwitcher::drawIndicateBar(QPainter &_painter) const {
    _painter.save();

    _painter.setPen(Qt::NoPen);
    _painter.setBrush(palette().highlight().color());

    auto rect = indexToRect(m_currentItemIndex);
    int width;
    if(m_item.at(m_currentItemIndex).has_message)
        width = computeTextWidth(m_item.at(m_currentItemIndex).text) + 3 + m_messageAlertDiameter;
    else
        width = computeTextWidth(m_item.at(m_currentItemIndex).text);

    _painter.drawRect(rect.x() + m_paddingForHorizon, (int)(this->height() * 0.80), width, 2);

    _painter.restore();
}

void PageSwitcher::mousePressEvent(QMouseEvent *_event) {
    auto index = mousePosToIndex();
    if(_event->button() == Qt::LeftButton && m_currentItemIndex != index) {
        m_currentItemIndex = index;
        this->update();
        emit indexChanged(m_currentItemIndex);
    }
    QWidget::mousePressEvent(_event);
}

/*
 * 返回鼠标位置对应的区块索引
 */
int PageSwitcher::mousePosToIndex() const {
    int widthCumulate = 0;
    for(auto i = 0; i < m_item.count(); i++) {
        widthCumulate += indexToWidth(i);
        if(widthCumulate > m_mousePos.x())
            return i;
    }
}

void PageSwitcher::mouseMoveEvent(QMouseEvent *_event) {
    m_mousePos = _event->pos();
    this->update();

    QWidget::mouseMoveEvent(_event);
}

void PageSwitcher::enterEvent(QEvent *_event) {
    m_isHover = true;
    this->update();

    QWidget::enterEvent(_event);
}

void PageSwitcher::leaveEvent(QEvent *_event) {
    m_isHover = false;
    this->update();

    QWidget::leaveEvent(_event);
}

/*
 * 设置默认选中项
 */
void PageSwitcher::setCurrentItem(int _index) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    m_currentItemIndex = _index;
}

/*
 * 绘制消息提醒小圆点
 */
void PageSwitcher::drawMessageAlert(QPainter &_painter) const {
    _painter.save();

    _painter.setBrush(palette().toolTipBase());

    for(auto i = 0; i < m_item.count(); i++) {
        if(m_item.at(i).has_message) {
            auto x = computeTotalWidth(i) + m_paddingForHorizon + computeTextWidth(m_item.at(i).text) + 3;
            _painter.drawEllipse(x, this->height() * 0.4, m_messageAlertDiameter, m_messageAlertDiameter);
        }

    }

    _painter.restore();
}
/*
 * 设置消息提醒
 */
void PageSwitcher::setMessageAlert(int _index, bool _has_message) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    m_item[_index].has_message = _has_message;
}

