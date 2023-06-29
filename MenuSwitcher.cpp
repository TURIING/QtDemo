//
// Created by TURIING on 2023/6/28.
//

#include "MenuSwitcher.h"

MenuSwitcher::MenuSwitcher(QWidget *_parent): QWidget(_parent) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, m_unActiveBgColor);
    palette.setColor(QPalette::Light, m_hoverBgColor);
    palette.setColor(QPalette::AlternateBase, m_indicateBarColor);
    palette.setColor(QPalette::Highlight, m_activeBgColor);
    palette.setColor(QPalette::WindowText, m_unActiveTextColor);
    palette.setColor(QPalette::HighlightedText, m_activeTextColor);
    this->setPalette(palette);

    this->setMouseTracking(true);

    this->resize(this->width(), m_item.count() * averageRectHeight());

    this->setCursor(Qt::PointingHandCursor);

}

void MenuSwitcher::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    drawBorderBackground(painter);

    drawActiveRect(painter);

    drawHoverRect(painter);

    drawIndicateBar(painter);

    drawIcon(painter);

    drawText(painter);
}

/*
 * 绘制指示条
 */
void MenuSwitcher::drawIndicateBar(QPainter &_painter) const {
    assert(m_currentItem >= 0);
    assert(m_currentItem < m_item.count());

    _painter.save();

    _painter.setBrush(palette().alternateBase());
    QRect havorRect = indexToRect(m_currentItem);
    _painter.drawRect(0, havorRect.y(), m_indicateBarWidth, havorRect.height());

    _painter.restore();
}

/*
 * 绘制背景矩形
 */
void MenuSwitcher::drawBorderBackground(QPainter &_painter) const {
    _painter.save();

    _painter.setBrush(this->palette().window());
    _painter.drawRect(this->rect());

    _painter.restore();
}
/*
 * 返回索引对应的按钮区域
 */
QRect MenuSwitcher::indexToRect(int _index) const {
    assert(_index >= 0);
    assert(_index < m_item.count());

    return QRect(0, _index * averageRectHeight(), this->width(), averageRectHeight());
}

void MenuSwitcher::enterEvent(QEvent *_event) {
    m_isHover = true;
    this->update();

    QWidget::enterEvent(_event);
}

void MenuSwitcher::mousePressEvent(QMouseEvent *_event) {
    m_currentItem = mousePosToIndex();
    this->update();
    emit indexChanged(m_currentItem);

    QWidget::mousePressEvent(_event);
}

void MenuSwitcher::mouseMoveEvent(QMouseEvent *_event) {
    m_mousePos = _event->pos();
    this->update();

    QWidget::mouseMoveEvent(_event);
}

void MenuSwitcher::leaveEvent(QEvent *_event) {
    m_isHover = false;
    this->update();

    QWidget::leaveEvent(_event);
}

/*
 * 绘制鼠标悬停的区域
 */
void MenuSwitcher::drawHoverRect(QPainter &_painter) const {
    if(!m_isHover) return;

    _painter.save();

    _painter.setBrush(this->palette().light());
    int index = mousePosToIndex();
    _painter.drawRect(indexToRect(index));

    _painter.restore();
}

/*
 * 返回鼠标悬停位置对应的索引
 */
int MenuSwitcher::mousePosToIndex() const {
    assert(m_item.count() != 0);

    return m_mousePos.y() / averageRectHeight();
}

void MenuSwitcher::append(const QString &_text, const QString &_iconActive, const QString &_iconUnActive, const QString &_iconHover) {
    m_item.append(Item{_text, _iconActive, _iconUnActive, _iconHover});
    // 动态调整控件的高度
    this->resize(this->width(), m_item.count() * averageRectHeight());
}

/*
 * 返回每个区块占用的大小
 */
int MenuSwitcher::averageRectHeight() const {
    auto count = m_item.count();
    if(count == 0)
        return 0;
    else
        return this->height() / m_item.count();
}

void MenuSwitcher::setDefaultItem(int _index) {
    assert(_index >= 0);
    assert(_index < m_item.count());

    m_currentItem = _index;
}

/*
 * 绘制选中的区域
 */
void MenuSwitcher::drawActiveRect(QPainter &_painter) const {
    assert(m_currentItem >= 0);
    assert(m_currentItem < m_item.count());

    _painter.save();

    _painter.setBrush(palette().highlight());
    _painter.drawRect(indexToRect(m_currentItem));

    _painter.restore();
}

/*
 * 绘制图标
 */
void MenuSwitcher::drawIcon(QPainter &_painter) const {
    QSvgRenderer renderer;

    for(auto i = 0; i < m_item.count(); i++) {
        if(mousePosToIndex() == i && m_isHover)
            renderer.load(m_item.at(i).iconHover);
        else if(m_currentItem == i)
            renderer.load(m_item.at(i).iconActive);
        else
            renderer.load(m_item.at(i).iconUnActive);

        renderer.render(&_painter, QRect(this->width() / 2.4, i * averageRectHeight() + averageRectHeight() / 5, 20, 20));
    }

}
/*
 * 绘制文本
 */
void MenuSwitcher::drawText(QPainter &_painter) const {
    _painter.save();

    for(auto i = 0; i < m_item.count(); i++) {
        if((i == mousePosToIndex() && m_isHover) || m_currentItem == i)
            _painter.setPen(palette().highlightedText().color());
        else
            _painter.setPen(palette().windowText().color());

        QFont font;
        font.setFamily("微软雅黑");
        font.setPixelSize(12);
        _painter.setFont(font);

        _painter.drawText(QRect(0, i * indexToRect(i).height() + averageRectHeight() / 2.2, this->width(), averageRectHeight() / 2), Qt::AlignCenter, m_item.at(i).text);
    }


    _painter.restore();
}
